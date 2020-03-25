/*
 * Carimpl.cpp
 *
 * This file use to exchange data between CARDVUI with CARDVIMPL.
 *
 *  Created on: 2019-10-10
 *      Author: lei.qin
 */

#include "entry/EasyUIContext.h"
#include "uart/UartContext.h"
#include "manager/ConfigManager.h"
#include <cstring>
#include "utils/Log.h"
#include <stdlib.h>
#include <sys/statfs.h>
#include "fcntl.h"
#include "carimpl.h"
#include "demux.h"
#include "MenuCommon.h"
#include <libexif/exif-loader.h>

CarDV_Info carimpl = {0};
bool bDcfMount = FALSE;

#define TEST_FILE_NUM   6
//const char *mediaFile[TEST_FILE_NUM]={"/tmp/udisk/Normal/F/Spilder_Man_1080P_NB.MOV",
//"/tmp/udisk/Normal/F/REC20190607-120607-0.ts",
//"/tmp/udisk/Normal/F/720p_oldboykaraok_30p.mpg",
//"/tmp/udisk/Normal/F/264.480p.MOV",
//"/tmp/udisk/Normal/F/REC20190607-120607-0_singlechnl_ss.ts",
//"/tmp/udisk/Normal/F/REC20190607-120607-1_dualstream_ss.ts",
//};
const char *mediaFile[TEST_FILE_NUM]={"/mnt/mmc/Normal/F/Spilder_Man_1080P_NB.MOV",
"/mnt/mmc/Normal/F/REC20190607-120607-0.ts",
"/mnt/mmc/Normal/F/720p_oldboykaraok_30p.mpg",
"/mnt/mmc/Normal/F/264.480p.MOV",
"/mnt/mmc/Normal/F/REC20190607-120607-0_singlechnl_ss.ts",
"/mnt/mmc/Normal/F/REC20190607-120607-1_dualstream_ss.ts",
};


bool Carimpl_SyncAllSetting(void) {
    //carimpl maybe need to maintain all of user`s setting.
    return true;
}

bool Carimpl_Reset(void)
{
    carimpl.stBrowserInfo.u8CamId = 0;     //fron cam
    carimpl.stBrowserInfo.u8DBId = 0;      //normal folder
    printf("%s %d\n", __FUNCTION__, __LINE__);
    for (int i = 0; i < DB_NUM; i++)
        for (int j = 0; j < CAM_NUM; j++)
            carimpl.stBrowserInfo.u32CurFileIdx[i][j] = 0;
    return true;
}

void Carimpl_Send2Fifo(const void *cmd, size_t size)
{
    int pipe_fd_w = 0;
    pipe_fd_w = open(FIFO_NAME, O_WRONLY);
    if (pipe_fd_w > 0) {
        write(pipe_fd_w, cmd, size);
        close(pipe_fd_w);
    }
}

/**********************************************************/
/********************* browser ****************************/
/**********************************************************/

int Carimpl_DcfMount(void)
{
    int ret = 0;

    if (bDcfMount)
        return 0;

    for (int i = 0; i < DB_NUM; i++)
        for (int j = 0; j < CAM_NUM; j++) {
            ret = DCF_Mount(i, j);
            if (ret < 0)
                goto L_DCF_ERR;
        }

    bDcfMount = TRUE;
    return ret;

L_DCF_ERR:
    for (int i = 0; i < DB_NUM; i++)
        for (int j = 0; j < CAM_NUM; j++)
            DCF_UnMount(i, j);

    return 0;
}

int Carimpl_DcfUnmount(void)
{
    int ret = 0;

    if (bDcfMount == FALSE)
        return 0;

    bDcfMount = FALSE;

    for (int i = 0; i < DB_NUM; i++)
        for (int j = 0; j < CAM_NUM; j++)
            DCF_UnMount(i, j);

    return ret;
}

unsigned int Carimpl_GetTotalFiles(unsigned char u8DB, unsigned char u8CamId)
{
    return DCF_GetDBFileCnt(u8DB, u8CamId);
}

unsigned int Carimpl_GetTotalFiles(void)
{
    return DCF_GetDBFileCnt(carimpl.stBrowserInfo.u8DBId, carimpl.stBrowserInfo.u8CamId);
}

unsigned int Carimpl_GetCurFileIdx(unsigned char u8DB, unsigned char u8CamId)
{
    return carimpl.stBrowserInfo.u32CurFileIdx[u8DB][u8CamId];
}

unsigned int Carimpl_GetCurFileIdx(void)
{
    return carimpl.stBrowserInfo.u32CurFileIdx[carimpl.stBrowserInfo.u8DBId][carimpl.stBrowserInfo.u8CamId];
}

bool Carimpl_SetCurFileIdx(unsigned char u8DB, unsigned char u8CamId, unsigned int u32FileIdx)
{
    // Idx from tail or head
    carimpl.stBrowserInfo.u32CurFileIdx[u8DB][u8CamId] = u32FileIdx;
    IPC_CarInfo_Write_BrowserInfo(&carimpl.stBrowserInfo);
    return true;
}

bool Carimpl_SetCurFileIdx(unsigned int u32FileIdx)
{
    // Idx from tail or head
    carimpl.stBrowserInfo.u32CurFileIdx[carimpl.stBrowserInfo.u8DBId][carimpl.stBrowserInfo.u8CamId] = u32FileIdx;
    IPC_CarInfo_Write_BrowserInfo(&carimpl.stBrowserInfo);
    return true;
}

bool Carimpl_SetCurFolder(unsigned char u8DB, unsigned char u8CamId)
{
    if (u8DB >= DB_NUM || u8CamId >= CAM_NUM) {
        printf("%s err %d\n",__FUNCTION__, __LINE__);
        return FALSE;
    }

    carimpl.stBrowserInfo.u8DBId = u8DB;
    carimpl.stBrowserInfo.u8CamId = u8CamId;
    IPC_CarInfo_Write_BrowserInfo(&carimpl.stBrowserInfo);
    return TRUE;
}

unsigned char Carimpl_GetCurDB(void)
{
    return carimpl.stBrowserInfo.u8DBId;
}

char* Carimpl_GetCurFileName(unsigned char u8DB, unsigned char u8CamId, unsigned int u32FileIdx)
{
    return DCF_GetFileNameFromTailByIdx(u8DB, u8CamId, u32FileIdx);
}

char* Carimpl_GetCurFileName(unsigned int u32FileIdx)
{
    return DCF_GetFileNameFromTailByIdx(carimpl.stBrowserInfo.u8DBId, carimpl.stBrowserInfo.u8CamId, u32FileIdx);
}

unsigned int Carimpl_GetFileThumbnail(char *pFileName, char *pThumbFileName)
{
    return demux_thumbnail(pFileName, pThumbFileName);
}

unsigned int Carimpl_GetJpegFileThumbnail(char *pFileName, char *pThumbFileName)
{
    int ret = 0;
    int fd = 0;
    ExifLoader *loader;

    ret = access(pThumbFileName, F_OK);
    if (ret == 0) {
        unlink(pThumbFileName);
    }

    /* Create an ExifLoader object to manage the EXIF loading process */
    loader = exif_loader_new();
    if (loader) {
        ExifData *exif;

        /* Load the EXIF data from the image file */
        exif_loader_write_file(loader, pFileName);

        /* Get a pointer to the EXIF data */
        exif = exif_loader_get_data(loader);

        /* The loader is no longer needed--free it */
        exif_loader_unref(loader);
        loader = NULL;
        if (exif) {
            /* Make sure the image had a thumbnail before trying to write it */
            if (exif->data && exif->size) {
                fd = open(pThumbFileName, O_WRONLY | O_CREAT, 0666);
                if (fd >= 0) {
                    write(fd, exif->data, exif->size);
                    close(fd);
                }
            }
            /* Free the EXIF data */
            exif_data_unref(exif);
        }
    }
    return ret;
}

unsigned int Carimpl_GetFileDuration(char *pFileName)
{
    int64_t duration = demux_duration(pFileName);
    duration = duration / 1000000;
    return (int)duration;
}

/**********************************************************/
/********************* record *****************************/
/**********************************************************/


/**********************************************************/
/********************* playback ***************************/
/**********************************************************/


/**********************************************************/
/********************** setting ***************************/
/**********************************************************/

static bool carimpl_ExecCmdHandler(const char *szCmdType, const char *szCmdParam)
{
    char cmdstr[256] = {0};
    int  cmdstatus = 0;

    sprintf(cmdstr, "%s %s %s", CGI_PROCESS_PATH, szCmdType, szCmdParam);
    cmdstatus = system(cmdstr);
    if (cmdstatus < 0) {
        printf("[%s]fail\n", cmdstr);
        return false;
    }
    return true;
}

void carimpl_VideoFunc_SetAttribute(void)
{
    switch (MenuSettingConfig()->uiMOVSize)
    {
        #if (MENU_MOVIE_SIZE_4K_24P_EN)
        case MOVIE_SIZE_4K_24P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_1440_30P_EN)
        case MOVIE_SIZE_1440_30P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_30P_EN)
        case MOVIE_SIZE_SHD_30P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_SHD_25P_EN)
        case MOVIE_SIZE_SHD_25P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_60P_EN)
        case MOVIE_SIZE_1080_60P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_EN)
        case MOVIE_SIZE_1080P:
            carimpl_ExecCmdHandler("set VideoRes", "1080P30fps");
            break;
        #endif
        #if (MENU_MOVIE_SIZE_1080P_30_HDR_EN)
        case MOVIE_SIZE_1080_30P_HDR:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_900P_30P_EN)
        case MOVIE_SIZE_900P_30P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_960P_30P_EN)
        case MOVIE_SIZE_960P_30P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_720P_EN)
        case MOVIE_SIZE_720P:
            carimpl_ExecCmdHandler("set VideoRes", "720P30fps");
            break;
        #endif
        #if (MENU_MOVIE_SIZE_720_60P_EN)
        case MOVIE_SIZE_720_60P:
            break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA30P_EN)
        case MOVIE_SIZE_VGA_30P:
            break;
        #endif
        default:
            printf("Unsupported resolution/frame rate!\n");
            break;
    }
}

void carimpl_VideoFunc_StartRecording(int rec)
{
    printf("%s:%d\n",__FUNCTION__, rec);

    #if ACT_SAME_AS_CGI_CMD
        carimpl_ExecCmdHandler("set Video", "record");
    #else
    if (rec)
        Carimpl_Send2Fifo(CARDV_CMD_START_REC, sizeof(CARDV_CMD_START_REC));
    else
        Carimpl_Send2Fifo(CARDV_CMD_STOP_REC, sizeof(CARDV_CMD_STOP_REC));
    #endif
}

void carimpl_VideoFunc_Capture(void)
{
    #if ACT_SAME_AS_CGI_CMD
        carimpl_ExecCmdHandler("set Video", "capture");
    #else
        Carimpl_Send2Fifo(CARDV_CMD_CAPTURE, sizeof(CARDV_CMD_CAPTURE));
    #endif
}

void carimpl_VideoFunc_setGSensor_Sensitivity(void)
{
    switch (MenuSettingConfig()->uiGsensorSensitivity)
    {
    #if (MENU_GENERAL_POWERON_GSENSOR_OFF_EN)
    case GSENSOR_POWERON_SENSITIVITY_OFF:
        carimpl_ExecCmdHandler("set GSensor", "OFF");
        break;
    #endif
    #if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL0_EN)
    case GSENSOR_POWERON_SENSITIVITY_L0:
        carimpl_ExecCmdHandler("set GSensor", "LEVEL0");
        break;
    #endif
    #if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL1_EN)
    case GSENSOR_POWERON_SENSITIVITY_L1:
        carimpl_ExecCmdHandler("set GSensor", "LEVEL1");
        break;
    #endif
    #if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL2_EN)
    case GSENSOR_POWERON_SENSITIVITY_L2:
        carimpl_ExecCmdHandler("set GSensor", "LEVEL2");
        break;
    #endif
    default:
        break;
    }
}

void carimpl_update_status(const char *status_name, const char *status, size_t size)
{
    int fd_wr = 0;
    fd_wr = open(status_name, O_RDWR | O_CREAT, 0666);
    if (fd_wr > 0) {
        write(fd_wr, status, size);
        close(fd_wr);
    }
}

MI_S32 carimpl_process_msg(IPC_MSG_ID id, MI_S8 *param, MI_S32 paramLen)
{
    printf("[UI] msg [%d] name [%s]\n", id, EASYUICONTEXT->currentAppName());
    if (EASYUICONTEXT->currentAppName() == NULL)
        return 0;
    if(paramLen)
    	printf("[lyj]%s\n",param);// lyj add carDv process pass message

    IPC_CarInfo_Read(&carimpl);

    switch (id) {
    case IPC_MSG_UI_SD_MOUNT:
        if (strcmp(EASYUICONTEXT->currentAppName(), "browserActivity") == 0 ||
            strcmp(EASYUICONTEXT->currentAppName(), "playerActivity") == 0)
        	printf("%s--->%d\n",__FUNCTION__,__LINE__);
            Carimpl_DcfMount();
        break;
    case IPC_MSG_UI_SD_UNMOUNT:
        if (strcmp(EASYUICONTEXT->currentAppName(), "browserActivity") == 0 ||
            strcmp(EASYUICONTEXT->currentAppName(), "playerActivity") == 0) {
        	printf("%s--->%d\n",__FUNCTION__,__LINE__);
            Carimpl_DcfUnmount();
            // Carimpl_Reset();
        }
        break;
    default:
        printf("%s: a msg from CardvImpl,unsupported!\n",__FUNCTION__);
        break;
    }

    return 0;
}

void carimpl_msg_handler(struct IPCMsgBuf *pMsgBuf)
{
    carimpl_process_msg(pMsgBuf->eIPCMsgId, (MI_S8 *)pMsgBuf->s8ParamBuf, pMsgBuf->u32ParamLen);
}
