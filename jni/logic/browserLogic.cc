#pragma once
#include "uart/ProtocolSender.h"
#include "carimpl/carimpl.h"
#include "carimpl/KeyEventContext.h"

/*
*此文件由GUI工具生成
*文件功能：用于处理用户的逻辑相应代码
*功能说明：
*========================onButtonClick_XXXX
当页面中的按键按下后系统会调用对应的函数，XXX代表GUI工具里面的[ID值]名称，
如Button1,当返回值为false的时候系统将不再处理这个按键，返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index)
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress)
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX()
当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[ID值]名称，
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[ID值]名称，
如List1;pListItem 是贴图中的单条目对象，index是列表总目的偏移量。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mTextXXXPtr->setText("****") 在控件TextXXX上显示文字****
*mButton1Ptr->setSelected(true); 将控件mButton1设置为选中模式，图片会切换成选中图片，按钮文字会切换为选中后的颜色
*mSeekBarPtr->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1Ptr->refreshListView() 让mListView1 重新刷新，当列表数据变化后调用
*mDashbroadView1Ptr->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度
*
* 在Eclipse编辑器中  使用 “alt + /”  快捷键可以打开智能提示
*/
// #include "usbdetect.h"


#define ICON_NUM_PER_PAGE	(6)

// char g_udiskPath[256] = {0};		// udisk root path
static bool bSdStatus = FALSE;

static void browserShowThumbByIdx(ZKButton* pThumbPtr, char* pFileName, int idx)
{
	char szThumbName[16] = {0,};
	unsigned char u8DB = Carimpl_GetCurDB();

	sprintf(szThumbName, "/tmp/thumb%d.jpg", idx);
	if (u8DB == DB_PHOTO) {
		Carimpl_GetJpegFileThumbnail(pFileName, szThumbName);
	} else {
		Carimpl_GetFileThumbnail(pFileName, szThumbName);
	}
	pThumbPtr->setVisible(true);
	pThumbPtr->setBackgroundPic(szThumbName);
}

static void browserHideThumb(void)
{
	mThumb0Ptr->setVisible(false);
	mThumb1Ptr->setVisible(false);
	mThumb2Ptr->setVisible(false);
	mThumb3Ptr->setVisible(false);
	mThumb4Ptr->setVisible(false);
	mThumb5Ptr->setVisible(false);
}

static void browserShowThumb(bool bSdStatus)
{
	unsigned int u32TotalFile = Carimpl_GetTotalFiles();
	unsigned int u32CurFileIdx = Carimpl_GetCurFileIdx();
	unsigned int u32FileIdx[ICON_NUM_PER_PAGE];
	char *pszFileName = NULL;

	browserHideThumb();

	if (!bSdStatus || u32TotalFile == 0) {
		return;
	}

	u32FileIdx[0] = u32CurFileIdx / ICON_NUM_PER_PAGE * ICON_NUM_PER_PAGE;
	for (int i = 0; i < ICON_NUM_PER_PAGE; i++) {
		u32FileIdx[i] = u32FileIdx[0] + i;
		if (u32FileIdx[i] < u32TotalFile) {
			pszFileName = Carimpl_GetCurFileName(u32FileIdx[i]);
			if (pszFileName) {
				printf("idx %d : %s\n", i, pszFileName);
				switch (i) {
				case 0:
					browserShowThumbByIdx(mThumb0Ptr, pszFileName, i);
				break;
				case 1:
					browserShowThumbByIdx(mThumb1Ptr, pszFileName, i);
				break;
				case 2:
					browserShowThumbByIdx(mThumb2Ptr, pszFileName, i);
				break;
				case 3:
					browserShowThumbByIdx(mThumb3Ptr, pszFileName, i);
				break;
				case 4:
					browserShowThumbByIdx(mThumb4Ptr, pszFileName, i);
				break;
				case 5:
					browserShowThumbByIdx(mThumb5Ptr, pszFileName, i);
				break;
				default:
					printf("CHECK thumnail count\n");
				break;
				}
			}
		} else {
			break;
		}
	}
}

static void browserShowFileInfo(bool bSdStatus)
{
	unsigned char u8DB = Carimpl_GetCurDB();
	unsigned int u32TotalFile = Carimpl_GetTotalFiles();
	unsigned int u32CurFileIdx = Carimpl_GetCurFileIdx();
	char *pszFileName = NULL;
	char szDuration[32] = {0,};
	int s32Duration = 0;

	if (bSdStatus && u32TotalFile > 0) {
		pszFileName = Carimpl_GetCurFileName(u32CurFileIdx);
		if (pszFileName) {
			mTXT_FileNamePtr->setText(pszFileName + strlen(SD_ROOT));
			if (u8DB != DB_PHOTO) {
				s32Duration = Carimpl_GetFileDuration(pszFileName);
				sprintf(szDuration, "%02d:%02d:%02d", s32Duration / 3600, (s32Duration % 3600) / 60, s32Duration % 60);
				mTXT_FileDurPtr->setText(szDuration);
			} else {
				mTXT_FileDurPtr->setText("");
			}
		}
	} else {
		mTXT_FileNamePtr->setText("");
		mTXT_FileDurPtr->setText("");
	}
}

static void browserShowPageInfo(bool bSdStatus)
{
	char szStr[16] = {0};
	unsigned int u32TotalFile = Carimpl_GetTotalFiles();
	unsigned int u32CurFileIdx = Carimpl_GetCurFileIdx();
	unsigned int u32PageCnt = 0;
	unsigned int u32CurPageIdx = 0;

	if (bSdStatus && u32TotalFile > 0) {
		u32PageCnt = u32TotalFile / ICON_NUM_PER_PAGE + 1;
		u32CurPageIdx = u32CurFileIdx / ICON_NUM_PER_PAGE;

		sprintf(szStr, "%d", u32CurPageIdx + 1);
		mTXT_CurPagePtr->setText(szStr);
		sprintf(szStr, "%d", u32PageCnt);
		mTXT_TotalPagePtr->setText(szStr);
	} else {
		mTXT_CurPagePtr->setText("0");
		mTXT_TotalPagePtr->setText("0");
	}
}

static void browserChangePageInfo(bool bSdStatus, int s32Offset)
{
	int  s32TotalFile = Carimpl_GetTotalFiles();
	int  s32CurFileIdx = Carimpl_GetCurFileIdx();
	int  s32CurPageIdx = s32CurFileIdx / ICON_NUM_PER_PAGE;
	int  s32NextPageIdx = 0;
	char szCurPage[8] = {0,};

    if (!bSdStatus || s32TotalFile == 0) {
    	return;
    }

	s32CurFileIdx += s32Offset;
	if (s32CurFileIdx >= s32TotalFile) {
		s32CurFileIdx = s32CurFileIdx % s32TotalFile;
	} else if (s32CurFileIdx < 0) {
		s32CurFileIdx = s32CurFileIdx + s32TotalFile;
	}

	Carimpl_SetCurFileIdx(s32CurFileIdx);
	s32NextPageIdx = s32CurFileIdx / ICON_NUM_PER_PAGE;
	if (s32NextPageIdx != s32CurPageIdx) {
		sprintf(szCurPage, "%d", s32NextPageIdx + 1);
		mTXT_CurPagePtr->setText(szCurPage);
		browserShowThumb(bSdStatus);
	}
}

static void browserShowAll(bool bSdStatus)
{
	browserShowPageInfo(bSdStatus);
	browserShowFileInfo(bSdStatus);
	browserShowThumb(bSdStatus);
}

static void browserPlay(unsigned char u8ThumbIdx)
{
	unsigned int u32CurFileIdx = Carimpl_GetCurFileIdx();
	char *pszFileName = NULL;

	u32CurFileIdx = u32CurFileIdx / ICON_NUM_PER_PAGE * ICON_NUM_PER_PAGE + u8ThumbIdx;
	Carimpl_SetCurFileIdx(u32CurFileIdx);
	pszFileName = Carimpl_GetCurFileName(u32CurFileIdx);
	if (pszFileName) {
		// enter to player
		Intent* intent = new Intent();
		intent->putExtra("filepath", pszFileName);
		EASYUICONTEXT->openActivity("playerActivity", intent);
	}
}

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{0,  1000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};


/**
 * 当界面构造时触发
 */
static void onUI_init() {
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	Carimpl_DcfUnmount();
	Carimpl_DcfMount();
	Carimpl_SetCurFolder(DB_NORMAL, FCAM); // TODO
	Carimpl_SetCurFileIdx(0);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
    // if (0 != SSTAR_DetectUsbDev((char*)g_udiskPath, sizeof(g_udiskPath)))
    // {
	// 	LOGD("onUI_intent DetectUsbDev fail\n");
    // }
}

static void on_key_callback(int keyCode, int keyStatus) {
	printf("browserlogic %s: keyCode: %d, keyStatus: %d\n",__func__, keyCode, keyStatus);
	if(keyStatus == 2)
	{
		EASYUICONTEXT->openActivity("mainActivity");
		CurPmenu = 1;
	}
	else
	{
		browserPlay(0);
	}
}

/*
 * 当界面显示时触发
 */
static void onUI_show() {
	//register CB FUNC
	set_key_event_callback(on_key_callback);

	bSdStatus = FALSE;
	SHOW_SD_ICON(mTxtSdStatusPtr, bSdStatus);
	browserShowAll(bSdStatus);
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {

}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {

}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * 定时器触发函数
 * 不建议在此函数中写耗时操作，否则将影响UI刷新
 * 参数： id
 *         当前所触发定时器的id，与注册时的id相同
 * 返回值: true
 *             继续运行当前定时器
 *         false
 *             停止运行当前定时器
 */
static bool onUI_Timer(int id) {
	char szTime[64] = {0,};
	bool bSdLastStatus = bSdStatus;
	time_t timep;
	struct tm *p;

	time(&timep);
	p = localtime(&timep);
	sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", (p->tm_year + 1900), (p->tm_mon + 1), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

	switch (id) {
	case 0:
		mTXT_SysTimePtr->setText(szTime);
		SHOW_SD_ICON(mTxtSdStatusPtr, bSdStatus);
		if (bSdLastStatus != bSdStatus) {
			browserShowAll(bSdStatus);
		}
		break;
	default:
		break;
	}
    return true;
}

/**
 * 有新的触摸事件时触发
 * 参数：ev
 *         新的触摸事件
 * 返回值：true
 *            表示该触摸事件在此被拦截，系统不再将此触摸事件传递到控件上
 *         false
 *            触摸事件将继续传递到控件上
 */
static bool onbrowserActivityTouchEvent(const MotionEvent &ev) {
	static MotionEvent s_ev;
	bool ret = false;

    switch (ev.mActionStatus) {
	case MotionEvent::E_ACTION_DOWN://触摸按下
		//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
		s_ev = ev;
		break;
	case MotionEvent::E_ACTION_MOVE://触摸滑动
		break;
	case MotionEvent::E_ACTION_UP:  //触摸抬起
		if ((s_ev.mX > ev.mX) && ((s_ev.mX - ev.mX) > 80)) {
			//slide to the left
			EASYUICONTEXT->openActivity("mainActivity");
			ret = true;
		}
		s_ev.reset();
		break;
	default:
		break;
	}
	return ret;
}

static bool onButtonClick_BTN_Up(ZKButton *pButton) {
	browserChangePageInfo(bSdStatus, -1);
	browserShowFileInfo(bSdStatus);
    return true;
}

static bool onButtonClick_BTN_Down(ZKButton *pButton) {
	browserChangePageInfo(bSdStatus, 1);
	browserShowFileInfo(bSdStatus);
    return true;
}

static bool onButtonClick_Thumb0(ZKButton *pButton) {
    //LOGD(" ButtonClick Thumb0 !!!\n");
	browserPlay(0);
    return true;
}

static bool onButtonClick_Thumb1(ZKButton *pButton) {
    //LOGD(" ButtonClick Thumb1 !!!\n");
	browserPlay(1);
    return true;
}

static bool onButtonClick_Thumb2(ZKButton *pButton) {
    //LOGD(" ButtonClick Thumb2 !!!\n");
	browserPlay(2);
    return true;
}

static bool onButtonClick_Thumb3(ZKButton *pButton) {
    //LOGD(" ButtonClick Thumb3 !!!\n");
	browserPlay(3);
    return true;
}

static bool onButtonClick_Thumb4(ZKButton *pButton) {
    //LOGD(" ButtonClick Thumb4 !!!\n");
	browserPlay(4);
    return true;
}

static bool onButtonClick_Thumb5(ZKButton *pButton) {
    //LOGD(" ButtonClick Thumb5 !!!\n");
	browserPlay(5);
    return true;
}
