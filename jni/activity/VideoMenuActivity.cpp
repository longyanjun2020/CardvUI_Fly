/***********************************************
/gen auto by zuitools
***********************************************/
#include "VideoMenuActivity.h"

/*TAG:GlobalVariable全局变量*/
static ZKTextView* mTextview1Ptr;
static ZKWindow* mWindow1Ptr;
static ZKTextView* mmin_valuePtr;
static ZKButton* mclocksetting_okPtr;
static ZKButton* mclocksetting_delPtr;
static ZKButton* mclocksetting_addPtr;
static ZKTextView* mmin_textPtr;
static ZKTextView* mhour_textPtr;
static ZKTextView* mhour_valuePtr;
static ZKTextView* mday_textPtr;
static ZKTextView* mday_valuePtr;
static ZKTextView* mmon_textPtr;
static ZKTextView* mmon_valuePtr;
static ZKTextView* myear_textPtr;
static ZKTextView* myear_valuePtr;
static ZKWindow* mClockSettingPtr;
static ZKWindow* msubMenuClockSettingPtr;
static ZKTextView* mSetParamPtr;
static ZKButton* mIncParamPtr;
static ZKButton* mDecParamPtr;
static ZKSeekBar* mAdjustParamPtr;
static ZKWindow* mSubMenuAdjustParamPtr;
static ZKListView* msubMenuListViewPtr;
static ZKButton* mButton1Ptr;
static ZKTextView* mMenuStatusModePtr;
static ZKWindow* mMenuStatusBarPtr;
static ZKListView* mMenuListviewPtr;
static VideoMenuActivity* mActivityPtr;

/*register activity*/
REGISTER_ACTIVITY(VideoMenuActivity);

typedef struct {
	int id; // 定时器ID ， 不能重复
	int time; // 定时器  时间间隔  单位 毫秒
}S_ACTIVITY_TIMEER;

#include "logic/VideoMenuLogic.cc"

/***********/
typedef struct {
    int id;
    const char *pApp;
} SAppInfo;

/**
 *点击跳转window
 */
static SAppInfo sAppInfoTab[] = {
//  { ID_MAIN_TEXT, "TextViewActivity" },
};

/***************/
typedef bool (*ButtonCallback)(ZKButton *pButton);
/**
 * button onclick表
 */
typedef struct {
    int id;
    ButtonCallback callback;
}S_ButtonCallback;

/*TAG:ButtonCallbackTab按键映射表*/
static S_ButtonCallback sButtonCallbackTab[] = {
    ID_VIDEOMENU_clocksetting_ok, onButtonClick_clocksetting_ok,
    ID_VIDEOMENU_clocksetting_del, onButtonClick_clocksetting_del,
    ID_VIDEOMENU_clocksetting_add, onButtonClick_clocksetting_add,
    ID_VIDEOMENU_IncParam, onButtonClick_IncParam,
    ID_VIDEOMENU_DecParam, onButtonClick_DecParam,
    ID_VIDEOMENU_Button1, onButtonClick_Button1,
};
/***************/


typedef void (*SeekBarCallback)(ZKSeekBar *pSeekBar, int progress);
typedef struct {
    int id;
    SeekBarCallback callback;
}S_ZKSeekBarCallback;
/*TAG:SeekBarCallbackTab*/
static S_ZKSeekBarCallback SZKSeekBarCallbackTab[] = {
    ID_VIDEOMENU_AdjustParam, onProgressChanged_AdjustParam,
};


typedef int (*ListViewGetItemCountCallback)(const ZKListView *pListView);
typedef void (*ListViewobtainListItemDataCallback)(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index);
typedef void (*ListViewonItemClickCallback)(ZKListView *pListView, int index, int id);
typedef struct {
    int id;
    ListViewGetItemCountCallback getListItemCountCallback;
    ListViewobtainListItemDataCallback obtainListItemDataCallback;
    ListViewonItemClickCallback onItemClickCallback;
}S_ListViewFunctionsCallback;
/*TAG:ListViewFunctionsCallback*/
static S_ListViewFunctionsCallback SListViewFunctionsCallbackTab[] = {
    ID_VIDEOMENU_subMenuListView, getListItemCount_subMenuListView, obtainListItemData_subMenuListView, onListItemClick_subMenuListView,
    ID_VIDEOMENU_MenuListview, getListItemCount_MenuListview, obtainListItemData_MenuListview, onListItemClick_MenuListview,
};


typedef void (*SlideWindowItemClickCallback)(ZKSlideWindow *pSlideWindow, int index);
typedef struct {
    int id;
    SlideWindowItemClickCallback onSlideItemClickCallback;
}S_SlideWindowItemClickCallback;
/*TAG:SlideWindowFunctionsCallbackTab*/
static S_SlideWindowItemClickCallback SSlideWindowItemClickCallbackTab[] = {
};


typedef void (*EditTextInputCallback)(const std::string &text);
typedef struct {
    int id;
    EditTextInputCallback onEditTextChangedCallback;
}S_EditTextInputCallback;
/*TAG:EditTextInputCallback*/
static S_EditTextInputCallback SEditTextInputCallbackTab[] = {
};

typedef void (*VideoViewCallback)(ZKVideoView *pVideoView, int msg);
typedef struct {
    int id; //VideoView ID
    bool loop; // 是否是轮播类型
    int defaultvolume;//轮播类型时,默认视频音量
    VideoViewCallback onVideoViewCallback;
}S_VideoViewCallback;
/*TAG:VideoViewCallback*/
static S_VideoViewCallback SVideoViewCallbackTab[] = {
};


VideoMenuActivity::VideoMenuActivity() {
	//todo add init code here
	mVideoLoopIndex = -1;
	mVideoLoopErrorCount = 0;
}

VideoMenuActivity::~VideoMenuActivity() {
  //todo add init file here
  // 退出应用时需要反注册
    EASYUICONTEXT->unregisterGlobalTouchListener(this);
    onUI_quit();
    unregisterProtocolDataUpdateListener(onProtocolDataUpdate);
}

const char* VideoMenuActivity::getAppName() const{
	return "VideoMenu.ftu";
}

//TAG:onCreate
void VideoMenuActivity::onCreate() {
	Activity::onCreate();
    mTextview1Ptr = (ZKTextView*)findControlByID(ID_VIDEOMENU_Textview1);
    mWindow1Ptr = (ZKWindow*)findControlByID(ID_VIDEOMENU_Window1);
    mmin_valuePtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_min_value);
    mclocksetting_okPtr = (ZKButton*)findControlByID(ID_VIDEOMENU_clocksetting_ok);
    mclocksetting_delPtr = (ZKButton*)findControlByID(ID_VIDEOMENU_clocksetting_del);
    mclocksetting_addPtr = (ZKButton*)findControlByID(ID_VIDEOMENU_clocksetting_add);
    mmin_textPtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_min_text);
    mhour_textPtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_hour_text);
    mhour_valuePtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_hour_value);
    mday_textPtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_day_text);
    mday_valuePtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_day_value);
    mmon_textPtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_mon_text);
    mmon_valuePtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_mon_value);
    myear_textPtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_year_text);
    myear_valuePtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_year_value);
    mClockSettingPtr = (ZKWindow*)findControlByID(ID_VIDEOMENU_ClockSetting);
    msubMenuClockSettingPtr = (ZKWindow*)findControlByID(ID_VIDEOMENU_subMenuClockSetting);
    mSetParamPtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_SetParam);
    mIncParamPtr = (ZKButton*)findControlByID(ID_VIDEOMENU_IncParam);
    mDecParamPtr = (ZKButton*)findControlByID(ID_VIDEOMENU_DecParam);
    mAdjustParamPtr = (ZKSeekBar*)findControlByID(ID_VIDEOMENU_AdjustParam);if(mAdjustParamPtr!= NULL){mAdjustParamPtr->setSeekBarChangeListener(this);}
    mSubMenuAdjustParamPtr = (ZKWindow*)findControlByID(ID_VIDEOMENU_SubMenuAdjustParam);
    msubMenuListViewPtr = (ZKListView*)findControlByID(ID_VIDEOMENU_subMenuListView);if(msubMenuListViewPtr!= NULL){msubMenuListViewPtr->setListAdapter(this);msubMenuListViewPtr->setItemClickListener(this);}
    mButton1Ptr = (ZKButton*)findControlByID(ID_VIDEOMENU_Button1);
    mMenuStatusModePtr = (ZKTextView*)findControlByID(ID_VIDEOMENU_MenuStatusMode);
    mMenuStatusBarPtr = (ZKWindow*)findControlByID(ID_VIDEOMENU_MenuStatusBar);
    mMenuListviewPtr = (ZKListView*)findControlByID(ID_VIDEOMENU_MenuListview);if(mMenuListviewPtr!= NULL){mMenuListviewPtr->setListAdapter(this);mMenuListviewPtr->setItemClickListener(this);}
	mActivityPtr = this;
	onUI_init();
    registerProtocolDataUpdateListener(onProtocolDataUpdate);
}

void VideoMenuActivity::onClick(ZKBase *pBase) {
	//TODO: add widget onClik code 
    int buttonTablen = sizeof(sButtonCallbackTab) / sizeof(S_ButtonCallback);
    for (int i = 0; i < buttonTablen; ++i) {
        if (sButtonCallbackTab[i].id == pBase->getID()) {
            if (sButtonCallbackTab[i].callback((ZKButton*)pBase)) {
            	return;
            }
            break;
        }
    }


    int len = sizeof(sAppInfoTab) / sizeof(sAppInfoTab[0]);
    for (int i = 0; i < len; ++i) {
        if (sAppInfoTab[i].id == pBase->getID()) {
            EASYUICONTEXT->openActivity(sAppInfoTab[i].pApp);
            return;
        }
    }

	Activity::onClick(pBase);
}

void VideoMenuActivity::onResume() {
	Activity::onResume();
	EASYUICONTEXT->registerGlobalTouchListener(this);
    registerActivityTimer();
	startVideoLoopPlayback();
	onUI_show();
}

void VideoMenuActivity::onPause() {
	Activity::onPause();
	EASYUICONTEXT->unregisterGlobalTouchListener(this);
    unregisterActivityTimer();
	stopVideoLoopPlayback();
	onUI_hide();
}

void VideoMenuActivity::onIntent(const Intent *intentPtr) {
	Activity::onIntent(intentPtr);
	onUI_intent(intentPtr);
}

bool VideoMenuActivity::onTimer(int id) {
	return onUI_Timer(id);
}

void VideoMenuActivity::onProgressChanged(ZKSeekBar *pSeekBar, int progress){

    int seekBarTablen = sizeof(SZKSeekBarCallbackTab) / sizeof(S_ZKSeekBarCallback);
    for (int i = 0; i < seekBarTablen; ++i) {
        if (SZKSeekBarCallbackTab[i].id == pSeekBar->getID()) {
            SZKSeekBarCallbackTab[i].callback(pSeekBar, progress);
            break;
        }
    }
}

int VideoMenuActivity::getListItemCount(const ZKListView *pListView) const{
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            return SListViewFunctionsCallbackTab[i].getListItemCountCallback(pListView);
            break;
        }
    }
    return 0;
}

void VideoMenuActivity::obtainListItemData(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].obtainListItemDataCallback(pListView, pListItem, index);
            break;
        }
    }
}

void VideoMenuActivity::onItemClick(ZKListView *pListView, int index, int id){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].onItemClickCallback(pListView, index, id);
            break;
        }
    }
}

void VideoMenuActivity::onSlideItemClick(ZKSlideWindow *pSlideWindow, int index) {
    int tablen = sizeof(SSlideWindowItemClickCallbackTab) / sizeof(S_SlideWindowItemClickCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SSlideWindowItemClickCallbackTab[i].id == pSlideWindow->getID()) {
            SSlideWindowItemClickCallbackTab[i].onSlideItemClickCallback(pSlideWindow, index);
            break;
        }
    }
}

bool VideoMenuActivity::onTouchEvent(const MotionEvent &ev) {
    return onVideoMenuActivityTouchEvent(ev);
}

void VideoMenuActivity::onTextChanged(ZKTextView *pTextView, const std::string &text) {
    int tablen = sizeof(SEditTextInputCallbackTab) / sizeof(S_EditTextInputCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SEditTextInputCallbackTab[i].id == pTextView->getID()) {
            SEditTextInputCallbackTab[i].onEditTextChangedCallback(text);
            break;
        }
    }
}

void VideoMenuActivity::registerActivityTimer() {
    int tablen = sizeof(REGISTER_ACTIVITY_TIMER_TAB) / sizeof(S_ACTIVITY_TIMEER);
    for (int i = 0; i < tablen; ++i) {
        S_ACTIVITY_TIMEER temp = REGISTER_ACTIVITY_TIMER_TAB[i];
        registerTimer(temp.id, temp.time);
    }
}

void VideoMenuActivity::unregisterActivityTimer() {
    int tablen = sizeof(REGISTER_ACTIVITY_TIMER_TAB) / sizeof(S_ACTIVITY_TIMEER);
    for (int i = 0; i < tablen; ++i) {
        S_ACTIVITY_TIMEER temp = REGISTER_ACTIVITY_TIMER_TAB[i];
        unregisterTimer(temp.id);
    }
}

void VideoMenuActivity::onVideoPlayerMessage(ZKVideoView *pVideoView, int msg) {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SVideoViewCallbackTab[i].id == pVideoView->getID()) {
        	if (SVideoViewCallbackTab[i].loop) {
                //循环播放
        		videoLoopPlayback(pVideoView, msg, i);
        	} else if (SVideoViewCallbackTab[i].onVideoViewCallback != NULL){
        	    SVideoViewCallbackTab[i].onVideoViewCallback(pVideoView, msg);
        	}
            break;
        }
    }
}

void VideoMenuActivity::videoLoopPlayback(ZKVideoView *pVideoView, int msg, size_t callbackTabIndex) {

	switch (msg) {
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED\n");
    if (callbackTabIndex >= (sizeof(SVideoViewCallbackTab)/sizeof(S_VideoViewCallback))) {
      break;
    }
		pVideoView->setVolume(SVideoViewCallbackTab[callbackTabIndex].defaultvolume / 10.0);
		mVideoLoopErrorCount = 0;
		break;
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_ERROR:
		/**错误处理 */
		++mVideoLoopErrorCount;
		if (mVideoLoopErrorCount > 100) {
			LOGD("video loop error counts > 100, quit loop playback !");
            break;
		} //不用break, 继续尝试播放下一个
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED\n");
        std::vector<std::string> videolist;
        std::string fileName(getAppName());
        if (fileName.size() < 4) {
             LOGD("getAppName size < 4, ignore!");
             break;
        }
        fileName = fileName.substr(0, fileName.length() - 4) + "_video_list.txt";
        fileName = "/mnt/extsd/" + fileName;
        if (!parseVideoFileList(fileName.c_str(), videolist)) {
            LOGD("parseVideoFileList failed !");
		    break;
        }
		if (pVideoView && !videolist.empty()) {
			mVideoLoopIndex = (mVideoLoopIndex + 1) % videolist.size();
			pVideoView->play(videolist[mVideoLoopIndex].c_str());
		}
		break;
	}
}

void VideoMenuActivity::startVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		//循环播放
    		videoLoopPlayback(videoView, ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED, i);
    		return;
    	}
    }
}

void VideoMenuActivity::stopVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		if (videoView->isPlaying()) {
    		    videoView->stop();
    		}
    		return;
    	}
    }
}

bool VideoMenuActivity::parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList) {
	mediaFileList.clear();
	if (NULL == pFileListPath || 0 == strlen(pFileListPath)) {
        LOGD("video file list is null!");
		return false;
	}

	ifstream is(pFileListPath, ios_base::in);
	if (!is.is_open()) {
		LOGD("cann't open file %s \n", pFileListPath);
		return false;
	}
	char tmp[1024] = {0};
	while (is.getline(tmp, sizeof(tmp))) {
		string str = tmp;
		removeCharFromString(str, '\"');
		removeCharFromString(str, '\r');
		removeCharFromString(str, '\n');
		if (str.size() > 1) {
     		mediaFileList.push_back(str.c_str());
		}
	}
	LOGD("(f:%s, l:%d) parse fileList[%s], get [%d]files\n", __FUNCTION__,
			__LINE__, pFileListPath, mediaFileList.size());
	for (size_t i = 0; i < mediaFileList.size(); i++) {
		LOGD("file[%d]:[%s]\n", i, mediaFileList[i].c_str());
	}
	is.close();

	return true;
}

int VideoMenuActivity::removeCharFromString(string& nString, char c) {
    string::size_type   pos;
    while(1) {
        pos = nString.find(c);
        if(pos != string::npos) {
            nString.erase(pos, 1);
        } else {
            break;
        }
    }
    return (int)nString.size();
}

void VideoMenuActivity::registerUserTimer(int id, int time) {
	registerTimer(id, time);
}

void VideoMenuActivity::unregisterUserTimer(int id) {
	unregisterTimer(id);
}

void VideoMenuActivity::resetUserTimer(int id, int time) {
	resetTimer(id, time);
}