/*
 * Carimpl.h
 *
 *  Created on: 2019-10-10
 *      Author: lei.qin
 */

#ifndef _CARDV_IMPL_H_
#define _CARDV_IMPL_H_

#include <stdint.h>
#include "usbdetect.h"
#include "mi_common_datatype.h"
#include "IPC_msg.h"
#include "IPC_cardvInfo.h"
#include "DCF.h"

#ifndef BYTE
typedef unsigned char   BYTE;
#endif
#ifndef UINT
typedef unsigned int    UINT;
#endif
#ifndef UINT16
typedef unsigned short  UINT16;
#endif

#define FIFO_NAME                           "/tmp/cardv_fifo"
#define REC_STATUS                          "/tmp/rec_status"
#define MMC_STATUS                          "/tmp/mmc_status"
#define CGI_PROCESS_PATH                    "/customer/wifi/webserver/www/CGI_PROCESS.sh"

#define CARDV_CMD_STOP_REC                  "rec 0"
#define CARDV_CMD_START_REC                 "rec 1"
#define CARDV_CMD_EMERG_REC                 "rec 2"
#define CARDV_CMD_CAPTURE                   "capture"
#define CARDV_CMD_START_PREVIEW             "disp start"
#define CARDV_CMD_STOP_PREVIEW              "disp stop"

#define SHOW_BAT_ICON(PTR)                           \
{                                                    \
    static char u8Idx = 0;                           \
    char str[32] = {0};                              \
    u8Idx++;                                         \
    if (u8Idx > 3) {                                 \
        u8Idx = 1;                                   \
        sprintf(str, "charge/%d-battery.png", 5);    \
    } else if(u8Idx == 2) {                          \
        sprintf(str, "charge/%d-battery.png", 7);    \
    } else {                                         \
        sprintf(str, "charge/%d-battery.png", 10);   \
    }                                                \
    PTR->setBackgroundPic(str);                      \
}                                                    \

#define SHOW_SD_ICON(PTR, bSdStatus)                 \
{                                                    \
    IPC_CarInfo_Read_SdInfo(&carimpl.stSdInfo);      \
    if (!bSdStatus && IMPL_SD_ISMOUNT) {             \
        bSdStatus = TRUE;                            \
        PTR->setBackgroundPic("mode3/SD.png");  \
        LOGD("SD mount,show icon\n");                \
    } else if (bSdStatus && !IMPL_SD_ISMOUNT) {      \
        bSdStatus = FALSE;                           \
        PTR->setBackgroundPic("mode3/SDno.png");                   \
        LOGD("SD unmount,hide icon\n");              \
    }                                                \
}                                                    \
/*lyj define*/
#define SHOW_SD_ICON1(bSdStatus)                 \
{                                                    \
    IPC_CarInfo_Read_SdInfo(&carimpl.stSdInfo);      \
    if (!bSdStatus && IMPL_SD_ISMOUNT) {             \
        bSdStatus = TRUE;                            \
        LOGD("SD mount,show icon\n");                \
    } else if (bSdStatus && !IMPL_SD_ISMOUNT) {      \
        bSdStatus = FALSE;                           \
        LOGD("SD unmount,hide icon\n");              \
    }                                                \
}                                                    \

/*******************************************************/
/*******************************************************/
extern int CurPmenu;
extern CarDV_Info carimpl;
#define IMPL_REC_STATUS     (carimpl.stRecInfo.bMuxing)
#define IMPL_REC_DURATION   (carimpl.stRecInfo.u32CurDuration)
#define IMPL_SD_ISMOUNT     (carimpl.stSdInfo.bStorageMount)
#define IMPL_CAP_PICNUM     (carimpl.stCapInfo.u32FileCnt)

//lyj define
#define IMPL_SD_Free     (carimpl.stSdInfo.u64FreeSize)
#define IMPL_SD_Total     (carimpl.stSdInfo.u64TotalSize)

unsigned int Carimpl_GetTotalFiles(unsigned char u8DB, unsigned char u8CamId);
unsigned int Carimpl_GetTotalFiles(void);
unsigned int Carimpl_GetCurFileIdx(unsigned char u8DB, unsigned char u8CamId);
unsigned int Carimpl_GetCurFileIdx(void);
char* Carimpl_GetCurFileName(unsigned char u8DB, unsigned char u8CamId, unsigned int u32FileIdx);
char* Carimpl_GetCurFileName(unsigned int u32FileIdx);
bool Carimpl_SetCurFileIdx(unsigned char u8DB, unsigned char u8CamId, unsigned int u32FileIdx);
bool Carimpl_SetCurFileIdx(unsigned int u32FileIdx);
bool Carimpl_SetCurFolder(unsigned char u8DB, unsigned char u8CamId);
unsigned char Carimpl_GetCurDB(void);
unsigned int Carimpl_GetFileDuration(char *pFileName);
unsigned int Carimpl_GetFileThumbnail(char *pFileName, char *pThumbFileName);
unsigned int Carimpl_GetJpegFileThumbnail(char *pFileName, char *pThumbFileName);
void Carimpl_Send2Fifo(const void *cmd, size_t size);
void carimpl_VideoFunc_StartRecording(int rec);
void carimpl_VideoFunc_Capture(void);
void carimpl_update_status(const char *status_name, const char *status, size_t size);
void carimpl_VideoFunc_SetAttribute(void);
void carimpl_msg_handler(struct IPCMsgBuf *pMsgBuf);
int Carimpl_DcfMount(void);
int Carimpl_DcfUnmount(void);

#endif /* _CARDV_IMPL_H_ */
