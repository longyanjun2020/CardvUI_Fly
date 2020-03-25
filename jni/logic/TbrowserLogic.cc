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


#define ICON_NUM_PER_PAGE	(6)
static bool bSdStatus = FALSE;
extern void Drawrec(int val);
//extern void upGO(void);
//extern void downGO(void)
// char g_udiskPath[256] = {0};		// udisk root path

static int FileCurNum = 0;


static void browserShowThumbByIdx1(ZKButton* pThumbPtr, char* pFileName, int idx)
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

static void browserHideThumb1(void)
{
	mButton1Ptr->setVisible(false);
	mButton2Ptr->setVisible(false);
	mButton3Ptr->setVisible(false);
	mButton4Ptr->setVisible(false);
	mButton5Ptr->setVisible(false);
	mButton6Ptr->setVisible(false);

}

static void browserShowThumb1(bool bSdStatus)
{
	unsigned int u32TotalFile = Carimpl_GetTotalFiles();
	unsigned int u32CurFileIdx = Carimpl_GetCurFileIdx();
	unsigned int u32FileIdx[ICON_NUM_PER_PAGE];
	char *pszFileName = NULL;

	browserHideThumb1();

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
					browserShowThumbByIdx1(mButton1Ptr, pszFileName, i);
				break;
				case 1:
					browserShowThumbByIdx1(mButton2Ptr, pszFileName, i);
				break;
				case 2:
					browserShowThumbByIdx1(mButton3Ptr, pszFileName, i);
				break;
				case 3:
					browserShowThumbByIdx1(mButton4Ptr, pszFileName, i);
				break;
				case 4:
					browserShowThumbByIdx1(mButton5Ptr, pszFileName, i);
				break;
				case 5:
					browserShowThumbByIdx1(mButton6Ptr, pszFileName, i);
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


static void browserShowFileInfo1(bool bSdStatus)
{
	unsigned char u8DB = Carimpl_GetCurDB();
	unsigned int u32TotalFile = Carimpl_GetTotalFiles();
	unsigned int u32CurFileIdx = Carimpl_GetCurFileIdx();
	FileCurNum = u32CurFileIdx;
	char *pszFileName = NULL;
	//char szDuration[32] = {0,};
	//int s32Duration = 0;

	if (bSdStatus && u32TotalFile > 0) {
		pszFileName = Carimpl_GetCurFileName(u32CurFileIdx);
		if (pszFileName) {
			mFilenamePtr->setText(pszFileName + strlen(SD_ROOT));
			if (u8DB != DB_PHOTO) {
				//s32Duration = Carimpl_GetFileDuration(pszFileName);
				//sprintf(szDuration, "%02d:%02d:%02d", s32Duration / 3600, (s32Duration % 3600) / 60, s32Duration % 60);
				//mTXT_FileDurPtr->setText(szDuration);
			} else {
				//mTXT_FileDurPtr->setText("");
			}
		}
	} else {
		//mTXT_FileNamePtr->setText("");
		//mTXT_FileDurPtr->setText("");
	}
}

static void browserShowPageInfo1(bool bSdStatus)
{
	char szStr[16] = {0};
	unsigned int u32TotalFile = Carimpl_GetTotalFiles();
	unsigned int u32CurFileIdx = Carimpl_GetCurFileIdx();
	unsigned int  s32CurFileIdx1 = u32CurFileIdx+1;// lyj add
	//unsigned int u32PageCnt = 0;
	//unsigned int u32CurPageIdx = 0;

	if (bSdStatus && u32TotalFile > 0) {
		//u32PageCnt = u32TotalFile / ICON_NUM_PER_PAGE + 1;
		//u32CurPageIdx = u32CurFileIdx / ICON_NUM_PER_PAGE;

		sprintf(szStr, "%d/%d", s32CurFileIdx1,u32TotalFile);
		//mTextview4Ptr->setText(szStr);
		//sprintf(szStr, "%d", u32PageCnt);
		mTextview4Ptr->setText(szStr);
	} else {
		mTextview4Ptr->setText("0/0");
		//mTXT_TotalPagePtr->setText("0");
	}
}

static void browserChangePageInfo1(bool bSdStatus, int s32Offset)
{
	int  s32TotalFile = Carimpl_GetTotalFiles();
	int  s32CurFileIdx = Carimpl_GetCurFileIdx();
	int  s32CurFileIdx1 = Carimpl_GetCurFileIdx()+1;
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
	s32CurFileIdx1 = s32CurFileIdx+1;
	s32NextPageIdx = s32CurFileIdx / ICON_NUM_PER_PAGE;
	if (s32NextPageIdx != s32CurPageIdx)
	{

		Drawrec(7);
		browserShowThumb1(bSdStatus);
	}
	s32CurFileIdx1 = Carimpl_GetCurFileIdx()+1;
		sprintf(szCurPage, "%d/%d", s32CurFileIdx1,s32TotalFile);
		mTextview4Ptr->setText(szCurPage);
		Drawrec(s32CurFileIdx % ICON_NUM_PER_PAGE);

}

static void browserShowAll1(bool bSdStatus)
{
	browserShowPageInfo1(bSdStatus);
	browserShowFileInfo1(bSdStatus);
	browserShowThumb1(bSdStatus);
}

static void browserPlay1(unsigned char u8ThumbIdx)
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
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123"); DB_NORMAL DB_PHOTO
	Carimpl_DcfUnmount();
		Carimpl_DcfMount();
		if(videoCarema ==0)
			Carimpl_SetCurFolder(DB_NORMAL, FCAM); // TODO
		else
			Carimpl_SetCurFolder(DB_PHOTO, FCAM);
		Carimpl_SetCurFileIdx(FileCurNum%6);//0
		Drawrec(FileCurNum%6);
		printf("%s\n",__FUNCTION__);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

static void on_key_callback(int keyCode, int keyStatus) {
	printf("Tbrowserlogic %s: keyCode: %d, keyStatus: %d\n",__func__, keyCode, keyStatus);

	switch (keyStatus) {
				case keyup:
					extern void upGO(int val);
							 upGO(1);
							break;
				case keydown:
					extern void downGO(int val);
							downGO(1);
							break;
				case keyOk:

							break;
				case keyMode:
					//EASYUICONTEXT->openActivity("mode3TopActivity");
							break;
				case keyReturn://录像--->返回录像界面
					//if(RecCapKey)//mainActivity
					//EASYUICONTEXT->openActivity("captureActivity");
							break;
				case keyMenu:
					EASYUICONTEXT->openActivity("mode3TopActivity");
							break;
				default:
					break;
			}

}

/*
 * 当界面显示时触发
 */
static void onUI_show() {

	set_key_event_callback(on_key_callback);

	if(videoCarema ==0)
				Carimpl_SetCurFolder(DB_NORMAL, FCAM); // TODO
			else
				Carimpl_SetCurFolder(DB_PHOTO, FCAM);

	bSdStatus = FALSE;
	//SHOW_SD_ICON(mchrstatusPtr, bSdStatus);
	SHOW_SD_ICON1(bSdStatus);
	browserShowAll1(bSdStatus);

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
static bool onUI_Timer(int id){
	bool bSdLastStatus = bSdStatus;




	switch (id) {
	case 0:
		SHOW_BAT_ICON(mchrstatusPtr);
		SHOW_SD_ICON1(bSdStatus);

		if (bSdLastStatus != bSdStatus) {
					browserShowAll1(bSdStatus);
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
static bool onTbrowserActivityTouchEvent(const MotionEvent &ev) {
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			break;
		default:
			break;
	}
	return false;
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
	browserPlay1(0);
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
    return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    //LOGD(" ButtonClick Button3 !!!\n");
    return false;
}

static bool onButtonClick_Button4(ZKButton *pButton) {
    //LOGD(" ButtonClick Button4 !!!\n");
    return false;
}

static bool onButtonClick_Button5(ZKButton *pButton) {
    //LOGD(" ButtonClick Button5 !!!\n");
    return false;
}

static bool onButtonClick_Button6(ZKButton *pButton) {
    //LOGD(" ButtonClick Button6 !!!\n");
    return false;
}

void upGO(int val)
{
	val =1;
	browserChangePageInfo1(bSdStatus, -1);
		browserShowFileInfo1(bSdStatus);
		return ;
}

void downGO(int val)
{
	val =1;
	browserChangePageInfo1(bSdStatus, 1);
		browserShowFileInfo1(bSdStatus);
		return ;
}


void Drawrec(int val)
{

	RECT Rectuse = {0,0,480,360};
	switch (val) {

		case 0:

			mPainter1Ptr->erase(&Rectuse);
			mPainter1Ptr->setLineWidth(4);
			mPainter1Ptr->setSourceColor(0xff0000);
			mPainter1Ptr->drawRect(15, 79, 146, 99, 0, 0);

					break;
		case 1:

			mPainter1Ptr->erase(&Rectuse);
			mPainter1Ptr->setLineWidth(4);
						mPainter1Ptr->setSourceColor(0xff0000);
						mPainter1Ptr->drawRect(167, 79, 146, 99, 0, 0);

					break;
		case 2:
			mPainter1Ptr->erase(&Rectuse);
			mPainter1Ptr->setLineWidth(4);
						mPainter1Ptr->setSourceColor(0xff0000);
						mPainter1Ptr->drawRect(320, 79, 146, 99, 0, 0);

					break;
		case 3:
			mPainter1Ptr->erase(&Rectuse);
			mPainter1Ptr->setLineWidth(4);
						mPainter1Ptr->setSourceColor(0xff0000);
						mPainter1Ptr->drawRect(15, 188, 146, 99, 0, 0);

					break;
		case 4:
			mPainter1Ptr->erase(&Rectuse);
			mPainter1Ptr->setLineWidth(4);
						mPainter1Ptr->setSourceColor(0xff0000);
						mPainter1Ptr->drawRect(167, 188, 146, 99, 0, 0);

					break;
		case 5:
			mPainter1Ptr->erase(&Rectuse);
			mPainter1Ptr->setLineWidth(4);
						mPainter1Ptr->setSourceColor(0xff0000);
						mPainter1Ptr->drawRect(320, 188, 146, 99, 0, 0);

					break;
		default:
			mPainter1Ptr->erase(&Rectuse);
			break;
	}


	return ;
}

