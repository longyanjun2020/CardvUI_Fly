#pragma once
#include "uart/ProtocolSender.h"
#include "carimpl/MenuCommon.h"
#include <sstream>
#include <sys/time.h>
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

static int Datetime[6] = {2019,01,01,12,0,0};//year,month,day,hour,minute
static int _idexex= 0;
//static int SubMenuInterface = 0;
static PSMENUSTRUCT pCurrentMenu = NULL;
static PSMENUITEM   pCurItem 	 = NULL;
static ZKListView::ZKListSubItem* long_sub;// lyj add
static int subMenuFlag =0;
static PSMENUSTRUCT MenuPageList[] =
{
#if (MENU_MOVIE_PAGE_EN)
    &sMainMenuVideo,
#endif
#if (MENU_STILL_PAGE_EN)
    &sMainMenuStill,
#endif
#if (MENU_PLAYBACK_PAGE_EN)
    &sMainMenuPlayback,
#endif
#if (MENU_MEDIA_PAGE_EN)
    &sMainMenuMedia,
#endif
#if (MENU_GENERAL_PAGE_EN)
    &sMainMenuGeneral,
#endif
};

static PSMENUSTRUCT GetNextCatagoryMenu(PSMENUSTRUCT pMenu)
{
    unsigned int i, Next;

    for(i=0; i<MENU_PAGE_NUM; i++)
    {
        if(pMenu->iMenuId==MenuPageList[i]->iMenuId)
        {
            Next = ((i+1)==MENU_PAGE_NUM)?(0):(i+1);
            return (MenuPageList[Next]);
        }
    }

    return &sMainMenuVideo;
}

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};


extern void VideoMenuupDown(void);
extern void obtainListItemData_subMenuListViewEx(int SelectVal);
extern void obtainListItemData_subMenuListViewExDo(void);
extern void onListItemClick_MenuListviewEx(int select);

static void on_key_callback(int keyCode, int keyStatus) {

	//printf("Menulogic %s: keyCode: %d, keyStatus: %d\n",__func__, keyCode, keyStatus);

#if 1
	switch (keyStatus) {
				case keyup:
					 if(_idexex == 26 && msubMenuClockSettingPtr->isVisible())
					{
							extern  bool onButtonClick_clocksetting_add1(ZKButton *pButton);
							onButtonClick_clocksetting_add1(mclocksetting_delPtr);
					}
					 else
					obtainListItemData_subMenuListViewEx(0);
							break;
				case keydown:
					if(_idexex == 26 && msubMenuClockSettingPtr->isVisible())
					{
						extern  bool onButtonClick_clocksetting_del1(ZKButton *pButton);
						onButtonClick_clocksetting_del1(mclocksetting_addPtr);
					}
					else
					obtainListItemData_subMenuListViewEx(1);
							break;
				case keyOk:
					onListItemClick_MenuListviewEx(1);//确认键   5
							break;
				case keyMode:
					//EASYUICONTEXT->openActivity("mode3TopActivity");
					if(msubMenuClockSettingPtr->isVisible())
					{
						extern bool onButtonClick_clocksetting_ok1(ZKButton *pButton);
						onButtonClick_clocksetting_ok1(mclocksetting_okPtr);
					}
							break;
				case keyReturn://录像--->返回录像界面
					//if(RecCapKey)//mainActivity
					//EASYUICONTEXT->openActivity("captureActivity");
					onListItemClick_MenuListviewEx(4);
							break;
				case keyMenu:
					EASYUICONTEXT->openActivity("mainActivity");
							break;
				default:
					break;
			}

#endif
}


/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	pCurrentMenu = &sMainMenuVideo;

		mMenuListviewPtr->setSelection(_idexex/5*5);// lyj add
			// mMenuListviewPtr->setSelected(_idexex);
			// mMenuListviewPtr->refreshListView();

}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * 当界面显示时触发
 */
static void onUI_show() {
	if(EASYUICONTEXT->isStatusBarShow())
		EASYUICONTEXT->hideStatusBar();

	set_key_event_callback(on_key_callback);
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
	switch (id) {

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
static bool onVideoMenuActivityTouchEvent(const MotionEvent &ev) {
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
			if((s_ev.mX > ev.mX) && ((s_ev.mX - ev.mX) > 80)){//slide to the left
				pCurrentMenu = GetNextCatagoryMenu(pCurrentMenu);
				printf("Slide Menu %s\n", MAP_STRINGID(pCurrentMenu->iStringId));
				mMenuStatusModePtr->setText(MAP_STRINGID(pCurrentMenu->iStringId));
				mMenuListviewPtr->refreshListView();
				ret = true;
			}

			s_ev.reset();
			break;
		default:
			break;
	}
	return ret;
}

void VideoMenuupDown(void)// lyj add
{
	pCurrentMenu = GetNextCatagoryMenu(pCurrentMenu);
					printf("Slide Menu %s\n", MAP_STRINGID(pCurrentMenu->iStringId));
					mMenuStatusModePtr->setText(MAP_STRINGID(pCurrentMenu->iStringId));
					mMenuListviewPtr->refreshListView();

}

static int getListItemCount_MenuListview(const ZKListView *pListView) {
    //LOGD("getListItemCount_MenuListview !\n");
	//printf("Current Menu Count=%d\n", pCurrentMenu->iNumOfItems);
    return pCurrentMenu->iNumOfItems;
}

static void obtainListItemData_MenuListview(ZKListView *pListView,ZKListView::ZKListItem  *pListItem, int index) {
   // printf(" obtainListItemData_ MenuListview  index == %d !!!\n",index);
	ZKListView::ZKListSubItem* sub = NULL;
	char NumBuf[12]={'\0'};
	unsigned int indexadd = _idexex + 1;
	//index = (_idexex%5)*5;// lyj add
	//if(index ==0 && _idexex !=0)
		//index = _idexex;
	sub = pListItem->findSubItemByID(ID_VIDEOMENU_MenuItemKey);
	//long_sub = sub;// lyj add
	//indexadd = _idexex + 1;
	sprintf(NumBuf,"%d/%d",indexadd,mMenuListviewPtr->getListItemCount());
	mMenuStatusModePtr->setText(NumBuf);
	if (sub) {
		sub->setText(MAP_STRINGID(pCurrentMenu->pItemsList[index]->pSubMenu->iStringId));
		if(_idexex == index)// lyj add
					{
						//sub->setTextColor(0x0000ff);
						sub->setBackgroundColor(0x0000ff);
						//printf("show UI 33\n");
					}
					else
					{

						sub->setBackgroundColor(0x151615);
					}
	}
	sub = pListItem->findSubItemByID(ID_VIDEOMENU_MenuItemVaule);
	long_sub = sub;// lyj add
	if (sub) {
		int CurValue = 0;
		PSMENUITEM pItem = pCurrentMenu->pItemsList[index];
		//printf("show UI 66666666666666666\n");
		if(pItem->pSubMenu->pfMenuGetDefaultVal)
		{
			CurValue = pItem->pSubMenu->pfMenuGetDefaultVal(pItem->pSubMenu);
#if 0
			if(sub->isSelected())// lyj add
						{
							sub->setTextColor(0x0000ff);
							printf("show UI\n");
						}
#endif
		}
		else {
			sub->setText(MAP_STRINGID(IDS_DS_EMPTY));
#if 0
			if(_idexex == index && SubMenuInterface){
				printf("show UI 777777777777\n");
				SubMenuInterface =0;
				obtainListItemData_subMenuListViewExDo();// lyj
			}
#endif
			return;
		}
		if(pItem->iItemId == ITEMID_VOLUME ||
				pItem->iItemId == ITEMID_CONTRAST ||
				pItem->iItemId == ITEMID_SATURATION ||
				pItem->iItemId == ITEMID_SHARPNESS ||
				pItem->iItemId == ITEMID_GAMMA) {
			sub->setText(CurValue);
			 printf(" obtainListItemData_ MenuListview 11-->%d !!!\n",_idexex);
			if(_idexex == index)// lyj add
			{
				//sub->setTextColor(0x0000ff);
				sub->setBackgroundColor(0x0000ff);
				printf("show UI 1\n");
			}
			else
			{

				sub->setBackgroundColor(0x151615);
			}
		}
		else {
			// printf(" obtainListItemData_ MenuListview 222--->%d !!!\n",_idexex);
			sub->setText(MAP_STRINGID(pCurrentMenu->pItemsList[index]->pSubMenu->pItemsList[CurValue]->iStringId));
			if(_idexex == index)// lyj add
			{
				//sub->setTextColor(0x0000ff);
				if(pItem->iItemId != ITEMID_FORMAT_SD_CARD||\
				   pItem->iItemId != ITEMID_CLOCK_SETTINGS||\
				   pItem->iItemId != ITEMID_GPS_INFO_CHART)
				{
				//sub->setBackgroundColor(0xff8000);
					if(subMenuFlag ==1)
						sub->setBackgroundColor(0xff8000);
					else if(subMenuFlag ==0)
						sub->setBackgroundColor(0x0000ff);
					else if(subMenuFlag ==2)
					{
						int subMenuNum = pCurrentMenu->pItemsList[index]->pSubMenu->iNumOfItems;
						// sub menu add following
						if(CurValue == 0 || CurValue < (subMenuNum-1))
						{
							CurValue++;
							//MenuSetDefault_Movie();
							 printf(" down down  !!!\n");
							 //pItem->pSubMenu->pItemsList[index]->iItemId++;
								if(pItem->pSubMenu->pItemsList[CurValue]->pfItemSelectHandler != NULL)
									pItem->pSubMenu->pItemsList[CurValue]->pfItemSelectHandler(pItem->pSubMenu->pItemsList[CurValue]);
						}
						else if(CurValue == subMenuNum-1)
						{
							//pItem->pSubMenu->pItemsList[index]->iItemId -= CurValue;
							CurValue=0;
							if(pItem->pSubMenu->pItemsList[CurValue]->pfItemSelectHandler != NULL)
								pItem->pSubMenu->pItemsList[CurValue]->pfItemSelectHandler(pItem->pSubMenu->pItemsList[CurValue]);

						}
						printf("[CurValue]==%d----[subMenuNum]==%d\n",CurValue,subMenuNum);
						sub->setText(MAP_STRINGID(pCurrentMenu->pItemsList[index]->pSubMenu->pItemsList[CurValue]->iStringId));
						sub->setBackgroundColor(0xff8000);
					}
					else if(subMenuFlag ==3)
					{
						int subMenuNum = pCurrentMenu->pItemsList[index]->pSubMenu->iNumOfItems;
						// sub menu add following
						if(CurValue <= (subMenuNum-1) && CurValue >= 0)
						{
							CurValue--;
							 printf(" up up up up  !!!\n");
							 if(CurValue < 0)
								 CurValue = subMenuNum-1;
								if(pItem->pSubMenu->pItemsList[CurValue]->pfItemSelectHandler != NULL)
									pItem->pSubMenu->pItemsList[CurValue]->pfItemSelectHandler(pItem->pSubMenu->pItemsList[CurValue]);
						}

						printf("[CurValue]==%d----[subMenuNum]==%d\n",CurValue,subMenuNum);
						sub->setText(MAP_STRINGID(pCurrentMenu->pItemsList[index]->pSubMenu->pItemsList[CurValue]->iStringId));
						sub->setBackgroundColor(0xff8000);

					}
				}
				//printf("show UI 2\n");
			}
			else
			{
				sub->setBackgroundColor(0x151615);

			}
		}
	}

}

//lyj add
void obtainListItemData_subMenuListViewEx(int SelectVal)
{
	//printf("id---> %d\n", mMenuListviewPtr->getFirstVisibleItemIndex());
	if(SelectVal)// down
	{
		if(!subMenuFlag)// lyj add
		{
			_idexex++;// getListItemCount
			if(_idexex >= mMenuListviewPtr->getListItemCount())
				_idexex = 0;
			//printf("id---> %d\n", _idexex);
			//obtainListItemData_MenuListview(mMenuListviewPtr,mMenuListviewPtr->mListItemPtr,mMenuListviewPtr->getFirstVisibleItemIndex());
			//mMenuListviewPtr->setSelection(_idexex);
			//mMenuListviewPtr->IItemClickListener(mMenuListviewPtr,1,1);
			mMenuListviewPtr->setSelected(_idexex);
			if(_idexex%5 == 0)
				mMenuListviewPtr->setSelection(_idexex);
		}
		else // subMenu down
		{

			subMenuFlag =2;
			if(_idexex <2)
			{
				mMenuListviewPtr->refreshListView();
			 mMenuListviewPtr->setSelected(_idexex);
			}

			else

				mMenuListviewPtr->setSelected(_idexex);
		}

	}
	else// up
	{
		if(!subMenuFlag)// lyj add
				{
					_idexex--;// getListItemCount
					if(_idexex < 0)
						_idexex = mMenuListviewPtr->getListItemCount()-1;
					//printf("id---> %d\n", _idexex);
					//obtainListItemData_MenuListview(mMenuListviewPtr,mMenuListviewPtr->mListItemPtr,mMenuListviewPtr->getFirstVisibleItemIndex());
					//mMenuListviewPtr->setSelection(_idexex);
					//mMenuListviewPtr->IItemClickListener(mMenuListviewPtr,1,1);
					if(_idexex ==1)
					{
						mMenuListviewPtr->refreshListView();
						 mMenuListviewPtr->setSelected(_idexex);
					}
					else
						mMenuListviewPtr->setSelected(_idexex);
					if((_idexex+1)%5 == 0)
					{
						//mMenuListviewPtr->refreshListView();
						mMenuListviewPtr->setSelection(_idexex/5*5);
					}
					else if(_idexex == (mMenuListviewPtr->getListItemCount() -1))
					{
						mMenuListviewPtr->setSelection(24);
					}
				}
				else // subMenu down
				{

					subMenuFlag =3;
					if(_idexex <2)
					{
						mMenuListviewPtr->refreshListView();
					 mMenuListviewPtr->setSelected(_idexex);
					}

					else
						mMenuListviewPtr->setSelected(_idexex);
				}


	}

	//mMenuListviewPtr->mItemPressInfo.index = _idexex;
	//mMenuListviewPtr->setVisible(1);
	//mMenuListviewPtr->setAnimatable(1);
	//mMenuListviewPtr->setPressed(1);
	//mMenuListviewPtr->setBackgroundColor(0x0000ff); 整个背景都
}


static void onListItemClick_MenuListview(ZKListView *pListView, int index, int id) {
    //printf(" onListItemClick_ MenuListview  !!!\n");
	pCurItem = pCurrentMenu->pItemsList[index];
	if(pCurItem->iItemId == ITEMID_VOLUME ||
			pCurItem->iItemId == ITEMID_CONTRAST ||
			pCurItem->iItemId == ITEMID_SATURATION ||
			pCurItem->iItemId == ITEMID_SHARPNESS ||
			pCurItem->iItemId == ITEMID_GAMMA) {
		if(pCurItem->pSubMenu->pfMenuGetDefaultVal != NULL) {
			int CurValue = 0;
			CurValue = pCurItem->pSubMenu->pfMenuGetDefaultVal(pCurItem->pSubMenu);
			mSubMenuAdjustParamPtr->setVisible(true);
			mSetParamPtr->setText(CurValue);
#if 0
			if(_idexex == index)// lyj add
			{
				//sub->setTextColor(0x0000ff);
				mSetParamPtr->setBackgroundColor(0x0000ff);
				printf("show UI front\n");
			}
			else
			{
				//printf("show UI front\n");
				mSetParamPtr->setBackgroundColor(0x050905);
			}
#endif
		}
	}
	else if(pCurItem->iItemId == ITEMID_CLOCK_SETTINGS) {
		msubMenuClockSettingPtr->setVisible(true);
		myear_valuePtr->setText(Datetime[IDX_YEAR]);
		mmon_valuePtr->setText(Datetime[IDX_MONTH]);
		mday_valuePtr->setText(Datetime[IDX_DAY]);
		mhour_valuePtr->setText(Datetime[IDX_HOUR]);
		mmin_valuePtr->setText(Datetime[IDX_MIN]);
		myear_valuePtr->setSelected(true);
		mmon_valuePtr->setSelected(false);
		mday_valuePtr->setSelected(false);
		mhour_valuePtr->setSelected(false);
		mmin_valuePtr->setSelected(false);
	}
	else
		msubMenuListViewPtr->setVisible(true);
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
	//EASYUICONTEXT->closeActivity("VideoMenuActivity");
	if(msubMenuListViewPtr->isVisible()) {
		msubMenuListViewPtr->setVisible(false);
	}
	else if(mSubMenuAdjustParamPtr->isVisible()) {
		mSubMenuAdjustParamPtr->setVisible(false);
	}
	else if(msubMenuClockSettingPtr->isVisible()) {
		msubMenuClockSettingPtr->setVisible(false);
	}
	else {
		Menu_WriteSetting();
		EASYUICONTEXT->goBack();
	}
    return false;
}// return 键
static int getListItemCount_subMenuListView(const ZKListView *pListView) {
   // printf("getListItemCount_subMenuListView !\n");
	return pCurItem->pSubMenu->iNumOfItems;
}

static void obtainListItemData_subMenuListView(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
   // printf(" obtainListItemData_ subMenuListView  !!!\n");
	ZKListView::ZKListSubItem* sub = NULL;

	sub = pListItem->findSubItemByID(ID_VIDEOMENU_SubItem);
	if (sub) {
		if(pCurItem->pSubMenu) {
			sub->setText(MAP_STRINGID(pCurItem->pSubMenu->pItemsList[index]->iStringId));
			if(pCurItem->pSubMenu->pfMenuGetDefaultVal != NULL) {
				if(index == pCurItem->pSubMenu->pfMenuGetDefaultVal(pCurItem->pSubMenu))
					sub->setPressed(true);
				else
					sub->setPressed(false);
			}
		}
	}
}// 猜测 ok键

void onListItemClick_MenuListviewEx(int select)
{
	/*
	 * 1 表示 选中 显示橘色
	 * 2向上选中
	 * 3下选中
	 * 4ok 运行处理函数并取消橘色显示
	 * */

	//  printf("%s-->%d\n",__FUNCTION__,__LINE__);

	 // pCurItem = pCurrentMenu->pItemsList[index];
	 // PSMENUITEM pItem = pCurrentMenu->pItemsList[_idexex];
	 // int ItemNum = pItem->pSubMenu->iNumOfItems;

	 // int CurValue = pItem->pSubMenu->pfMenuGetDefaultVal(pItem->pSubMenu);
	 // mMenuListviewPtr->ZKListItem->findSubItemByID(ID_VIDEOMENU_MenuItemVaule);
	//  long_sub->setText(MAP_STRINGID(pCurrentMenu->pItemsList[index]->pSubMenu->pItemsList[pItem->pSubMenu->pfMenuGetDefaultVal(pItem->pSubMenu)]->iStringId));
	 // long_sub->setBackgroundColor(0xff8000);

	  switch (select) {
		case 1:
#if 0
			long_sub->setBackgroundColor(0xff8000);
#endif
			if(subMenuFlag == 0)
			{
				subMenuFlag = 1;
				if(_idexex <2)
				{
					mMenuListviewPtr->refreshListView();
					mMenuListviewPtr->setSelected(_idexex);
				}
				else
				{
					if(_idexex==27 ||\
						_idexex==26 ||\
						_idexex==25)
						//SubMenuInterface =1;
						obtainListItemData_subMenuListViewExDo();// lyj
					else
					mMenuListviewPtr->setSelected(_idexex);
				}
				//subMenuFlag =0;
			}
			else if(subMenuFlag)
			{
				if(_idexex <2)
				{
					mMenuListviewPtr->refreshListView();
					mMenuListviewPtr->setSelected(_idexex);
				}
				else
				{
					if(_idexex==27 ||\
						_idexex==26 ||\
						_idexex==25)
						//SubMenuInterface =1;
						obtainListItemData_subMenuListViewExDo();// lyj
					else
					mMenuListviewPtr->setSelected(_idexex);
				}
				subMenuFlag =0;
			}
			break;
		case 2:
#if 0
			if(CurValue < ItemNum-1)
				CurValue++;
			else if(CurValue >= ItemNum-1)
				CurValue =0;
			long_sub->setText(MAP_STRINGID(pCurrentMenu->pItemsList[_idexex]->pSubMenu->pItemsList[CurValue]->iStringId));
#endif
			break;
		case 3:
#if 0
			if(CurValue < (ItemNum-1) && CurValue > 0)
							CurValue--;
						else if(CurValue == 0)
							CurValue =ItemNum -1;
			long_sub->setText(MAP_STRINGID(pCurrentMenu->pItemsList[_idexex]->pSubMenu->pItemsList[CurValue]->iStringId));
#endif
			break;
		case 4:
#if 1
			long_sub->setBackgroundColor(0x0000ff);
			//printf(" onListItemClick_ subMenuListView  !!!\n");
				if(pCurItem->pSubMenu->pItemsList[_idexex]->pfItemSelectHandler != NULL)
					pCurItem->pSubMenu->pItemsList[_idexex]->pfItemSelectHandler(pCurItem->pSubMenu->pItemsList[_idexex]);
#endif
			break;
		default:
			printf("choose error!\n");
			break;
	}


}//lyj add

void obtainListItemData_subMenuListViewExDo(void)// lyj add
{
	//printf("%s,%d\n",__FUNCTION__,__LINE__);
	//msubMenuListViewPtr->setPressed(true);
	if(!msubMenuListViewPtr->isVisible() &&!mSubMenuAdjustParamPtr->isVisible()&&\
			!msubMenuClockSettingPtr->isVisible()) {
		//mMenuListviewPtr->setVisible(false);

	//msubMenuListViewPtr->setVisible(true);
	onListItemClick_MenuListview(mMenuListviewPtr,_idexex,1);
	}
	else
	{

		onButtonClick_Button1(mButton1Ptr);
	}
}



static void onListItemClick_subMenuListView(ZKListView *pListView, int index, int id) {
    printf(" onListItemClick_ subMenuListView  !!!\n");
	if(pCurItem->pSubMenu->pItemsList[index]->pfItemSelectHandler != NULL)
		pCurItem->pSubMenu->pItemsList[index]->pfItemSelectHandler(pCurItem->pSubMenu->pItemsList[index]);
}
static void onProgressChanged_AdjustParam(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged AdjustParam %d !!!\n", progress);
	//mSetParamPtr->setText(progress);
	//pSeekBar->setProgress(progress);
}

static bool onButtonClick_DecParam(ZKButton *pButton) {
    //LOGD(" ButtonClick DecParam !!!\n");
	int iPreprogress = mAdjustParamPtr->getProgress();
	mAdjustParamPtr->setProgress(((iPreprogress - 10)>0?(iPreprogress - 10):0));
	mSetParamPtr->setText(((iPreprogress - 10)>0?(iPreprogress - 10):0));
	if(pCurItem->pSubMenu->pItemsList[0]->pfItemSelectHandler != NULL)
		pCurItem->pSubMenu->pItemsList[0]->pfItemSelectHandler(pCurItem->pSubMenu->pItemsList[0]);
    return false;
}

static bool onButtonClick_IncParam(ZKButton *pButton) {
    //LOGD(" ButtonClick IncParam !!!\n");
	int iPreprogress = mAdjustParamPtr->getProgress();
	mAdjustParamPtr->setProgress(((iPreprogress + 10)>100?100:iPreprogress + 10));
	mSetParamPtr->setText(((iPreprogress + 10)>100?100:iPreprogress + 10));
	if(pCurItem->pSubMenu->pItemsList[1]->pfItemSelectHandler != NULL)
		pCurItem->pSubMenu->pItemsList[1]->pfItemSelectHandler(pCurItem->pSubMenu->pItemsList[1]);
    return false;
}

static int Check_Validate_ClockSetting(int* pDatetime, int ubCheckType)
{
	int Year,Month,Day,Hour,Min,Sec;

	Year  = *(pDatetime+IDX_YEAR);
	Month = *(pDatetime+IDX_MONTH);
	Day   = *(pDatetime+IDX_DAY);
	Hour  = *(pDatetime+IDX_HOUR);
	Min   = *(pDatetime+IDX_MIN);
	Sec   = *(pDatetime+IDX_SEC);

	//Check Year
	if(ubCheckType & CHECK_YEAR) {
		if(Year > RTC_MAX_YEAR) {
			*(pDatetime+IDX_YEAR) = RTC_MIN_YEAR;
		}
		else if(Year < RTC_MIN_YEAR) {
			*(pDatetime+IDX_YEAR) = RTC_MAX_YEAR;
		}
		if( ((Year %4 == 0) && (Year %100 != 0)) || ( Year %400 == 0)) {//Leap Year
			if( Month == 2 && Day == 28 ) {
				*(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_LEAP_YEAR;
			}
		}
		else {
			if( Month == 2 && Day == 29 ) {
				*(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_NONLEAP_YEAR;
			}
		}
	}
	//Check Month
	if(ubCheckType & CHECK_MONTH) {
		if(Month > RTC_MAX_MONTH) {
			*(pDatetime+IDX_MONTH) = RTC_MIN_MONTH;
		}
		else if(Month < RTC_MIN_MONTH) {
			*(pDatetime+IDX_MONTH) = RTC_MAX_MONTH;
		}
		if(Month == 2){
			if( ((Year %4 == 0) && (Year %100 != 0)) || ( Year %400 == 0)) {//Leap Year
				if(Day == 30 || Day == 31) {
					*(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_LEAP_YEAR;
				}
			}
			else {
				if(Day == 29 || Day == 30 || Day == 31) {
					*(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_NONLEAP_YEAR;
				}
			}
		}
		else if(Month == 4 || Month == 6 || Month == 9 || Month == 11) {
			if(Day == 31) {
				*(pDatetime+IDX_DAY) = RTC_MAX_DAY_30;
			}
		}
		//printf("[lyj--month]%02d\n",*(pDatetime+IDX_MONTH));
	}
	//Check Day
	if(ubCheckType & CHECK_DAY) {
		if(Month==1  || Month==3 || Month==5 || Month==7 || Month==8 || Month==10 || Month==12) {
			if(Day >RTC_MAX_DAY_31) {
				*(pDatetime+IDX_DAY) = RTC_MIN_DAY;
			}
			else if(Day < RTC_MIN_DAY) {
				*(pDatetime+IDX_DAY) = RTC_MAX_DAY_31;
			}
		}

		if(Month==4 || Month==6 || Month==9 || Month==11) {
			if(Day >RTC_MAX_DAY_30) {
				*(pDatetime+IDX_DAY) = RTC_MIN_DAY;
			}
			else if(Day < RTC_MIN_DAY) {
					*(pDatetime+IDX_DAY) = RTC_MAX_DAY_30;
			}
		}

		if(Month==2) {
			if( ((Year %4 == 0) && (Year %100 != 0)) || ( Year %400 == 0)) {//Leap Year
				if(Day >RTC_MAX_DAY_FEB_LEAP_YEAR) {
					*(pDatetime+IDX_DAY) = RTC_MIN_DAY;
				}
				else if(Day < RTC_MIN_DAY) {
					*(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_LEAP_YEAR;
				}
			}
			else {
				if(Day >RTC_MAX_DAY_FEB_NONLEAP_YEAR) {
					*(pDatetime+IDX_DAY) = RTC_MIN_DAY;
				}
				else if(Day < RTC_MIN_DAY) {
					*(pDatetime+IDX_DAY) = RTC_MAX_DAY_FEB_NONLEAP_YEAR;
				}
			}
		}
	}
	 //Check Hour
	if(ubCheckType & CHECK_HOUR) {
		if(Hour > RTC_MAX_HOUR) {
			*(pDatetime+IDX_HOUR) = RTC_MIN_HOUR;
		}
		else if(Hour < RTC_MIN_HOUR) {
			*(pDatetime+IDX_HOUR) = RTC_MAX_HOUR;
		}
		//printf("[lyj--hour]%02d",*(pDatetime+IDX_HOUR));
	}
	//Check Minute
	if(ubCheckType & CHECK_MIN) {
		if(Min > RTC_MAX_MIN) {
			*(pDatetime+IDX_MIN) = RTC_MIN_MIN;
		}
		else if(Min < RTC_MIN_MIN) {
			*(pDatetime+IDX_MIN) = RTC_MAX_MIN;
		}
	}
	//Check Second
	if(ubCheckType & CHECK_SEC) {
		if(Sec > RTC_MAX_SEC) {
			*(pDatetime+IDX_SEC) = RTC_MIN_SEC;
		}
		else if(Sec < RTC_MIN_SEC) {
			*(pDatetime+IDX_SEC) = RTC_MAX_SEC;
		}
	}
	return CHECK_PASS;
}

int SetRtcTime(int* pDatetime)
{
    struct tm RtcTm;
    struct timeval tv;
    time_t timep;

    RtcTm.tm_sec = *(pDatetime+IDX_SEC);
    RtcTm.tm_min = *(pDatetime+IDX_MIN);
    RtcTm.tm_hour = *(pDatetime+IDX_HOUR);
    RtcTm.tm_mday = *(pDatetime+IDX_DAY);
    RtcTm.tm_mon = *(pDatetime+IDX_MONTH)-1;// lyj change
    RtcTm.tm_year = *(pDatetime+IDX_YEAR) - 1900;

    timep = mktime(&RtcTm);
    tv.tv_sec = timep;
    tv.tv_usec = 0;
    if(settimeofday(&tv, (struct timezone *) 0) < 0) {
    	printf("Set rtc datatime error!\n");
    	return -1;
    }
    return 0;
}

static bool onButtonClick_clocksetting_add(ZKButton *pButton) {
    //LOGD(" ButtonClick clocksetting_add !!!\n");
	string str = "";
	if(myear_valuePtr->isSelected()){
		str = myear_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_YEAR];
		Datetime[IDX_YEAR] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_YEAR);
		myear_valuePtr->setText(Datetime[IDX_YEAR]);
	}
	else if(mmon_valuePtr->isSelected()){
		str = mmon_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MONTH];
		Datetime[IDX_MONTH] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_MONTH);
		mmon_valuePtr->setText(Datetime[IDX_MONTH]);
	}
	else if(mday_valuePtr->isSelected()){
		str = mday_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_DAY];
		Datetime[IDX_DAY] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_DAY);
		mday_valuePtr->setText(Datetime[IDX_DAY]);
	}
	else if(mhour_valuePtr->isSelected()){
		str = mhour_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MONTH];
		Datetime[IDX_HOUR] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_HOUR);
		mhour_valuePtr->setText(Datetime[IDX_HOUR]);
	}
	else if(mmin_valuePtr->isSelected()){
		str = mmin_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MIN];
		Datetime[IDX_MIN] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_MIN);
		mmin_valuePtr->setText(Datetime[IDX_MIN]);
	}
    return false;
}

static bool onButtonClick_clocksetting_del(ZKButton *pButton) {
    //LOGD(" ButtonClick clocksetting_del !!!\n");
	string str = "";
	if(myear_valuePtr->isSelected()){
		str = myear_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_YEAR];
		Datetime[IDX_YEAR] -= 1;
		Check_Validate_ClockSetting(Datetime, CHECK_YEAR);
		myear_valuePtr->setText(Datetime[IDX_YEAR]);
	}
	else if(mmon_valuePtr->isSelected()){
		str = mmon_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MONTH];
		Datetime[IDX_MONTH] -= 1;

		Check_Validate_ClockSetting(Datetime, CHECK_MONTH);
		mmon_valuePtr->setText(Datetime[IDX_MONTH]);
	}
	else if(mday_valuePtr->isSelected()){
		str = mday_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_DAY];
		Datetime[IDX_DAY] -= 1;
		Check_Validate_ClockSetting(Datetime, CHECK_DAY);
		mday_valuePtr->setText(Datetime[IDX_DAY]);
	}
	else if(mhour_valuePtr->isSelected()){
		str = mhour_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MONTH];
		Datetime[IDX_HOUR] -= 1;
		Check_Validate_ClockSetting(Datetime, CHECK_HOUR);
		mhour_valuePtr->setText(Datetime[IDX_HOUR]);
	}
	else if(mmin_valuePtr->isSelected()){
		str = mmin_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MIN];
		Datetime[IDX_MIN] -= 1;
		Check_Validate_ClockSetting(Datetime, CHECK_MIN);
		mmin_valuePtr->setText(Datetime[IDX_MIN]);
	}
    return false;
}

static bool onButtonClick_clocksetting_ok(ZKButton *pButton) {
    //LOGD(" ButtonClick clocksetting_ok !!!\n");
	if(myear_valuePtr->isSelected()) {
		myear_valuePtr->setSelected(false);
		mmon_valuePtr->setSelected(true);
	}
	else if(mmon_valuePtr->isSelected()) {
		mmon_valuePtr->setSelected(false);
		mday_valuePtr->setSelected(true);
	}
	else if(mday_valuePtr->isSelected()) {
		mday_valuePtr->setSelected(false);
		mhour_valuePtr->setSelected(true);
	}
	else if(mhour_valuePtr->isSelected()) {
		mhour_valuePtr->setSelected(false);
		mmin_valuePtr->setSelected(true);
	}
	else if(mmin_valuePtr->isSelected()) {
		mmin_valuePtr->setSelected(false);
		myear_valuePtr->setSelected(true);
		SetRtcTime(Datetime);
		msubMenuClockSettingPtr->setVisible(false);
	}
    return false;
}


 bool onButtonClick_clocksetting_add1(ZKButton *pButton) {
    //LOGD(" ButtonClick clocksetting_add !!!\n");
	string str = "";
	if(myear_valuePtr->isSelected()){
		str = myear_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_YEAR];
		Datetime[IDX_YEAR] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_YEAR);
		myear_valuePtr->setText(Datetime[IDX_YEAR]);
	}
	else if(mmon_valuePtr->isSelected()){
		str = mmon_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MONTH];
		Datetime[IDX_MONTH] += 1;
		//printf("[lyj--month0]%02d\n",*(Datetime+IDX_MONTH));
		Check_Validate_ClockSetting(Datetime, CHECK_MONTH);
		mmon_valuePtr->setText(Datetime[IDX_MONTH]);
	}
	else if(mday_valuePtr->isSelected()){
		str = mday_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_DAY];
		Datetime[IDX_DAY] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_DAY);
		mday_valuePtr->setText(Datetime[IDX_DAY]);
	}
	else if(mhour_valuePtr->isSelected()){
		str = mhour_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_HOUR];// 这里写错了
		Datetime[IDX_HOUR] += 1;
		//printf("[lyj--month2]%02d\n",*(Datetime+IDX_MONTH));
		Check_Validate_ClockSetting(Datetime, CHECK_HOUR);
		mhour_valuePtr->setText(Datetime[IDX_HOUR]);
	}
	else if(mmin_valuePtr->isSelected()){
		str = mmin_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MIN];
		Datetime[IDX_MIN] += 1;
		Check_Validate_ClockSetting(Datetime, CHECK_MIN);
		mmin_valuePtr->setText(Datetime[IDX_MIN]);
	}
    return false;
}

 bool onButtonClick_clocksetting_del1(ZKButton *pButton) {
    //LOGD(" ButtonClick clocksetting_del !!!\n");
	string str = "";
	if(myear_valuePtr->isSelected()){
		str = myear_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_YEAR];
		Datetime[IDX_YEAR] -= 1;
		Check_Validate_ClockSetting(Datetime, CHECK_YEAR);
		myear_valuePtr->setText(Datetime[IDX_YEAR]);
	}
	else if(mmon_valuePtr->isSelected()){
		str = mmon_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MONTH];
		if(Datetime[IDX_MONTH] > 12)
			Datetime[IDX_MONTH] = 1;// lyj add
		Datetime[IDX_MONTH] -= 1;
		//printf("[lyj--month0]%02d\n",*(Datetime+IDX_MONTH));
		Check_Validate_ClockSetting(Datetime, CHECK_MONTH);
		mmon_valuePtr->setText(Datetime[IDX_MONTH]);
	}
	else if(mday_valuePtr->isSelected()){
		str = mday_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_DAY];
		Datetime[IDX_DAY] -= 1;
		Check_Validate_ClockSetting(Datetime, CHECK_DAY);
		mday_valuePtr->setText(Datetime[IDX_DAY]);
	}
	else if(mhour_valuePtr->isSelected()){
		str = mhour_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_HOUR];
		Datetime[IDX_HOUR] -= 1;
		//printf("[lyj--month1]%02d\n",*(Datetime+IDX_MONTH));
		Check_Validate_ClockSetting(Datetime, CHECK_HOUR);
		mhour_valuePtr->setText(Datetime[IDX_HOUR]);
	}
	else if(mmin_valuePtr->isSelected()){
		str = mmin_valuePtr->getText();
		istringstream(str)>>Datetime[IDX_MIN];
		Datetime[IDX_MIN] -= 1;
		Check_Validate_ClockSetting(Datetime, CHECK_MIN);
		mmin_valuePtr->setText(Datetime[IDX_MIN]);
	}
    return false;
}

 int SetRtcTime1(int* pDatetime)
 {
#if 1
     struct tm RtcTm;
     struct timeval tv;
     time_t timep;

     RtcTm.tm_sec = *(pDatetime+IDX_SEC);
     RtcTm.tm_min = *(pDatetime+IDX_MIN);
     RtcTm.tm_hour = *(pDatetime+IDX_HOUR);
     RtcTm.tm_mday = *(pDatetime+IDX_DAY);
     RtcTm.tm_mon = *(pDatetime+IDX_MONTH)-1;// lyj change
     RtcTm.tm_year = *(pDatetime+IDX_YEAR) - 1900;

     timep = mktime(&RtcTm);
     tv.tv_sec = timep;
     tv.tv_usec = 0;
     if(settimeofday(&tv, (struct timezone *) 0) < 0) {
     	printf("Set rtc datatime error!\n");
     	return -1;
     }
#else
     char Timecharator[31] = {0};
     //int mYear = (*(pDatetime+IDX_YEAR))%2000;
     /*sprintf(Timecharator, "date %02d%02d%02d%02d%02d",*(pDatetime+IDX_MONTH),\
    		 *(pDatetime+IDX_DAY),*(pDatetime+IDX_HOUR),*(pDatetime+IDX_MIN),\
			 mYear);*/


     printf("[lyj]%04d-%02d-%02d %02d:%02d:%02d\n",*(pDatetime+IDX_YEAR),*(pDatetime+IDX_MONTH),\
     		 *(pDatetime+IDX_DAY),*(pDatetime+IDX_HOUR),*(pDatetime+IDX_MIN),\
			 *(pDatetime+IDX_SEC));

     if(*(pDatetime+IDX_MONTH) > 12)
    	 *(pDatetime+IDX_MONTH) -= 12;

     sprintf(Timecharator, "date -s \"%04d-%02d-%02d %02d:%02d:%02d\"",*(pDatetime+IDX_YEAR),*(pDatetime+IDX_MONTH),\
         		 *(pDatetime+IDX_DAY),*(pDatetime+IDX_HOUR),*(pDatetime+IDX_MIN),\
				 *(pDatetime+IDX_SEC));
     //strcat(Timecharator, ".50");
     const char *Timesetting = Timecharator;
     printf("[time]==%s\n",Timesetting);
    // usleep(100);
     //if(execl("/bin/ls", "ls", "-al", NULL) < 0) {
               //perror("error");
    	// printf("error setting time \n");
       // }

     	 system(Timesetting);
     usleep(10000);
#endif
     return 0;

 }


 bool onButtonClick_clocksetting_ok1(ZKButton *pButton) {
    //LOGD(" ButtonClick clocksetting_ok !!!\n");
	if(myear_valuePtr->isSelected()) {
		myear_valuePtr->setSelected(false);
		mmon_valuePtr->setSelected(true);
		printf("[lyj1]%04d-%02d-%02d %02d:%02d:%02d\n",*(Datetime+IDX_YEAR),*(Datetime+IDX_MONTH),\
		     		 *(Datetime+IDX_DAY),*(Datetime+IDX_HOUR),*(Datetime+IDX_MIN),\
					 *(Datetime+IDX_SEC));
	}
	else if(mmon_valuePtr->isSelected()) {
		mmon_valuePtr->setSelected(false);
		mday_valuePtr->setSelected(true);
		printf("[lyj2]%04d-%02d-%02d %02d:%02d:%02d\n",*(Datetime+IDX_YEAR),*(Datetime+IDX_MONTH),\
				     		 *(Datetime+IDX_DAY),*(Datetime+IDX_HOUR),*(Datetime+IDX_MIN),\
							 *(Datetime+IDX_SEC));
	}
	else if(mday_valuePtr->isSelected()) {
		mday_valuePtr->setSelected(false);
		mhour_valuePtr->setSelected(true);
		printf("[lyj3]%04d-%02d-%02d %02d:%02d:%02d\n",*(Datetime+IDX_YEAR),*(Datetime+IDX_MONTH),\
				     		 *(Datetime+IDX_DAY),*(Datetime+IDX_HOUR),*(Datetime+IDX_MIN),\
							 *(Datetime+IDX_SEC));
	}
	else if(mhour_valuePtr->isSelected()) {
		mhour_valuePtr->setSelected(false);
		mmin_valuePtr->setSelected(true);
		printf("[lyj4]%04d-%02d-%02d %02d:%02d:%02d\n",*(Datetime+IDX_YEAR),*(Datetime+IDX_MONTH),\
				     		 *(Datetime+IDX_DAY),*(Datetime+IDX_HOUR),*(Datetime+IDX_MIN),\
							 *(Datetime+IDX_SEC));
	}
	else if(mmin_valuePtr->isSelected()) {
		mmin_valuePtr->setSelected(false);
		myear_valuePtr->setSelected(true);
		printf("[lyj5]%04d-%02d-%02d %02d:%02d:%02d\n",*(Datetime+IDX_YEAR),*(Datetime+IDX_MONTH),\
				     		 *(Datetime+IDX_DAY),*(Datetime+IDX_HOUR),*(Datetime+IDX_MIN),\
							 *(Datetime+IDX_SEC));
		SetRtcTime1(Datetime);
		msubMenuClockSettingPtr->setVisible(false);
		subMenuFlag =0;
	}
    return false;
}

