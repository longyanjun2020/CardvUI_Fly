#include "MenuCommon.h"

/*===========================================================================
 * Local function
 *===========================================================================*/
bool MenuItemStillImageSize(PSMENUITEM pItem);
bool MenuItemStillQuality(PSMENUITEM pItem);
bool MenuItemStillStable(PSMENUITEM pItem);
bool MenuItemFlash(PSMENUITEM pItem);
bool MenuItemFlashLevel(PSMENUITEM pItem);
bool MenuItemRedEyeReduc(PSMENUITEM pItem);
bool MenuItemSelfTimer(PSMENUITEM pItem);
bool MenuItemBurstCapture(PSMENUITEM pItem);
bool MenuItemVMDShotNum(PSMENUITEM pItem);
bool MenuItemTimeLapseInterval(PSMENUITEM pItem);

int   MenuGetDefault_Camera(PSMENUSTRUCT pMenu);

/*===========================================================================
 * Extern varible
 *===========================================================================*/
extern SMENUITEM    sItemScence;
extern SMENUITEM    sItemEV;
extern SMENUITEM    sItemWB;
extern SMENUITEM    sItemISO;
extern SMENUITEM    sItemColor;
extern SMENUITEM    sItemEffect;
extern SMENUITEM    sItemContrast;
extern SMENUITEM    sItemSaturation;
extern SMENUITEM    sItemSharpness;
extern SMENUITEM    sItemGamma;
 
 /*===========================================================================
 * Global variable : Menu
 *===========================================================================*/
extern SMENUSTRUCT	sMainMenuStill;
extern SMENUSTRUCT sSubStillImageSize;
extern SMENUSTRUCT sSubStillQuality;

/*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/
 // Still Image Size
#if (MENU_STILL_SIZE_EN)
SMENUITEM sItemStillImageSize          = { ITEMID_STILL_IMAGE_SIZE, 	IDS_DS_STILL_IMAGE_SIZE,	&sSubStillImageSize, 0 };
#if (MENU_STILL_SIZE_30M_EN)
SMENUITEM sItemStillImageSize_30M      = { ITEMID_IMAGE_SIZE_30M, 	IDS_DS_IMAGE_SIZE_30M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_14M_EN)
SMENUITEM sItemStillImageSize_14M      = { ITEMID_IMAGE_SIZE_14M, 	IDS_DS_IMAGE_SIZE_14M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_12M_EN)
SMENUITEM sItemStillImageSize_12M      = { ITEMID_IMAGE_SIZE_12M, 	IDS_DS_IMAGE_SIZE_12M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_8M_EN)
SMENUITEM sItemStillImageSize_8M       = { ITEMID_IMAGE_SIZE_8M,  	IDS_DS_IMAGE_SIZE_8M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_5M_EN)
SMENUITEM sItemStillImageSize_5M       = { ITEMID_IMAGE_SIZE_5M,  	IDS_DS_IMAGE_SIZE_5M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_3M_EN)
SMENUITEM sItemStillImageSize_3M       = { ITEMID_IMAGE_SIZE_3M,  	IDS_DS_IMAGE_SIZE_3M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_2M_WIDE_EN)
SMENUITEM sItemStillImageSize_2M_Wide  = { ITEMID_IMAGE_SIZE_2M,   	IDS_DS_IMAGE_SIZE_2M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_1d2M_EN)
SMENUITEM sItemStillImageSize_1_2M     = { ITEMID_IMAGE_SIZE_1_2M, 	IDS_DS_IMAGE_SIZE_1_2M,	NULL, MenuItemStillImageSize };
#endif
#if (MENU_STILL_SIZE_VGA_EN)
SMENUITEM sItemStillImageSize_VGA      = { ITEMID_IMAGE_SIZE_VGA, 	IDS_DS_IMAGE_SIZE_VGA,	NULL, MenuItemStillImageSize };
#endif
#endif

// Still Quality
#if (MENU_STILL_QUALITY_EN)
SMENUITEM sItemStillQuality            = { ITEMID_STILL_QUALITY, IDS_DS_STILL_QUALITY,	&sSubStillQuality, 0 };
#if (MENU_STILL_QUALITY_SUPER_FINE_EN)
SMENUITEM sItemStillQuality_Super_Fine = { ITEMID_SQUALITY_SUPERFINE, IDS_DS_QUALITY_SUPERFINE,	NULL, MenuItemStillQuality };
#endif
#if (MENU_STILL_QUALITY_FINE_EN)
SMENUITEM sItemStillQuality_Fine       = { ITEMID_SQUALITY_FINE,  IDS_DS_QUALITY_FINE, 		NULL, MenuItemStillQuality };
#endif
#endif
/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/
 #if (MENU_STILL_SIZE_EN)
PSMENUITEM   sMenuListStillImageSize[] =
{
#if (MENU_STILL_SIZE_30M_EN)
    &sItemStillImageSize_30M,
#endif
#if (MENU_STILL_SIZE_14M_EN)
    &sItemStillImageSize_14M,
#endif
#if (MENU_STILL_SIZE_12M_EN)
    &sItemStillImageSize_12M,
#endif
#if (MENU_STILL_SIZE_8M_EN)
    &sItemStillImageSize_8M,
#endif
#if (MENU_STILL_SIZE_5M_EN)
    &sItemStillImageSize_5M,
#endif
#if (MENU_STILL_SIZE_3M_EN)
    &sItemStillImageSize_3M,
#endif
#if (MENU_STILL_SIZE_2M_WIDE_EN)
    &sItemStillImageSize_2M_Wide,
#endif
#if (MENU_STILL_SIZE_1d2M_EN)
    &sItemStillImageSize_1_2M,
#endif
#if (MENU_STILL_SIZE_VGA_EN)
    &sItemStillImageSize_VGA
#endif
};
#endif

#if (MENU_STILL_QUALITY_EN)
PSMENUITEM   sMenuListStillQuality[] =
{
#if (MENU_STILL_QUALITY_SUPER_FINE_EN)
    &sItemStillQuality_Super_Fine,
#endif
#if (MENU_STILL_QUALITY_FINE_EN)
    &sItemStillQuality_Fine
#endif
};
#endif

PSMENUITEM   sMenuListMainStill[] =
{
#if (MENU_STILL_SIZE_EN)
    &sItemStillImageSize,
#endif
#if (MENU_STILL_QUALITY_EN)
    &sItemStillQuality,
#endif
#if (MENU_STILL_SCENE_EN)
	&sItemScence,
#endif
#if (MENU_STILL_EV_EN)
	&sItemEV,
#endif
#if (MENU_STILL_WB_EN)
	&sItemWB,
#endif
#if (MENU_STILL_ISO_EN)
	&sItemISO,
#endif
#if (MENU_STILL_COLOR_EN)
	&sItemColor,
#endif
#if (MENU_STILL_EFFECT_EN)
	&sItemEffect,
#endif
#if (MENU_STILL_CONTRAST_EN)
	&sItemContrast,
#endif
#if (MENU_STILL_SATURATION_EN)
	&sItemSaturation,
#endif
#if (MENU_STILL_SHARPNESS_EN)
	&sItemSharpness,
#endif
#if (MENU_STILL_GAMMA_EN)
	&sItemGamma,
#endif
};
/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuStill =
{
    MENUID_MAIN_MENU_STILL,
    IDS_DS_STILL_CAPTURE,
    NULL,
    sizeof(sMenuListMainStill)/sizeof(PSMENUITEM),
    sMenuListMainStill,
    0,
};

//--------------SUB MENU-------------------

#if (MENU_STILL_SIZE_EN)
SMENUSTRUCT sSubStillImageSize =
{
    MENUID_SUB_MENU_STILL_IMAGE_SIZE,
    IDS_DS_STILL_IMAGE_SIZE,
    &sMainMenuStill,
    sizeof(sMenuListStillImageSize)/sizeof(PSMENUITEM),
    sMenuListStillImageSize,
    MenuGetDefault_Camera,
};
#endif

#if (MENU_STILL_QUALITY_EN)
SMENUSTRUCT sSubStillQuality =
{
    MENUID_SUB_MENU_STILL_QUALITY,
    IDS_DS_STILL_QUALITY,
    &sMainMenuStill,
    sizeof(sMenuListStillQuality)/sizeof(PSMENUITEM),
    sMenuListStillQuality,
    MenuGetDefault_Camera,
};
#endif
/*===========================================================================
 * Main body
 *===========================================================================*/
 #if (MENU_STILL_SIZE_EN)
bool MenuItemStillImageSize(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiIMGSize = pItem->iItemId - ITEMID_STILL_IMAGE_SIZE - 1;
    return true;
}
#endif

#if (MENU_STILL_QUALITY_EN)
bool MenuItemStillQuality(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiIMGQuality = pItem->iItemId - ITEMID_STILL_QUALITY - 1;
    return true;
}
#endif

int   MenuGetDefault_Camera(PSMENUSTRUCT pMenu)
{
    int DefaultValue = 0;

    switch( pMenu->iMenuId )
    {
#if (MENU_STILL_SIZE_EN)
        case MENUID_SUB_MENU_STILL_IMAGE_SIZE:
            DefaultValue = MenuSettingConfig()->uiIMGSize;
            break;
#endif
#if (MENU_STILL_QUALITY_EN)
        case MENUID_SUB_MENU_STILL_QUALITY:
            DefaultValue = MenuSettingConfig()->uiIMGQuality;
            break;
#endif
    }
    return DefaultValue;
}

