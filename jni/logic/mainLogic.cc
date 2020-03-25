#pragma once
#include "uart/ProtocolSender.h"
#include "carimpl/carimpl.h"
#include "carimpl/KeyEventContext.h"

#include <sys/vfs.h>// lyj add
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


/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{0,  500}, //定时器id=0, 时间间隔500ms
	//{1,  1000},
};

int CurPmenu = 1;
static bool bSdStatus = FALSE;

/**
 * 当界面构造时触发
 */
static void onUI_init() {
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	//LayoutPosition positon1(0,120,480,360);
	//mCameraview1Ptr->setPosition(positon1);//lyj add
	IPC_CarInfo_Open();
	IPC_CarInfo_Read(&carimpl);
	IPC_MsgToUI_Init();
	//mCameraview1Ptr->setPosition(positon1);//lyj add
	IPC_MsgToUI_RegisterMsgHandler(carimpl_msg_handler);
	IPC_MsgToUI_CreateThread();
	LOGD(" main onUI_init!\n");
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
    LOGD(" main onUI_intent!\n");
}


static void on_key_callback(int keyCode, int keyStatus) {
	//static int CurPmenu = 1;
	//printf("mainlogic %s: keyCode: %d, keyStatus: %d\n",__func__, keyCode, keyStatus);


	switch (keyStatus) {
			case keyup:

						break;
			case keydown:

			{
				static int muteFlag = 1;
				if(!muteFlag)
				{
					mTxtRecStatusPtr->setBackgroundPic("mode3/micIconm.png");

					Carimpl_Send2Fifo("audiorec 0", sizeof("audiorec 0"));
					muteFlag =1;
				}
				else
				{
					mTxtRecStatusPtr->setBackgroundPic("mode3/micIconmMute.png");

					Carimpl_Send2Fifo("audiorec 1", sizeof("audiorec 1"));
					muteFlag =0;
				}
			}
						break;
			case keyOk:
				if (IMPL_REC_STATUS == 1) {
									mBTN_RecPtr->setBackgroundPic("main_/sxt.png");
									mDuration_TXTview2Ptr->setText("00:00:00");
									//mTxtRecStatusPtr->setText("STBY");
									mTxtRecIconPtr->setBackgroundPic("");
									carimpl_VideoFunc_StartRecording(0);
								} else {
									//mTxtRecStatusPtr->setText("REC");
									carimpl_VideoFunc_StartRecording(1);
								}
						break;
			case keyMode:
				EASYUICONTEXT->openActivity("mode3TopActivity");
						break;
			case keyReturn://录像--->返回录像界面
				RecCapKey =CAP_FLAG;//mainActivity
				EASYUICONTEXT->openActivity("captureActivity");
						break;
			case keyMenu:
				EASYUICONTEXT->openActivity("VideoMenuActivity");
						break;
			default:
				break;
		}




}

/*
 * 当界面显示时触发
 */
static void onUI_show() {
	LOGD(" main onUI_show!\n");

	//register CB FUNC
	set_key_event_callback(on_key_callback);

	bSdStatus = FALSE;
	SHOW_SD_ICON(mTxtSdStatusPtr,bSdStatus);
	if (IMPL_REC_STATUS == 0) {
		//mTxtRecStatusPtr->setText("STBY");
	} else {
		//mTxtRecStatusPtr->setText("REC");
	}
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	LOGD(" main onUI_hide!\n");
}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {
	IPC_MsgToUI_DestroyThread();
	IPC_MsgToUI_DeInit();
	IPC_CarInfo_Close();
	LOGD(" main onUI_quit!\n");
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
	char str[32] = {0,};
	char str1[64] = {0,};
	time_t timep;
	struct tm *p;
	int duration;
	static int cnt = 0;
	char str2[32]={'\0'};
	static unsigned long long implSDfree =0;

	static int FreeSDG = 0;//(IMPL_SD_Free>>30);
	static int FreeSDM = 0;//(((IMPL_SD_Free>>20)%1024)/100);
	//if(FreeSDM == 10) FreeSDM =9;
	//printf("[lyj]%d\n",(int)IMPL_SD_Free);
	if(RecCapKey == 1)
	{
		if (IMPL_REC_STATUS == 1) {
					mBTN_RecPtr->setBackgroundPic("main_/sxt.png");
					mDuration_TXTview2Ptr->setText("00:00:00");
					//mTxtRecStatusPtr->setText("STBY");
					mTxtRecIconPtr->setBackgroundPic("");
					carimpl_VideoFunc_StartRecording(0);
				} else {
					//mTxtRecStatusPtr->setText("REC");
					carimpl_VideoFunc_StartRecording(1);
				}
		RecCapKey = 0;
	}

	if(bSdStatus)
	{

		  struct statfs diskInfo;
		  unsigned long long blockSize = 0;
			  statfs("/mnt/mmc", &diskInfo);
			  blockSize =  diskInfo.f_bsize;
			  implSDfree =  blockSize*diskInfo.f_bavail;//diskInfo.f_blocks  * diskInfo.f_frsize;//(diskInfo.f_bsize*diskInfo.f_bavail);

			  FreeSDG = (implSDfree>>30);
			  FreeSDM = (((implSDfree>>20)%1024)/100);
			  if(FreeSDM == 10) FreeSDM =9;

			 // printf("[lyj]%llu\n",implSDfree);
	}



	time(&timep);
	p = localtime(&timep);
	sprintf(str1, "%04d-%02d-%02d %02d:%02d:%02d", (p->tm_year + 1900), (p->tm_mon + 1), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	sprintf(str2, "%d.%dG",FreeSDG,FreeSDM);
	switch (id) {
		case 0:
			IPC_CarInfo_Read_RecInfo(&carimpl.stRecInfo);
			mTextview2Ptr->setText(str2);
			mTxtDateTimePtr->setText(str1);
			SHOW_BAT_ICON(mTxtChgStuPtr);
			SHOW_SD_ICON(mTxtSdStatusPtr, bSdStatus);

			if (IMPL_REC_STATUS) {
				duration = IMPL_REC_DURATION / 1000000;
				sprintf(str, "%02d:%02d:%02d", duration/60/60, duration/60, duration%60);
				mDuration_TXTview2Ptr->setText(str);
				mDuration_TXTview2Ptr->setTextColor(0xff0000);
				//mTxtRecStatusPtr->setText("REC");
				if (cnt++ % 2 == 0)
					mTxtRecIconPtr->setBackgroundPic("main/recstatus1.png");
				else
					mTxtRecIconPtr->setBackgroundPic("main/recstatus2.png");
			} else {
				mBTN_RecPtr->setBackgroundPic("main_/sxt.png");
				mDuration_TXTview2Ptr->setText("00:00:00");
				//mTxtRecStatusPtr->setText("STBY");
				mDuration_TXTview2Ptr->setTextColor(0xffffff);
				mTxtRecIconPtr->setBackgroundPic("");
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
static bool onmainActivityTouchEvent(const MotionEvent &ev) {
	static MotionEvent s_ev;
	bool ret = false;

    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			s_ev = ev;
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			//printf("main E_ACTION_MOVE (%d,%d)\r\n",ev.mX,ev.mY);
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			printf("main TouchEvent %d,%d\r\n",ev.mX,ev.mY);
			if (!IMPL_REC_STATUS) {
				if ((s_ev.mX > ev.mX) && ((s_ev.mX - ev.mX) > 200)) {//slide to the left
					EASYUICONTEXT->openActivity("captureActivity");
					ret = true;
				}
				else if ((abs(s_ev.mY - ev.mY) > 200)) {//slide to the up or down
					EASYUICONTEXT->openActivity("VideoMenuActivity");
					ret = true;
				}
			}

			s_ev.reset();
			break;
		default:
			break;
	}
	return ret;
}

static bool onButtonClick_BTN_WIFI(ZKButton *pButton) {
    //LOGD(" ButtonClick BTN_WIFI !!!\n");
	char path[50];
	static char u8Idx = 0;

	u8Idx++;
	if (u8Idx > 4) {
		u8Idx = 1;
	}

	sprintf(path,"wifi/wifi_signal_%d.png",u8Idx);
	mBTN_WIFIPtr->setBackgroundPic(path);
    return true;
}

static bool onButtonClick_BTN_Rec(ZKButton *pButton) {
    //LOGD(" ButtonClick BTN_Rec !!!\n");
	if (IMPL_REC_STATUS == 1) {
		mBTN_RecPtr->setBackgroundPic("main_/sxt.png");
		mDuration_TXTview2Ptr->setText("00:00:00");
		//mTxtRecStatusPtr->setText("STBY");
		mTxtRecIconPtr->setBackgroundPic("");
		carimpl_VideoFunc_StartRecording(0);
	} else {
		//mTxtRecStatusPtr->setText("REC");
		carimpl_VideoFunc_StartRecording(1);
	}
    return true;
}
static bool onButtonClick_Button1(ZKButton *pButton) {
	//LOGD(" ButtonClick BTN_Rec !!!\n");
		if (IMPL_REC_STATUS == 1) {
			mBTN_RecPtr->setBackgroundPic("main_/sxt.png");
			mDuration_TXTview2Ptr->setText("00:00:00");
			//mTxtRecStatusPtr->setText("STBY");
			mTxtRecIconPtr->setBackgroundPic("");
			carimpl_VideoFunc_StartRecording(0);
		} else {
			//mTxtRecStatusPtr->setText("REC");
			carimpl_VideoFunc_StartRecording(1);
		}
	    return true;
}
