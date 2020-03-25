#ifndef __DEMUX_H__
#define __DEMUX_H__

#ifdef __cplusplus
extern "C" {               // 告诉编译器下列代码要以C链接约定的模式进行链接
#endif

#ifdef SUPPORT_PLAYER_MODULE
#include "player.h"


int open_demux(player_stat_t *is);
int demux_thumbnail(char *src_filename, char *dst_filename);
int64_t demux_duration(char *src_filename);

#endif

#ifdef __cplusplus
}
#endif
#endif
