/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __VIDEOMENUACTIVITY_H__
#define __VIDEOMENUACTIVITY_H__


#include "app/Activity.h"
#include "entry/EasyUIContext.h"

#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"

#include "utils/Log.h"
#include "control/ZKDigitalClock.h"
#include "control/ZKButton.h"
#include "control/ZKCircleBar.h"
#include "control/ZKDiagram.h"
#include "control/ZKListView.h"
#include "control/ZKPointer.h"
#include "control/ZKQRCode.h"
#include "control/ZKTextView.h"
#include "control/ZKSeekBar.h"
#include "control/ZKEditText.h"
#include "control/ZKVideoView.h"
#include "window/ZKSlideWindow.h"

/*TAG:Macro宏ID*/
#define ID_VIDEOMENU_Textview1    50013
#define ID_VIDEOMENU_Window1    110005
#define ID_VIDEOMENU_min_value    50011
#define ID_VIDEOMENU_clocksetting_ok    20009
#define ID_VIDEOMENU_clocksetting_del    20008
#define ID_VIDEOMENU_clocksetting_add    20007
#define ID_VIDEOMENU_min_text    50012
#define ID_VIDEOMENU_hour_text    50010
#define ID_VIDEOMENU_hour_value    50009
#define ID_VIDEOMENU_day_text    50008
#define ID_VIDEOMENU_day_value    50007
#define ID_VIDEOMENU_mon_text    50006
#define ID_VIDEOMENU_mon_value    50005
#define ID_VIDEOMENU_year_text    50004
#define ID_VIDEOMENU_year_value    50003
#define ID_VIDEOMENU_ClockSetting    110004
#define ID_VIDEOMENU_subMenuClockSetting    110003
#define ID_VIDEOMENU_SetParam    50001
#define ID_VIDEOMENU_IncParam    20006
#define ID_VIDEOMENU_DecParam    20005
#define ID_VIDEOMENU_AdjustParam    91001
#define ID_VIDEOMENU_SubMenuAdjustParam    110002
#define ID_VIDEOMENU_SubItem    20004
#define ID_VIDEOMENU_subMenuListView    80002
#define ID_VIDEOMENU_Button1    20003
#define ID_VIDEOMENU_MenuStatusMode    50002
#define ID_VIDEOMENU_MenuStatusBar    110001
#define ID_VIDEOMENU_MenuItemVaule    20002
#define ID_VIDEOMENU_MenuItemKey    20001
#define ID_VIDEOMENU_MenuListview    80001
/*TAG:Macro宏ID END*/

class VideoMenuActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    VideoMenuActivity();
    virtual ~VideoMenuActivity();

    /**
     * 注册定时器
     */
	void registerUserTimer(int id, int time);
	/**
	 * 取消定时器
	 */
	void unregisterUserTimer(int id);
	/**
	 * 重置定时器
	 */
	void resetUserTimer(int id, int time);

protected:
    /*TAG:PROTECTED_FUNCTION*/
    virtual const char* getAppName() const;
    virtual void onCreate();
    virtual void onClick(ZKBase *pBase);
    virtual void onResume();
    virtual void onPause();
    virtual void onIntent(const Intent *intentPtr);
    virtual bool onTimer(int id);

    virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress);

    virtual int getListItemCount(const ZKListView *pListView) const;
    virtual void obtainListItemData(ZKListView *pListView, ZKListView::ZKListItem *pListItem, int index);
    virtual void onItemClick(ZKListView *pListView, int index, int subItemIndex);

    virtual void onSlideItemClick(ZKSlideWindow *pSlideWindow, int index);

    virtual bool onTouchEvent(const MotionEvent &ev);

    virtual void onTextChanged(ZKTextView *pTextView, const string &text);

    void registerActivityTimer();
    void unregisterActivityTimer();

    virtual void onVideoPlayerMessage(ZKVideoView *pVideoView, int msg);
    void videoLoopPlayback(ZKVideoView *pVideoView, int msg, size_t callbackTabIndex);
    void startVideoLoopPlayback();
    void stopVideoLoopPlayback();
    bool parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList);
    int removeCharFromString(string& nString, char c);


private:
    /*TAG:PRIVATE_VARIABLE*/
    int mVideoLoopIndex;
    int mVideoLoopErrorCount;

};

#endif