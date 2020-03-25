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

//static unsigned int gu32Pic_cunt = 0;
static bool bSdStatus = FALSE;

int RecCapKey =0;

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
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	//if(!EASYUICONTEXT->isStatusBarShow())
	//	EASYUICONTEXT->showStatusBar();
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
	printf("caplogic %s: keyCode: %d, keyStatus: %d\n",__func__, keyCode, keyStatus);

	switch (keyStatus) {
		case keyup:

					break;
		case keydown:

					break;
		case keyOk:
			carimpl_VideoFunc_Capture();
					break;
		case keyMode:
			EASYUICONTEXT->openActivity("mode3TopActivity");
					break;
		case keyReturn://录像--->返回录像界面
			RecCapKey =REC_FLAG;//mainActivity
			EASYUICONTEXT->openActivity("mainActivity");
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
	char szCnt[32] = {0,};

	IPC_CarInfo_Read_CapInfo(&carimpl.stCapInfo);
	sprintf(szCnt, "PicNum:%05d", IMPL_CAP_PICNUM);
	mpic_cuntPtr->setText(szCnt);

	//register CB FUNC
	set_key_event_callback(on_key_callback);

	bSdStatus = FALSE;
	SHOW_SD_ICON(mTxtSdStatusPtr, bSdStatus);
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	if(EASYUICONTEXT->isStatusBarShow())
		EASYUICONTEXT->hideStatusBar();
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
	char str[64] = {0};
	char str1[64] = {0};
	time_t timep;
	struct tm *p;


	if(RecCapKey ==2)// lyj add
	{

		carimpl_VideoFunc_Capture();
		RecCapKey = 0;
	}

	time(&timep);
	p = localtime(&timep);
	sprintf(str1, "%04d-%02d-%02d %02d:%02d:%02d", (p->tm_year + 1900), (p->tm_mon + 1), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

	switch (id) {
		case 0:
			IPC_CarInfo_Read_CapInfo(&carimpl.stCapInfo);

			mTxtDateTimePtr->setText(str1);
			SHOW_BAT_ICON(mTxtChgStuPtr);
			SHOW_SD_ICON(mTxtSdStatusPtr, bSdStatus);

			sprintf(str, "PicNum:%05d", IMPL_CAP_PICNUM);
			mpic_cuntPtr->setText(str);
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
static bool oncaptureActivityTouchEvent(const MotionEvent &ev) {
	static MotionEvent s_ev;
	bool ret = false;

    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			s_ev = ev;
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			//printf("cap E_ACTION_MOVE (%d,%d)\r\n",ev.mX,ev.mY);
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			if((s_ev.mX > ev.mX) && ((s_ev.mX - ev.mX) > 200)){
				//slide to the left
				EASYUICONTEXT->openActivity("browserActivity");
				//LOGD("slide to the left,enter next mode!");
				ret = true;
			}
			s_ev.reset();
			break;
		default:
			break;
	}
	return ret;
}
static bool onButtonClick_BTN_Cap(ZKButton *pButton) {
    //LOGD(" ButtonClick BTN_Cap !!!\n");
	carimpl_VideoFunc_Capture();
    return true;
}
