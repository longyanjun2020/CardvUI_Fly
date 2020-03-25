﻿#ifdef SUPPORT_PLAYER_MODULE
#include "demux.h"
#include "packet.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

extern AVPacket flush_pkt;

static int decode_interrupt_cb(void *ctx)
{
    player_stat_t *is = (player_stat_t *)ctx;
    return is->abort_request;
}

static int demux_init(player_stat_t *is)
{
    AVFormatContext *p_fmt_ctx = NULL;
    int err, i, ret;
    int a_idx;
    int v_idx;

    p_fmt_ctx = avformat_alloc_context();
    if (!p_fmt_ctx)
    {
        printf("Could not allocate context.\n");
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    // 中断回调机制。为底层I/O层提供一个处理接口，比如中止IO操作。
    p_fmt_ctx->interrupt_callback.callback = decode_interrupt_cb;
    p_fmt_ctx->interrupt_callback.opaque = is;

    // 1. 构建AVFormatContext
    // 1.1 打开视频文件：读取文件头，将文件格式信息存储在"fmt context"中
    err = avformat_open_input(&p_fmt_ctx, is->filename, NULL, NULL);
    if (err < 0)
    {
        if (err == -101)
        {
            printf("error : network is not reachable!\n");
            if (is->playerController.fpPlayError)
                is->playerController.fpPlayError(err);
        }
        else
        {
            printf("avformat_open_input() failed %x\n", err);
            if (is->playerController.fpPlayError)
                is->playerController.fpPlayError(err);
        }
        ret = -1;
        goto fail;
    }
    is->p_fmt_ctx = p_fmt_ctx;
    // 1.2 搜索流信息：读取一段视频文件数据，尝试解码，将取到的流信息填入p_fmt_ctx->streams
    //     ic->streams是一个指针数组，数组大小是pFormatCtx->nb_streams
    err = avformat_find_stream_info(p_fmt_ctx, NULL);
    if (err < 0)
    {
        printf("avformat_find_stream_info() failed %d\n", err);
        ret = -1;
        goto fail;
    }

    // get media duration
    printf("probesize is %lld, duration is %lld ms, start_time is %lld\n", is->p_fmt_ctx->probesize, is->p_fmt_ctx->duration, is->p_fmt_ctx->start_time);
    if (is->playerController.fpGetDuration)
        is->playerController.fpGetDuration(is->p_fmt_ctx->duration);

    // 2. 查找第一个音频流/视频流
    a_idx = -1;
    v_idx = -1;
    for (i = 0; i < (int)p_fmt_ctx->nb_streams; i++)
    {
        printf("Find a stream, index_%d=type_%d\n", i,p_fmt_ctx->streams[i]->codecpar->codec_type);
        if ((p_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) &&
            (a_idx == -1))
        {
            a_idx = i;
            printf("Find a audio stream, index %d\n", a_idx);
        }
        if ((p_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)/* && (v_idx == -1)*/)
        {
            v_idx = i;//use the last streaming
            printf("Find a video stream, index %d\n", v_idx);
        }

        //The last streaming will be playing always.
        #if 0
        if (a_idx != -1 && v_idx != -1)
        {
            break;
        }
        #endif
    }
    if (a_idx == -1 && v_idx == -1)
    {
        printf("Cann't find any audio/video stream\n");
        ret = -1;
 fail:
        if (p_fmt_ctx != NULL)
        {
            avformat_close_input(&p_fmt_ctx);
        }

        return ret;
    }

    is->audio_idx = a_idx;
    is->video_idx = v_idx;
    printf("audio idx: %d,video idx: %d\n",a_idx,v_idx);

    double totle_seconds = p_fmt_ctx->duration * av_q2d(AV_TIME_BASE_Q);
    printf("total time of file : %f\n", totle_seconds);

    if (is->audio_idx >= 0)
    {
        is->p_audio_stream = p_fmt_ctx->streams[a_idx];
        printf("audio codec_info_nb_frames:%d, nb_frames:%lld, probe_packet:%d\n", is->p_audio_stream->codec_info_nb_frames, is->p_audio_stream->nb_frames, is->p_audio_stream->probe_packets);
        //printf("audio duration:%lld, nb_frames:%lld\n", is->p_audio_stream->duration, is->p_audio_stream->nb_frames);
    }
    if (is->video_idx >= 0)
    {
        is->p_video_stream = p_fmt_ctx->streams[v_idx];
        printf("video codec_info_nb_frames:%d, nb_frames:%lld, probe_packet:%d\n", is->p_video_stream->codec_info_nb_frames, is->p_video_stream->nb_frames, is->p_video_stream->probe_packets);
        //printf("video duration:%lld, nb_frames:%lld\n", is->p_video_stream->duration, is->p_video_stream->nb_frames);
    }

    // set GetCurPlayPos callback
    if (is->video_idx >= 0 && is->p_video_stream->codec_info_nb_frames > 1)
    {
        is->playerController.fpGetCurrentPlayPosFromVideo = is->playerController.fpGetCurrentPlayPos;
        printf("get play pos from video stream\n");
    }
    else
    {
        is->playerController.fpGetCurrentPlayPosFromAudio = is->playerController.fpGetCurrentPlayPos;
        printf("get play pos from audio stream\n");
    }

    return 0;
}

int demux_deinit()
{
    return 0;
}

static int stream_has_enough_packets(AVStream *st, int stream_id, packet_queue_t *queue)
{
    //printf("id: %d,disposition: %d,nb_packets: %d,duration: %d\n",stream_id,st->disposition,queue->nb_packets,queue->duration);
    return stream_id < 0 ||
           queue->abort_request ||
           (st->disposition & AV_DISPOSITION_ATTACHED_PIC) ||
           (queue->nb_packets > MIN_FRAMES && (!queue->duration || av_q2d(st->time_base) * queue->duration > 1.0));
}

static void step_to_next_frame(player_stat_t *is)
{
    /* if the stream is paused unpause it, then step */
    if (is->paused)
        stream_toggle_pause(is);
    is->step = 1;
}

/* this thread gets the stream from the disk or the network */
static void* demux_thread(void *arg)
{
    player_stat_t *is = (player_stat_t *)arg;
    int ret;
    AVPacket pkt1, *pkt = &pkt1;

    struct timeval now;
    struct timespec outtime;

    pthread_mutex_t wait_mutex;

    if (pthread_mutex_init(&wait_mutex, NULL) != SUCCESS)
    {
        printf("[%s %d]exec function failed\n", __FUNCTION__, __LINE__);
        return NULL;
    }

    is->eof = 0;
    is->audio_complete = 0;
    is->video_complete = 0;
    // 4. 解复用处理
    while (1)
    {

        if (is->abort_request)
        {
            printf("demux thread exit\n");
            break;
        }
        //printf("loop start paused: %d,last_paused: %d\n",is->paused,is->last_paused);
        if (is->paused != is->last_paused) {
            is->last_paused = is->paused;
            if (is->paused)
            {
                is->read_pause_return = av_read_pause(is->p_fmt_ctx);
            }
            else
            {
                av_read_play(is->p_fmt_ctx);
            }
        }

        if (is->paused)
        {
            /* wait 10 ms */
            pthread_mutex_lock(&wait_mutex);

            gettimeofday(&now, NULL);
            outtime.tv_sec = now.tv_sec;
            outtime.tv_nsec = now.tv_usec * 1000 + 10 * 1000 * 1000;//timeout 10ms

            pthread_cond_timedwait(&is->continue_read_thread, &wait_mutex, &outtime);

            //SDL_CondWaitTimeout(is->continue_read_thread, wait_mutex, 10);
            pthread_mutex_unlock(&wait_mutex);

            continue;

        }

        if (is->seek_req) {
            int64_t seek_target = is->seek_pos;
            int64_t seek_min    = is->seek_rel > 0 ? seek_target - is->seek_rel + 2: INT64_MIN;
            int64_t seek_max    = is->seek_rel < 0 ? seek_target - is->seek_rel - 2: INT64_MAX;

            // FIXME the +-2 is due to rounding being not done in the correct direction in generation
            // of the seek_pos/seek_rel variables

            ret = avformat_seek_file(is->p_fmt_ctx, -1, seek_min, seek_target, seek_max, is->seek_flags);
            //ret = av_seek_frame(is->p_fmt_ctx, -1, seek_target, is->seek_flags);

            if (ret < 0) {
                av_log(NULL, AV_LOG_ERROR,
                       "%s: error while seeking\n", is->p_fmt_ctx->url);
            } else {
                if (is->audio_idx >= 0) {
                    packet_queue_flush(&is->audio_pkt_queue);
                    packet_queue_put(&is->audio_pkt_queue, &flush_pkt);
                }
                if (is->video_idx >= 0) {
                    packet_queue_flush(&is->video_pkt_queue);
                    packet_queue_put(&is->video_pkt_queue, &flush_pkt);
                }
                /*
                if (is->seek_flags & AVSEEK_FLAG_BYTE) {
                   set_clock(&is->extclk, NAN, 0);
                } else {
                   set_clock(&is->extclk, seek_target / (double)AV_TIME_BASE, 0);
                }
                */
            }
            is->seek_req = 0;
            //is->queue_attachments_req = 1;
            is->eof = 0;
            if (is->paused)
                step_to_next_frame(is);
        }


        /* if the queue are full, no need to read more */
        if (is->audio_pkt_queue.size + is->video_pkt_queue.size > MAX_QUEUE_SIZE ||
            (stream_has_enough_packets(is->p_audio_stream, is->audio_idx, &is->audio_pkt_queue) &&
             stream_has_enough_packets(is->p_video_stream, is->video_idx, &is->video_pkt_queue)))
        {
            /* wait 10 ms */
            pthread_mutex_lock(&wait_mutex);

            gettimeofday(&now, NULL);

            outtime.tv_sec = now.tv_sec;
            outtime.tv_nsec = now.tv_usec * 1000 + 10 * 1000 * 1000;//timeout 10ms

            pthread_cond_timedwait(&is->continue_read_thread,&wait_mutex,&outtime);

            //SDL_CondWaitTimeout(is->continue_read_thread, wait_mutex, 10);
            pthread_mutex_unlock(&wait_mutex);
            //printf("queue size: %d\n",is->audio_pkt_queue.size + is->video_pkt_queue.size);
            //printf("wait video queue avalible pktnb: %d\n",is->video_pkt_queue.nb_packets);
            //printf("wait audio queue avalible pktnb: %d\n",is->audio_pkt_queue.nb_packets);

            continue;
        }

        // 4.1 从输入文件中读取一个packet
        ret = av_read_frame(is->p_fmt_ctx, pkt);
        if (ret < 0)
        {
            if (((ret == AVERROR_EOF) || avio_feof(is->p_fmt_ctx->pb)) && !is->eof)
            {
                // 输入文件已读完，则往packet队列中发送NULL packet，以冲洗(flush)解码器，否则解码器中缓存的帧取不出来
                if (is->video_idx >= 0)
                {
                    packet_queue_put_nullpacket(&is->video_pkt_queue, is->video_idx);
                }
                if (is->audio_idx >= 0)
                {
                    packet_queue_put_nullpacket(&is->audio_pkt_queue, is->audio_idx);
                }
                is->eof = 1;
            }

            pthread_mutex_lock(&wait_mutex);

            gettimeofday(&now, NULL);
            outtime.tv_sec = now.tv_sec;
            outtime.tv_nsec = now.tv_usec * 1000 + 10 * 1000 * 1000;//timeout 10ms
            pthread_cond_timedwait(&is->continue_read_thread, &wait_mutex, &outtime);

            pthread_mutex_unlock(&wait_mutex);

            continue;
        }
        else
        {
            is->eof = 0;
        }

        // 4.3 根据当前packet类型(音频、视频、字幕)，将其存入对应的packet队列
        if (pkt->stream_index == is->audio_idx)
        {
            packet_queue_put(&is->audio_pkt_queue, pkt);
        }
        else if (pkt->stream_index == is->video_idx)
        {
            packet_queue_put(&is->video_pkt_queue, pkt);
        }
        else
        {
            av_packet_unref(pkt);
        }
    }

    pthread_mutex_destroy(&wait_mutex);
    return NULL;
}

int open_demux(player_stat_t *is)
{
    if (demux_init(is) != 0)
    {
        printf("demux_init() failed\n");
        return -1;
    }

    CheckFuncResult(pthread_create(&is->read_tid, NULL, demux_thread, is));

    return 0;
}

int demux_thumbnail(char *src_filename, char *dst_filename)
{
    AVFormatContext *fmt_ctx = NULL;
    AVPacket pkt;
    int fd = 0;
    int ret = 0;
    unsigned int stream_idx = 0;
    int thumb_idx = 0;

    ret = access(dst_filename, F_OK);
    if (ret == 0) {
        unlink(dst_filename);
    }

    /* open input file, and allocate format context */
    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        return -1;
    }

    for (stream_idx = 0; stream_idx < fmt_ctx->nb_streams; stream_idx++) {
        AVStream * stream = fmt_ctx->streams[stream_idx];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_DATA) {
            thumb_idx = stream_idx; // First AVMEDIA_TYPE_DATA stream is thumbnail.
            break;
        }
    }

    /* dump input information to stderr */
    // av_dump_format(fmt_ctx, 0, src_filename, 0);

    /* initialize packet, set data to NULL, let the demuxer fill it */
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    /* read frames from the file */
    while (av_read_frame(fmt_ctx, &pkt) >= 0) {
        if (pkt.stream_index == thumb_idx) {
            fd = open(dst_filename,  O_WRONLY | O_CREAT, 0666);
            if (fd) {
                write(fd, pkt.data, pkt.size);
                close(fd);
            }
            av_packet_unref(&pkt);
            printf("demux thumb succeeded\n");
            break;
        }
        av_packet_unref(&pkt);
    }

    avformat_close_input(&fmt_ctx);
    return ret;
}

int64_t demux_duration(char *src_filename)
{
#define DURATION_MAX_READ_SIZE 100000LL
#define DURATION_MAX_RETRY 6

    AVFormatContext *fmt_ctx = NULL;
    AVPacket pkt;
    unsigned int stream_idx = 0;
    int video_idx = 0;
    int64_t filesize, offset, duration, start_pts = AV_NOPTS_VALUE, end_pts = AV_NOPTS_VALUE;
    int retry = 0;
    AVRational src_tb = {1, 90000};
    AVRational dst_tb = {1, 1000000};

    /* open input file, and allocate format context */
    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        return -1;
    }

    for (stream_idx = 0; stream_idx < fmt_ctx->nb_streams; stream_idx++) {
        AVStream * stream = fmt_ctx->streams[stream_idx];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_idx = stream_idx; // Find first AVMEDIA_TYPE_VIDEO stream.
            break;
        }
    }

    /* dump input information to stderr */
    // av_dump_format(fmt_ctx, 0, src_filename, 0);

    filesize = fmt_ctx->pb ? avio_size(fmt_ctx->pb) : 0;

    /* initialize packet, set data to NULL, let the demuxer fill it */
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    do {
        offset = filesize - (DURATION_MAX_READ_SIZE << retry);
        if (offset < 0)
            offset = 0;
        avio_seek(fmt_ctx->pb, offset, SEEK_SET);

        /* read last pts from last video frame */
        while (av_read_frame(fmt_ctx, &pkt) == 0) {
            if (pkt.stream_index == video_idx && pkt.pts != AV_NOPTS_VALUE) {
                end_pts = pkt.pts;
            }
            av_packet_unref(&pkt);
        }
    } while (end_pts == AV_NOPTS_VALUE && ++retry <= DURATION_MAX_RETRY);

    if (end_pts == AV_NOPTS_VALUE) {
        return -1;
    }

#if 0 // TBD
    avio_seek(fmt_ctx->pb, 0, SEEK_SET);

    /* read first pts from first video frame */
    while (av_read_frame(fmt_ctx, &pkt) == 0) {
        if (pkt.stream_index == video_idx && pkt.pts != AV_NOPTS_VALUE) {
            start_pts = pkt.pts;
            av_packet_unref(&pkt);
            break;
        }
        av_packet_unref(&pkt);
    }

    if (start_pts == AV_NOPTS_VALUE) {
        return -1;
    }
#else
    start_pts = 0;
#endif

    duration = av_rescale_q(end_pts - start_pts, src_tb, dst_tb);
    // printf("[%s] duration [%lld]\n", src_filename, duration);

    avformat_close_input(&fmt_ctx);

    return duration;
}

#endif
