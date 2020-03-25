#include "MenuCommon.h"

/*===========================================================================
 * Local function
 *===========================================================================*/
bool MenuItemCut(PSMENUITEM pItem);
bool MenuItemRotate(PSMENUITEM pItem);
bool MenuItemResize(PSMENUITEM pItem);
bool MenuItemTrimming(PSMENUITEM pItem);
bool MenuItemSlideShowFiles(PSMENUITEM pItem);
bool MenuItemSlideShowEffects(PSMENUITEM pItem);
bool MenuItemSlideShowMusic(PSMENUITEM pItem);
bool MenuItemVolume(PSMENUITEM pItem);
bool MenuItemPlaybackVideoType(PSMENUITEM pItem);

int   MenuGetDefault_Playback(PSMENUSTRUCT pMenu);
 /*===========================================================================
 * Extern varible
 *===========================================================================*/
extern SMENUITEM 	sItemDelete;
extern SMENUITEM 	sItemProtect;
extern SMENUITEM	sItemConfirmOne_Yes;
extern SMENUITEM	sItemConfirmOne_No;
 /*===========================================================================
 * Global variable : Menu
 *===========================================================================*/
extern SMENUSTRUCT sMainMenuPlayback;

extern SMENUSTRUCT sSubCut;
extern SMENUSTRUCT sSubRotate;
extern SMENUSTRUCT sSubResize;
extern SMENUSTRUCT sSubTrimming;
extern SMENUSTRUCT sSubSlideShowFiles;
extern SMENUSTRUCT sSubSlideShowEffects;
extern SMENUSTRUCT sSubSlideShowMusic;
extern SMENUSTRUCT sSubVolume;
extern SMENUSTRUCT sSubPlaybackVideoType;
 /*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/
// Cut
#if (MENU_PLAYBACK_QM_CUT_EN)
SMENUITEM sItemQM_Cut         		= { ITEMID_CUT,  IDS_DS_CUT,	&sSubCut, 0 };
SMENUITEM sItemQM_Cut_Yes       	= { ITEMID_CUT_YES,  IDS_DS_YES, NULL, MenuItemCut };
SMENUITEM sItemQM_Cut_No       		= { ITEMID_CUT_NO,  IDS_DS_NO,  NULL, MenuItemCut };
#endif

// Rotate
#if (MENU_PLAYBACK_ROTATE_EN)
SMENUITEM sItemRotate         		= { ITEMID_ROTATE,  IDS_DS_ROTATE,	&sSubRotate, 0 };
SMENUITEM sItemRotate_Left         	= { ITEMID_ROTATE_LEFT,    NULL,			NULL, MenuItemRotate };
SMENUITEM sItemRotate_Right      	= { ITEMID_ROTATE_RIGHT,   NULL, 			NULL, MenuItemRotate };
SMENUITEM sItemRotate_OK       		= { ITEMID_ROTATE_OK, 	   IDS_DS_OK, 		NULL, MenuItemRotate };
SMENUITEM sItemRotate_Cancel       	= { ITEMID_ROTATE_CANCEL,  IDS_DS_CANCEL, 	NULL, MenuItemRotate };
#endif

// Resize
#if (MENU_PLAYBACK_RESIZE_EN)
SMENUITEM sItemResize         		= { ITEMID_RESIZE,  IDS_DS_RESIZE,	&sSubResize, 0 };
SMENUITEM sItemResize_14M       	= { ITEMID_RESIZE_SIZE_14M,   IDS_DS_IMAGE_SIZE_14M,	NULL, MenuItemResize };
SMENUITEM sItemResize_12M       	= { ITEMID_RESIZE_SIZE_12M,   IDS_DS_IMAGE_SIZE_12M,	NULL, MenuItemResize };
SMENUITEM sItemResize_8M       		= { ITEMID_RESIZE_SIZE_8M,     IDS_DS_IMAGE_SIZE_8M,	NULL, MenuItemResize };
SMENUITEM sItemResize_5M       		= { ITEMID_RESIZE_SIZE_5M,    	IDS_DS_IMAGE_SIZE_5M,	NULL, MenuItemResize };
SMENUITEM sItemResize_3M       		= { ITEMID_RESIZE_SIZE_3M,    	IDS_DS_IMAGE_SIZE_3M,	NULL, MenuItemResize };
SMENUITEM sItemResize_2M_Wide       = { ITEMID_RESIZE_SIZE_2M,    	IDS_DS_IMAGE_SIZE_2M,	NULL, MenuItemResize };
SMENUITEM sItemResize_1_2M       	= { ITEMID_RESIZE_SIZE_1_2M,  IDS_DS_IMAGE_SIZE_1_2M,	NULL, MenuItemResize };
SMENUITEM sItemResize_VGA       	= { ITEMID_RESIZE_SIZE_VGA,    IDS_DS_IMAGE_SIZE_VGA,	NULL, MenuItemResize };
#endif

// Trimming
#if (MENU_PLAYBACK_TRIMMING_EN)
SMENUITEM sItemTrimming         	= { ITEMID_TRIMMING,  IDS_DS_TRIMMING,	&sSubTrimming, 0 };
SMENUITEM sItemTrimming_OK       	= { ITEMID_TRIMMING_OK, 	 IDS_DS_OK, 	 NULL, MenuItemTrimming };
SMENUITEM sItemTrimming_Cancel      = { ITEMID_TRIMMING_CANCEL,  IDS_DS_CANCEL, NULL, MenuItemTrimming };
#endif

// Slide Show Files
#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
SMENUITEM sItemSlideShowFiles       = { ITEMID_SLIDE_SHOW_FILES,  IDS_DS_SLIDE_SHOW_FILES,	&sSubSlideShowFiles, 0 };
#if (MENU_PLAYBACK_SLIDESHOW_FILE_ALL_EN)
SMENUITEM sItemSlideShowFiles_All   = { ITEMID_FILES_ALL,    IDS_DS_FFILES_ALL, NULL, MenuItemSlideShowFiles };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_STILL_EN)
SMENUITEM sItemSlideShowFiles_Still = { ITEMID_FILES_STILL,  IDS_DS_FILE_STILL, NULL, MenuItemSlideShowFiles };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_MOVIE_EN)
SMENUITEM sItemSlideShowFiles_Movie = { ITEMID_FILES_MOVIE, NULL, IDS_DS_FILE_MOVIE, NULL, MenuItemSlideShowFiles };
#endif
#endif

// Slide Show Effects
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
SMENUITEM sItemSlideShowEffects         	= { ITEMID_SLIDE_SHOW_EFFECTS,  IDS_DS_SLIDE_SHOW_EFFECTS,	&sSubSlideShowEffects, 0 };
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_SIMPLE_EN)
SMENUITEM sItemSlideShowEffects_Simple      = { ITEMID_SLIDE_EFFECTS_SIMPLE, 	 IDS_DS_SIMPLE, 			NULL, MenuItemSlideShowEffects };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_NOSTALGIC_EN)
SMENUITEM sItemSlideShowEffects_Nostalgic   = { ITEMID_SLIDE_EFFECTS_NOSTALGIC,  IDS_DS_EFFECTS_NOSTALGIC, NULL, MenuItemSlideShowEffects };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_STYLISH_EN)
SMENUITEM sItemSlideShowEffects_Stylish     = { ITEMID_SLIDE_EFFECTS_STYLISH, 	 IDS_DS_EFFECTS_STYLISH, 	NULL, MenuItemSlideShowEffects };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_ACTIVE_EN)
SMENUITEM sItemSlideShowEffects_Active      = { ITEMID_SLIDE_EFFECTS_ACTIVE, 	NULL, IDS_DS_EFFECTS_ACTIVE, 	NULL, MenuItemSlideShowEffects };
#endif
#endif

// Slide Show Music
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
SMENUITEM sItemSlideShowMusic       = { ITEMID_SLIDE_SHOW_MUSIC,  IDS_DS_SLIDE_SHOW_MUSIC,	&sSubSlideShowMusic, 0 };
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_ON_EN)
SMENUITEM sItemSlideShowMusic_On    = { ITEMID_MUSIC_ON,   IDS_DS_ON,  NULL, MenuItemSlideShowMusic };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_OFF_EN)
SMENUITEM sItemSlideShowMusic_Off   = { ITEMID_MUSIC_OFF,  IDS_DS_OFF, NULL, MenuItemSlideShowMusic };
#endif
#endif

// Volume
#if (MENU_PLAYBACK_VOLUME_EN)
SMENUITEM sItemVolume         		= { ITEMID_VOLUME,  IDS_DS_VOLUME,	&sSubVolume, 0 };
#if (MENU_PLAYBACK_VOLUME_LV0_EN)
SMENUITEM sItemVolume_00       		= { ITEMID_VOLUME_00,   IDS_DS_EMPTY,NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV1_EN)
SMENUITEM sItemVolume_01      		= { ITEMID_VOLUME_01,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV2_EN)
SMENUITEM sItemVolume_02       		= { ITEMID_VOLUME_02,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV3_EN)
SMENUITEM sItemVolume_03       		= { ITEMID_VOLUME_03,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV4_EN)
SMENUITEM sItemVolume_04       		= { ITEMID_VOLUME_04,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV5_EN)
SMENUITEM sItemVolume_05       		= { ITEMID_VOLUME_05,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV6_EN)
SMENUITEM sItemVolume_06       		= { ITEMID_VOLUME_06,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV7_EN)
SMENUITEM sItemVolume_07      		= { ITEMID_VOLUME_07,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV8_EN)
SMENUITEM sItemVolume_08       		= { ITEMID_VOLUME_08,   IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#if (MENU_PLAYBACK_VOLUME_LV9_EN)
SMENUITEM sItemVolume_09       		= { ITEMID_VOLUME_09,   IDS_DS_EMPTY,	NULL, MenuItemVolume };   
#endif
#if (MENU_PLAYBACK_VOLUME_LV10_EN)
SMENUITEM sItemVolume_10       		= { ITEMID_VOLUME_10,  IDS_DS_EMPTY,	NULL, MenuItemVolume };
#endif
#endif


// Video Type
#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
SMENUITEM sItemVideoType       		= { ITEMID_SHOW_VIDEO_TYPE,  IDS_DS_VIDEO_TYPE, &sSubPlaybackVideoType, 0 };
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
SMENUITEM sItemVideoTypeNormal 		= { ITEMID_VIDEO_TYPE_NORMAL,   IDS_DS_VIDEO_TYPE_NORMAL, NULL, MenuItemPlaybackVideoType };
#endif
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
SMENUITEM sItemVideoTypeParking		= { ITEMID_VIDEO_TYPE_PARKING,   IDS_DS_VIDEO_TYPE_PARKING, NULL, MenuItemPlaybackVideoType };
#endif
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
SMENUITEM sItemVideoTypeEmergency	= { ITEMID_VIDEO_TYPE_EMERGENCY,   IDS_DS_VIDEO_TYPE_EMERGENCY, NULL, MenuItemPlaybackVideoType };
#endif
#endif

 /*===========================================================================
 * Global varible : Item List
 *===========================================================================*/
#if (MENU_PLAYBACK_QM_CUT_EN)
PSMENUITEM   sMenuListCut[] =
{
    &sItemQM_Cut_Yes,
    &sItemQM_Cut_No
};
#endif

#if (MENU_PLAYBACK_ROTATE_EN)
PSMENUITEM   sMenuListRotate[] =
{
    &sItemRotate_OK,
    &sItemRotate_Cancel
};
#endif

#if (MENU_PLAYBACK_RESIZE_EN)
PSMENUITEM   sMenuListResize[] =
{
    &sItemResize_14M,
    &sItemResize_5M,
    &sItemResize_3M,
    &sItemResize_2M_Wide,
    &sItemResize_1_2M,
    &sItemResize_VGA
};
#endif

#if (MENU_PLAYBACK_TRIMMING_EN)
PSMENUITEM   sMenuListTrimming[] =
{
    &sItemTrimming_OK,
    &sItemTrimming_Cancel
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
PSMENUITEM   sMenuListSlideShowFiles[] =
{
#if (MENU_PLAYBACK_SLIDESHOW_FILE_ALL_EN)
    &sItemSlideShowFiles_All,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_STILL_EN)    
    &sItemSlideShowFiles_Still,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_MOVIE_EN)    
    &sItemSlideShowFiles_Movie
#endif    
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
PSMENUITEM   sMenuListSlideShowEffects[] =
{
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_SIMPLE_EN)
    &sItemSlideShowEffects_Simple,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_NOSTALGIC_EN)    
    &sItemSlideShowEffects_Nostalgic,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_STYLISH_EN)    
    &sItemSlideShowEffects_Stylish,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_ACTIVE_EN)    
    &sItemSlideShowEffects_Active
#endif    
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
PSMENUITEM   sMenuListSlideShowMusic[] =
{
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_ON_EN)
    &sItemSlideShowMusic_On,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_OFF_EN)    
    &sItemSlideShowMusic_Off
#endif    
};
#endif

#if (MENU_PLAYBACK_VOLUME_EN)
PSMENUITEM   sMenuListVolume[] =
{
#if (MENU_PLAYBACK_VOLUME_LV0_EN)
    &sItemVolume_00,
#endif
#if (MENU_PLAYBACK_VOLUME_LV1_EN)    
    &sItemVolume_01,
#endif
#if (MENU_PLAYBACK_VOLUME_LV2_EN)    
    &sItemVolume_02,
#endif
#if (MENU_PLAYBACK_VOLUME_LV3_EN)    
    &sItemVolume_03,
#endif
#if (MENU_PLAYBACK_VOLUME_LV4_EN)    
    &sItemVolume_04,
#endif
#if (MENU_PLAYBACK_VOLUME_LV5_EN)    
    &sItemVolume_05,
#endif
#if (MENU_PLAYBACK_VOLUME_LV6_EN)    
    &sItemVolume_06,
#endif
#if (MENU_PLAYBACK_VOLUME_LV7_EN)    
    &sItemVolume_07,
#endif
#if (MENU_PLAYBACK_VOLUME_LV8_EN)    
    &sItemVolume_08,
#endif
#if (MENU_PLAYBACK_VOLUME_LV9_EN)    
    &sItemVolume_09,    
#endif
#if (MENU_PLAYBACK_VOLUME_LV10_EN)    
    &sItemVolume_10,  
#endif
};
#endif

#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
PSMENUITEM   sMenuListVideoType[] =
{
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
    &sItemVideoTypeNormal,
#endif
#if (MENU_PLAYBACK_VIDEO_TYPE_PARKING_EN)    
    &sItemVideoTypeParking,
#endif    
#if (MENU_PLAYBACK_VIDEO_TYPE_EMERGENCY_EN)    
    &sItemVideoTypeEmergency
#endif    
};
#endif

PSMENUITEM   sMenuListEditToolConfirm[] =
{
	&sItemConfirmOne_Yes,
	&sItemConfirmOne_No
};

PSMENUITEM   sMenuListMainPlayback[] =
{
#if (MENU_PLAYBACK_VOLUME_EN)
    &sItemVolume,
#endif
#if (MENU_EDIT_DELETE_EN)    
	&sItemDelete,
#endif
#if (MENU_EDIT_PROTECT_EN)    
    &sItemProtect,
#endif    
#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
	&sItemSlideShowFiles,
#endif	
#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
	&sItemVideoType
#endif	
};
 /*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/
SMENUSTRUCT   sMainMenuPlayback =
{
    MENUID_MAIN_MENU_PLAYBACK,                                 		                                          				
    IDS_DS_PLAYBACK,                                                
    NULL,                                              				
    sizeof(sMenuListMainPlayback)/sizeof(PSMENUITEM),    			
    sMenuListMainPlayback,                                 			                                			
    NULL,                                    				                     				
};

SMENUSTRUCT   sEditToolSelectMenu =
{
    MENUID_MAIN_MENU_PLAYBACK,                                 		                                       				
    IDS_DS_PLAYBACK,                                                
    NULL,                                              				
    sizeof(sMenuListEditToolConfirm)/sizeof(PSMENUITEM),    			
    sMenuListEditToolConfirm,                                 			                           			
    NULL,                                   				                                              				
};

//--------------SUB MENU-------------------

#if (MENU_PLAYBACK_QM_CUT_EN)
SMENUSTRUCT sSubCut =
{
    MENUID_SUB_MENU_CUT,
    IDS_DS_CUT,
    &sMainMenuPlayback,
    sizeof(sMenuListCut)/sizeof(PSMENUITEM),
    sMenuListCut,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_ROTATE_EN)
SMENUSTRUCT sSubRotate =
{
    MENUID_SUB_MENU_ROTATE,
    IDS_DS_ROTATE,
    &sMainMenuPlayback,
    sizeof(sMenuListRotate)/sizeof(PSMENUITEM),
    sMenuListRotate,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_RESIZE_EN)
SMENUSTRUCT sSubResize =
{
    MENUID_SUB_MENU_RESIZE,
    IDS_DS_RESIZE,
    &sMainMenuPlayback,
    sizeof(sMenuListResize)/sizeof(PSMENUITEM),
    sMenuListResize,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_TRIMMING_EN)
SMENUSTRUCT sSubTrimming =
{
    MENUID_SUB_MENU_TRIMMING,
    IDS_DS_TRIMMING,
    &sMainMenuPlayback,
    sizeof(sMenuListTrimming)/sizeof(PSMENUITEM),
    sMenuListTrimming,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
SMENUSTRUCT sSubSlideShowFiles =
{
    MENUID_SUB_MENU_SLIDE_SHOW_FILES,
    IDS_DS_SLIDE_SHOW_FILES,
    &sMainMenuPlayback,
    sizeof(sMenuListSlideShowFiles)/sizeof(PSMENUITEM),
    sMenuListSlideShowFiles,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
SMENUSTRUCT sSubSlideShowEffects =
{
    MENUID_SUB_MENU_SLIDE_SHOW_EFFECTS,
    IDS_DS_SLIDE_SHOW_EFFECTS,
    &sMainMenuPlayback,
    sizeof(sMenuListSlideShowEffects)/sizeof(PSMENUITEM),
    sMenuListSlideShowEffects,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
SMENUSTRUCT sSubSlideShowMusic =
{
    MENUID_SUB_MENU_SLIDE_SHOW_MUSIC,
    IDS_DS_SLIDE_SHOW_MUSIC,
    &sMainMenuPlayback,
    sizeof(sMenuListSlideShowMusic)/sizeof(PSMENUITEM),
    sMenuListSlideShowMusic,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_VOLUME_EN)
SMENUSTRUCT sSubVolume =
{
    MENUID_SUB_MENU_VOLUME,
    IDS_DS_VOLUME,
    &sMainMenuPlayback,
    sizeof(sMenuListVolume)/sizeof(PSMENUITEM),
    sMenuListVolume,
    MenuGetDefault_Playback,
};
#endif

#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
SMENUSTRUCT sSubPlaybackVideoType =
{
    MENUID_SUB_MENU_VIDEO_TYPE,
    IDS_DS_VIDEO_TYPE,
    &sMainMenuPlayback,
    sizeof(sMenuListVideoType)/sizeof(PSMENUITEM),
    sMenuListVideoType,
    MenuGetDefault_Playback,
};
#endif
/*===========================================================================
 * Global variable
 *===========================================================================*/

int m_ulVolume[] = //Unit:Percent
{
#if (MENU_PLAYBACK_VOLUME_LV0_EN)
	0, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV1_EN)	
	10, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV2_EN)	
	20, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV3_EN)	
	30, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV4_EN)	
	40, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV5_EN)	
	50, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV6_EN)	
	60, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV7_EN)	
	70, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV8_EN)	
	80, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV9_EN)	
	90, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV10_EN)	
	100
#endif	
};

 /*===========================================================================
 * Main body
 *===========================================================================*/
 #if (MENU_PLAYBACK_QM_CUT_EN)
bool MenuItemCut(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_PLAYBACK_ROTATE_EN)
bool MenuItemRotate(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_PLAYBACK_RESIZE_EN)
bool MenuItemResize(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_PLAYBACK_TRIMMING_EN)
bool MenuItemTrimming(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
bool MenuItemSlideShowFiles(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiSlideShowFile = pItem->iItemId - ITEMID_SLIDE_SHOW_FILES-1;
    return true;
}
#endif

#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
bool MenuItemSlideShowEffects(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiSlideShowEffect = pItem->iItemId - ITEMID_SLIDE_SHOW_EFFECTS-1;
    return true;
}
#endif

#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
bool MenuItemSlideShowMusic(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiSlideShowMusic= pItem->iItemId - ITEMID_SLIDE_SHOW_MUSIC-1;
    return true;
}
#endif

#if (MENU_PLAYBACK_VOLUME_EN)
bool MenuItemVolume(PSMENUITEM pItem)
{
    if(pItem->iItemId - ITEMID_VOLUME == 2)//add
    {
        MenuSettingConfig()->uiVolume = sMenuListVolume[((MenuSettingConfig()->uiVolume+1 > 10)?10:MenuSettingConfig()->uiVolume+1)]->iItemId - ITEMID_VOLUME-1;
    }
    else if(pItem->iItemId - ITEMID_VOLUME == 1)//del
    {
        MenuSettingConfig()->uiVolume = sMenuListVolume[((MenuSettingConfig()->uiVolume-1 < 0)?0:MenuSettingConfig()->uiVolume-1)]->iItemId - ITEMID_VOLUME-1;
    }
    return true;
}
#endif

#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
bool MenuItemPlaybackVideoType(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiPlaybackVideoType = pItem->iItemId - ITEMID_SHOW_VIDEO_TYPE-1;
    return true;
}
#endif

int MenuGetDefault_Playback(PSMENUSTRUCT pMenu)
{
    int DefaultValue = 0;

    switch( pMenu->iMenuId )
    {
#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)  
        case MENUID_SUB_MENU_SLIDE_SHOW_FILES:
            DefaultValue = MenuSettingConfig()->uiSlideShowFile;
            break;
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)  
        case MENUID_SUB_MENU_SLIDE_SHOW_EFFECTS:
            DefaultValue = MenuSettingConfig()->uiSlideShowEffect;
            break;
#endif
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)              
        case MENUID_SUB_MENU_SLIDE_SHOW_MUSIC:
            DefaultValue = MenuSettingConfig()->uiSlideShowMusic;
            break;
#endif
#if (MENU_PLAYBACK_VOLUME_EN)            
        case MENUID_SUB_MENU_VOLUME:
            DefaultValue = MenuSettingConfig()->uiVolume*10;
            break;
#endif            
#if (MENU_PLAYBACK_VIDEO_TYPE_EN)            
        case MENUID_SUB_MENU_VIDEO_TYPE:
            DefaultValue = MenuSettingConfig()->uiPlaybackVideoType;
            break;
#endif            
    }
    return DefaultValue;
}

