#include "MenuCommon.h"

/*===========================================================================
 * Local function
 *===========================================================================*/
bool MenuItemScenceSelect(PSMENUITEM pItem, bool bHover);
bool MenuItemFocusWindow(PSMENUITEM pItem);
bool MenuItemFocusRange(PSMENUITEM pItem);
bool MenuItemExpoMetering(PSMENUITEM pItem);
bool MenuItemExpoAdjust(PSMENUITEM pItem);
bool MenuItemISO(PSMENUITEM pItem);
bool MenuItemWB(PSMENUITEM pItem);
bool MenuItemColor(PSMENUITEM pItem);
bool MenuItemColorTemp(PSMENUITEM pItem);
bool MenuItemEffect(PSMENUITEM pItem);
bool MenuItemContrastAdjust(PSMENUITEM pItem);
bool MenuItemSaturationAdjust(PSMENUITEM pItem);
bool MenuItemSharpnessAdjust(PSMENUITEM pItem);
bool MenuItemGammaAdjust(PSMENUITEM pItem);

int   MenuGetDefault_ManualSetting(PSMENUSTRUCT pMenu);
 /*===========================================================================
 * Extern varible
 *===========================================================================*/
extern SMENUSTRUCT sMainMenuManual;

extern SMENUSTRUCT sSubScence;
extern SMENUSTRUCT sSubFocusWindow;
extern SMENUSTRUCT sSubFocusRange;
extern SMENUSTRUCT sSubExpoMetering;
extern SMENUSTRUCT sSubExpoAdjust;
extern SMENUSTRUCT sSubISO;
extern SMENUSTRUCT sSubWB;
extern SMENUSTRUCT sSubColor;
extern SMENUSTRUCT sSubColorTemp;
extern SMENUSTRUCT sSubEffect;
extern SMENUSTRUCT sSubSmileDetection;
extern SMENUSTRUCT sSubSmileSensitivity;
extern SMENUSTRUCT sSubContrastAdjust;
extern SMENUSTRUCT sSubSaturationAdjust;
extern SMENUSTRUCT sSubSharpnessAdjust;
extern SMENUSTRUCT sSubGammaAdjust;
 /*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/
// Scence
#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
SMENUITEM sItemScence                   = { ITEMID_SCENE,                IDS_DS_SCENE_SELECTION, &sSubScence, 0 };
#if (MENU_MANUAL_SCENE_AUTO_EN)
SMENUITEM sItemScence_Auto              = { ITEMID_SCENE_AUTO,           IDS_DS_AUTO ,           NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_SPORT_EN)
SMENUITEM sItemScence_Sports            = { ITEMID_SCENE_SPORTS,        IDS_DS_SCENE_SPORTS,    NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_PORTRAIT_EN)
SMENUITEM sItemScence_Portrait          = { ITEMID_SCENE_PORTRAIT,   IDS_DS_SCENE_PORTRAIT,  NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_LANDSCAPE_EN)
SMENUITEM sItemScence_Landscape         = { ITEMID_SCENE_LANDSCAPE, IDS_DS_SCENE_LANDSCAPE, NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_PORTRAIT_EN)
SMENUITEM sItemScence_TwilightPortrait  = { ITEMID_SCENE_TWILIGHT_PORTRAIT,  IDS_DS_SCENE_TWILIGHTPORTRAIT,NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_EN)
SMENUITEM sItemScence_Twilight          = { ITEMID_SCENE_TWILIGHT,   IDS_DS_SCENE_TWILIGHT,  NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_SNOW_EN)
SMENUITEM sItemScence_Snow              = { ITEMID_SCENE_SNOW,           IDS_DS_SCENE_SNOW,      NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_BEACH_EN)
SMENUITEM sItemScence_Beach             = { ITEMID_SCENE_BEACH,         IDS_DS_SCENE_BEACH,     NULL, MenuItemScenceSelect };
#endif
#if (MENU_MANUAL_SCENE_FIREWORKS_EN)
SMENUITEM sItemScence_Fireworks         = { ITEMID_SCENE_FIREWORKS,  IDS_DS_SCENE_FIREWORKS, NULL, MenuItemScenceSelect };
#endif
#endif


// Exposure Adjust
#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
SMENUITEM sItemEV                   = { ITEMID_EV,      IDS_DS_EV,  &sSubExpoAdjust, 0 };
#if (MENU_MANUAL_EV_P20_EN)
SMENUITEM sItemEV_P20               = { ITEMID_EV_P20,  IDS_DS_EV_P20,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_P17_EN)
SMENUITEM sItemEV_P17               = { ITEMID_EV_P17,  IDS_DS_EV_P17,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_P13_EN)
SMENUITEM sItemEV_P13               = { ITEMID_EV_P13,  IDS_DS_EV_P13,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_P10_EN)
SMENUITEM sItemEV_P10               = { ITEMID_EV_P10,  IDS_DS_EV_P10,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_P07_EN)
SMENUITEM sItemEV_P07               = { ITEMID_EV_P07,  IDS_DS_EV_P07,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_P03_EN)
SMENUITEM sItemEV_P03               = { ITEMID_EV_P03,  IDS_DS_EV_P03,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_00_EN)
SMENUITEM sItemEV_00                = { ITEMID_EV_00,      IDS_DS_EV_0,  NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_N03_EN)
SMENUITEM sItemEV_N03               = { ITEMID_EV_N03,  IDS_DS_EV_N03,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_N07_EN)
SMENUITEM sItemEV_N07               = { ITEMID_EV_N07,  IDS_DS_EV_N07,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_N10_EN)
SMENUITEM sItemEV_N10               = { ITEMID_EV_N10,  IDS_DS_EV_N10,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_N13_EN)
SMENUITEM sItemEV_N13               = { ITEMID_EV_N13,  IDS_DS_EV_N13,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_N17_EN)
SMENUITEM sItemEV_N17               = { ITEMID_EV_N17,  IDS_DS_EV_N17,NULL, MenuItemExpoAdjust };
#endif
#if (MENU_MANUAL_EV_N20_EN)
SMENUITEM sItemEV_N20               = { ITEMID_EV_N20,  IDS_DS_EV_N20,NULL, MenuItemExpoAdjust };
#endif
#endif

// ISO Sensitivity
#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
SMENUITEM sItemISO                  = { ITEMID_ISO,        IDS_DS_ISO,     &sSubISO, 0 };
#if (MENU_MANUAL_ISO_AUTO_EN)
SMENUITEM sItemISO_Auto             = { ITEMID_ISO_AUTO,   IDS_DS_AUTO,     NULL, MenuItemISO };
#endif
#if (MENU_MANUAL_ISO_100_EN)
SMENUITEM sItemISO_100              = { ITEMID_ISO_100,     IDS_DS_ISO_100,  NULL, MenuItemISO };
#endif
#if (MENU_MANUAL_ISO_200_EN)
SMENUITEM sItemISO_200              = { ITEMID_ISO_200,     IDS_DS_ISO_200,  NULL, MenuItemISO };
#endif
#if (MENU_MANUAL_ISO_400_EN)
SMENUITEM sItemISO_400              = { ITEMID_ISO_400,     IDS_DS_ISO_400,  NULL, MenuItemISO };
#endif
#if (MENU_MANUAL_ISO_800_EN)
SMENUITEM sItemISO_800              = { ITEMID_ISO_800,      IDS_DS_ISO_800,  NULL, MenuItemISO };
#endif
#if (MENU_MANUAL_ISO_1600_EN)
SMENUITEM sItemISO_1600             = { ITEMID_ISO_1600,   IDS_DS_ISO_1600, NULL, MenuItemISO };
#endif
#if (MENU_MANUAL_ISO_3200_EN)
SMENUITEM sItemISO_3200             = { ITEMID_ISO_3200,    IDS_DS_ISO_3200, NULL, MenuItemISO };
#endif
#endif

// White Balance
#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)

SMENUITEM sItemWB                   = { ITEMID_WB,                     IDS_DS_WB,              &sSubWB, 0 };
#if (MENU_MANUAL_WB_AUTO_EN)
SMENUITEM sItemWB_Auto              = { ITEMID_WB_AUTO,         IDS_DS_AUTO,            NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_DAYLIGHT_EN)
SMENUITEM sItemWB_Daylight          = { ITEMID_WB_DAYLIGHT,    IDS_DS_WB_DAYLIGHT,     NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_CLOUDY_EN)
SMENUITEM sItemWB_Cloudy            = { ITEMID_WB_CLOUDY,       IDS_DS_WB_CLOUDY,       NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_FLUORESCENT1_EN)
SMENUITEM sItemWB_Fluorescent1      = { ITEMID_WB_FLUORESCENT1,        IDS_DS_WB_FLUORESCENT1, NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_FLUORESCENT2_EN)
SMENUITEM sItemWB_Fluorescent2      = { ITEMID_WB_FLUORESCENT2,        IDS_DS_WB_FLUORESCENT2, NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_FLUORESCENT3_EN)
SMENUITEM sItemWB_Fluorescent3      = { ITEMID_WB_FLUORESCENT3,        IDS_DS_WB_FLUORESCENT3, NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_INCANDESCENT_EN)
SMENUITEM sItemWB_Incandescent      = { ITEMID_WB_INCANDESCENT, IDS_DS_WB_INCANDESCENT, NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_FLASH_EN)
SMENUITEM sItemWB_Flash             = { ITEMID_WB_FLASH,               IDS_DS_WB_FLASH,        NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_ONEPUSH_EN)
SMENUITEM sItemWB_Onepush           = { ITEMID_WB_ONEPUSH,         IDS_DS_WB_ONEPUSH,      NULL, MenuItemWB };
#endif
#if (MENU_MANUAL_WB_ONE_PUSH_SET_EN)
SMENUITEM sItemWB_OnePush_Set       = { ITEMID_WB_ONE_PUSH_SET, IDS_DS_WB_ONE_PUSH_SET, NULL, MenuItemWB };
#endif
#endif

// Color
#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN || MENU_MOVIE_COLOR_EN)
SMENUITEM sItemColor                = { ITEMID_COLOR,             IDS_DS_COLOR,  &sSubColor, 0 };
#if (MENU_MANUAL_COLOR_NATURAL_EN)
SMENUITEM sItemColor_Natural        = { ITEMID_COLOR_NATURAL,  IDS_DS_COLOR_NATURAL, NULL, MenuItemColor };
#endif
#if (MENU_MANUAL_COLOR_VIVID_EN)
SMENUITEM sItemColor_Vivid          = { ITEMID_COLOR_VIVID,      IDS_DS_COLOR_VIVID,   NULL, MenuItemColor };
#endif
#if (MENU_MANUAL_COLOR_PALE_EN)
SMENUITEM sItemColor_Pale           = { ITEMID_COLOR_PALE,        IDS_DS_COLOR_PALE,    NULL, MenuItemColor };
#endif
#endif

// Effect
#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
SMENUITEM sItemEffect               = { ITEMID_EFFECT,                  IDS_DS_EFFECT,              &sSubEffect, 0 };
#if (MENU_MANUAL_EFFECT_NORMAL_EN)
SMENUITEM sItemEffect_Normal        = { ITEMID_EFFECT_NORMAL,         IDS_DS_NORMAL,              NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_SEPIA_EN)
SMENUITEM sItemEffect_Sepia         = { ITEMID_EFFECT_SEPIA,           IDS_DS_EFFECT_SEPIA,        NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_BLACK_WHITE_EN)
SMENUITEM sItemEffect_BlackWhite    = { ITEMID_EFFECT_BLACK_WHITE,        IDS_DS_EFFECT_BLACK_WHITE,  NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_EMBOSS_EN)
SMENUITEM sItemEffect_Emboss        = { ITEMID_EFFECT_EMBOSS,         IDS_DS_EFFECT_EMBOSS,       NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_NEGATIVE_EN)
SMENUITEM sItemEffect_Negative      = { ITEMID_EFFECT_NEGATIVE,      IDS_DS_EFFECT_NEGATIVE,    NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_SKETCH_EN)
SMENUITEM sItemEffect_Sketch        = { ITEMID_EFFECT_SKETCH,         IDS_DS_EFFECT_SKETCH,       NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_OIL_EN)
SMENUITEM sItemEffect_Oil           = { ITEMID_EFFECT_OIL,               IDS_DS_EFFECT_OIL,          NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_CRAYON_EN)
SMENUITEM sItemEffect_Crayon        = { ITEMID_EFFECT_CRAYON,         IDS_DS_EFFECT_CRAYON,       NULL, MenuItemEffect };
#endif
#if (MENU_MANUAL_EFFECT_BEAUTY_EN)
SMENUITEM sItemEffect_Beauty        = { ITEMID_EFFECT_BEAUTY,         IDS_DS_EFFECT_BEAUTY,       NULL, MenuItemEffect };
#endif
#endif

// Contrast Adjust
#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
SMENUITEM sItemContrast             = { ITEMID_CONTRAST,          IDS_DS_CONTRAST,    &sSubContrastAdjust, 0 };
SMENUITEM sItemContrastInc          = { ITEMID_CONTRAST_INC,      IDS_DS_INC,    NULL, MenuItemContrastAdjust };
SMENUITEM sItemContrastDec          = { ITEMID_CONTRAST_DEC,      IDS_DS_DEC,    NULL, MenuItemContrastAdjust };
#endif

// Saturation Adjust
#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
SMENUITEM sItemSaturation           = { ITEMID_SATURATION,      IDS_DS_SATURATION,  &sSubSaturationAdjust, 0 };
SMENUITEM sItemSaturationInc        = { ITEMID_SATURATION_INC,  IDS_DS_INC,  NULL, MenuItemSaturationAdjust };
SMENUITEM sItemSaturationDec        = { ITEMID_SATURATION_DEC,  IDS_DS_DEC,  NULL, MenuItemSaturationAdjust };
#endif

// Sharpness Adjust
#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
SMENUITEM sItemSharpness            = { ITEMID_SHARPNESS,       IDS_DS_SHARPNESS,   &sSubSharpnessAdjust, 0 };
SMENUITEM sItemSharpnessInc         = { ITEMID_SHARPNESS_INC,    IDS_DS_INC,   NULL, MenuItemSharpnessAdjust };
SMENUITEM sItemSharpnessDec         = { ITEMID_SHARPNESS_DEC,    IDS_DS_DEC,   NULL, MenuItemSharpnessAdjust };
#endif

// Gamma Adjust
#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
SMENUITEM sItemGamma                = { ITEMID_GAMMA,                IDS_DS_GAMMA,       &sSubGammaAdjust, 0 };
SMENUITEM sItemGammaInc             = { ITEMID_GAMMA_INC,            IDS_DS_INC,       NULL, MenuItemGammaAdjust };
SMENUITEM sItemGammaDec             = { ITEMID_GAMMA_DEC,            IDS_DS_DEC,       NULL, MenuItemGammaAdjust };
#endif


 /*===========================================================================
 * Global varible : Item List
 *===========================================================================*/
#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
PSMENUITEM   sMenuListScence[] =
{
#if (MENU_MANUAL_SCENE_AUTO_EN)
    &sItemScence_Auto,
#endif
#if (MENU_MANUAL_SCENE_SPORT_EN)
    &sItemScence_Sports,
#endif
#if (MENU_MANUAL_SCENE_PORTRAIT_EN)
    &sItemScence_Portrait,
#endif
#if (MENU_MANUAL_SCENE_LANDSCAPE_EN)
    &sItemScence_Landscape,
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_PORTRAIT_EN)
    &sItemScence_TwilightPortrait,
#endif
#if (MENU_MANUAL_SCENE_TWILIGHT_EN)
    &sItemScence_Twilight,
#endif
#if (MENU_MANUAL_SCENE_SNOW_EN)
    &sItemScence_Snow,
#endif
#if (MENU_MANUAL_SCENE_BEACH_EN)
    &sItemScence_Beach,
#endif
#if (MENU_MANUAL_SCENE_FIREWORKS_EN)
    &sItemScence_Fireworks
#endif
};
#endif

#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
PSMENUITEM   sMenuListEV[] =
{
#if (MENU_MANUAL_EV_N20_EN)
    &sItemEV_N20,
#endif
#if (MENU_MANUAL_EV_N17_EN)
    &sItemEV_N17,
#endif
#if (MENU_MANUAL_EV_N13_EN)
    &sItemEV_N13,
#endif
#if (MENU_MANUAL_EV_N10_EN)
    &sItemEV_N10,
#endif
#if (MENU_MANUAL_EV_N07_EN)
    &sItemEV_N07,
#endif
#if (MENU_MANUAL_EV_N03_EN)
    &sItemEV_N03,
#endif
#if (MENU_MANUAL_EV_00_EN)
    &sItemEV_00,
#endif
#if (MENU_MANUAL_EV_P03_EN)
    &sItemEV_P03,
#endif
#if (MENU_MANUAL_EV_P07_EN)
    &sItemEV_P07,
#endif
#if (MENU_MANUAL_EV_P10_EN)
    &sItemEV_P10,
#endif
#if (MENU_MANUAL_EV_P13_EN)
    &sItemEV_P13,
#endif
#if (MENU_MANUAL_EV_P17_EN)
    &sItemEV_P17,
#endif
#if (MENU_MANUAL_EV_P20_EN)
    &sItemEV_P20
#endif
};
#endif

#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
PSMENUITEM   sMenuListISO[] =
{
#if (MENU_MANUAL_ISO_AUTO_EN)
    &sItemISO_Auto,
#endif
#if (MENU_MANUAL_ISO_100_EN)
    &sItemISO_100,
#endif
#if (MENU_MANUAL_ISO_200_EN)
    &sItemISO_200,
#endif
#if (MENU_MANUAL_ISO_400_EN)
    &sItemISO_400,
#endif
#if (MENU_MANUAL_ISO_800_EN)
    &sItemISO_800,
#endif
#if (MENU_MANUAL_ISO_1600_EN)
    &sItemISO_1600,
#endif
#if (MENU_MANUAL_ISO_3200_EN)
    &sItemISO_3200
#endif
};
#endif

#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
PSMENUITEM   sMenuListWB[] =
{
#if (MENU_MANUAL_WB_AUTO_EN)
    &sItemWB_Auto,
#endif
#if (MENU_MANUAL_WB_DAYLIGHT_EN)
    &sItemWB_Daylight,
#endif
#if (MENU_MANUAL_WB_CLOUDY_EN)
    &sItemWB_Cloudy,
#endif
#if (MENU_MANUAL_WB_FLUORESCENT1_EN)
    &sItemWB_Fluorescent1,
#endif
#if (MENU_MANUAL_WB_FLUORESCENT2_EN)
    &sItemWB_Fluorescent2,
#endif
#if (MENU_MANUAL_WB_FLUORESCENT3_EN)
    &sItemWB_Fluorescent3,
#endif
#if (MENU_MANUAL_WB_INCANDESCENT_EN)
    &sItemWB_Incandescent,
#endif
#if (MENU_MANUAL_WB_FLASH_EN)
    &sItemWB_Flash,
#endif
#if (MENU_MANUAL_WB_ONEPUSH_EN)
    &sItemWB_Onepush,
#endif
#if (MENU_MANUAL_WB_ONE_PUSH_SET_EN)
    &sItemWB_OnePush_Set
#endif
};
#endif

#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN)
PSMENUITEM   sMenuListColor[] =
{
#if (MENU_MANUAL_COLOR_NATURAL_EN)
    &sItemColor_Natural,
#endif
#if (MENU_MANUAL_COLOR_VIVID_EN)
    &sItemColor_Vivid,
#endif
#if (MENU_MANUAL_COLOR_PALE_EN)
    &sItemColor_Pale
#endif
};
#endif

#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
PSMENUITEM   sMenuListEffect[] =
{
#if (MENU_MANUAL_EFFECT_NORMAL_EN)
    &sItemEffect_Normal,
#endif
#if (MENU_MANUAL_EFFECT_SEPIA_EN)
    &sItemEffect_Sepia,
#endif
#if (MENU_MANUAL_EFFECT_BLACK_WHITE_EN)
    &sItemEffect_BlackWhite,
#endif
#if (MENU_MANUAL_EFFECT_EMBOSS_EN)
    &sItemEffect_Emboss,
#endif
#if (MENU_MANUAL_EFFECT_NEGATIVE_EN)
    &sItemEffect_Negative,
#endif
#if (MENU_MANUAL_EFFECT_SKETCH_EN)
    &sItemEffect_Sketch,
#endif
#if (MENU_MANUAL_EFFECT_OIL_EN)
    &sItemEffect_Oil,
#endif
#if (MENU_MANUAL_EFFECT_CRAYON_EN)
    &sItemEffect_Crayon,
#endif
#if (MENU_MANUAL_EFFECT_BEAUTY_EN)
    &sItemEffect_Beauty
#endif
};
#endif

#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
PSMENUITEM   sMenuListContrast[] =
{
    &sItemContrastDec,
    &sItemContrastInc
};
#endif

#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
PSMENUITEM   sMenuListSaturation[] =
{
    &sItemSaturationDec,
    &sItemSaturationInc
};
#endif

#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
PSMENUITEM   sMenuListSharpness[] =
{
    &sItemSharpnessDec,
    &sItemSharpnessInc
};
#endif

#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
PSMENUITEM   sMenuListGamma[] =
{
    &sItemGammaDec,
    &sItemGammaInc
};
#endif
 /*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/
//--------------SUB MENU-------------------

#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
SMENUSTRUCT sSubScence =
{
    MENUID_SUB_MENU_SCENCE,
    IDS_DS_SCENE_SELECTION,
    &sMainMenuVideo,
    sizeof(sMenuListScence)/sizeof(PSMENUITEM),
    sMenuListScence,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
SMENUSTRUCT sSubExpoAdjust =
{
    MENUID_SUB_MENU_EV,
    IDS_DS_EV,
    &sMainMenuVideo,
    sizeof(sMenuListEV)/sizeof(PSMENUITEM),
    sMenuListEV,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
SMENUSTRUCT sSubISO =
{
    MENUID_SUB_MENU_ISO,
    IDS_DS_ISO,
    &sMainMenuVideo,
    sizeof(sMenuListISO)/sizeof(PSMENUITEM),
    sMenuListISO,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
SMENUSTRUCT sSubWB =
{
    MENUID_SUB_MENU_WB,
    IDS_DS_WB,
    &sMainMenuVideo,
    sizeof(sMenuListWB)/sizeof(PSMENUITEM),
    sMenuListWB,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN)
SMENUSTRUCT sSubColor =
{
    MENUID_SUB_MENU_COLOR,
    IDS_DS_COLOR,
    &sMainMenuVideo,
    sizeof(sMenuListColor)/sizeof(PSMENUITEM),
    sMenuListColor,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
SMENUSTRUCT sSubEffect =
{
    MENUID_SUB_MENU_EFFECT,
    IDS_DS_EFFECT,
    &sMainMenuVideo,
    sizeof(sMenuListEffect)/sizeof(PSMENUITEM),
    sMenuListEffect,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
SMENUSTRUCT sSubContrastAdjust =
{
    MENUID_SUB_MENU_CONTRAST,
    IDS_DS_CONTRAST,
    &sMainMenuVideo,
    sizeof(sMenuListContrast)/sizeof(PSMENUITEM),
    sMenuListContrast,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
SMENUSTRUCT sSubSaturationAdjust =
{
    MENUID_SUB_MENU_SATURATION,
    IDS_DS_SATURATION,
    &sMainMenuVideo,
    sizeof(sMenuListSaturation)/sizeof(PSMENUITEM),
    sMenuListSaturation,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
SMENUSTRUCT sSubSharpnessAdjust =
{
    MENUID_SUB_MENU_SHARPNESS,
    IDS_DS_SHARPNESS,
    &sMainMenuVideo,
    sizeof(sMenuListSharpness)/sizeof(PSMENUITEM),
    sMenuListSharpness,
    MenuGetDefault_ManualSetting,
};
#endif

#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
SMENUSTRUCT sSubGammaAdjust =
{
    MENUID_SUB_MENU_GAMMA,
    IDS_DS_GAMMA,
    &sMainMenuVideo,
    sizeof(sMenuListSaturation)/sizeof(PSMENUITEM),
    sMenuListGamma,
    MenuGetDefault_ManualSetting,
};
#endif
 /*===========================================================================
 * Main body
 *===========================================================================*/
#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
bool MenuItemScenceSelect(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiScene = pItem->iItemId - ITEMID_SCENE -1;
    return true;
}
#endif

#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
bool MenuItemExpoAdjust(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiEV = pItem->iItemId - ITEMID_EV-1;
    return true;
}
#endif

#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
bool MenuItemISO(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiISO = pItem->iItemId - ITEMID_ISO-1;
    return true;
}
#endif

#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
bool MenuItemWB(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiWB = pItem->iItemId - ITEMID_WB -1;
    return true;
}
#endif

#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN || MENU_MOVIE_COLOR_EN)
bool MenuItemColor(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiColor = pItem->iItemId - ITEMID_COLOR-1;
    return true;
}
#endif

#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
bool MenuItemEffect(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiEffect = pItem->iItemId - ITEMID_EFFECT -1;
    return true;
}
#endif

#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
bool MenuItemContrastAdjust(PSMENUITEM pItem)
{
    if(pItem->iItemId == ITEMID_CONTRAST_INC)
    {
        MenuSettingConfig()->uiContrast += 10;
        if(MenuSettingConfig()->uiContrast > 100)
            MenuSettingConfig()->uiContrast = 100;
    }
    else if(pItem->iItemId == ITEMID_CONTRAST_DEC)
    {
        MenuSettingConfig()->uiContrast -= 10;
        if(MenuSettingConfig()->uiContrast < 0)
            MenuSettingConfig()->uiContrast = 0;
    }
    return true;
}
#endif

#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
bool MenuItemSaturationAdjust(PSMENUITEM pItem)
{
    if(pItem->iItemId == ITEMID_SATURATION_INC)
    {
        MenuSettingConfig()->uiSaturation+= 10;
        if(MenuSettingConfig()->uiSaturation > 100)
            MenuSettingConfig()->uiSaturation = 100;
    }
    else if(pItem->iItemId == ITEMID_SATURATION_DEC)
    {
        MenuSettingConfig()->uiSaturation -= 10;
        if(MenuSettingConfig()->uiSaturation < 0)
            MenuSettingConfig()->uiSaturation = 0;
    }
    return true;
}
#endif

#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
bool MenuItemSharpnessAdjust(PSMENUITEM pItem)
{
    if(pItem->iItemId == ITEMID_SHARPNESS_INC)
    {
        MenuSettingConfig()->uiSharpness+= 10;
        if(MenuSettingConfig()->uiSharpness > 100)
            MenuSettingConfig()->uiSharpness = 100;
    }
    else if(pItem->iItemId == ITEMID_SHARPNESS_DEC)
    {
        MenuSettingConfig()->uiSharpness -= 10;
        if(MenuSettingConfig()->uiSharpness < 0)
            MenuSettingConfig()->uiSharpness = 0;
    }
    return true;
}
#endif

#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
bool MenuItemGammaAdjust(PSMENUITEM pItem)
{
    if(pItem->iItemId == ITEMID_GAMMA_INC)
    {
        MenuSettingConfig()->uiGamma+= 10;
        if(MenuSettingConfig()->uiGamma > 100)
            MenuSettingConfig()->uiGamma = 100;
    }
    else if(pItem->iItemId == ITEMID_GAMMA_DEC)
    {
        MenuSettingConfig()->uiGamma -= 10;
        if(MenuSettingConfig()->uiGamma < 0)
            MenuSettingConfig()->uiGamma = 0;
    }
    return true;
}
#endif

int MenuGetDefault_ManualSetting(PSMENUSTRUCT pMenu)
{
    int  DefaultValue = 0;
    switch( pMenu->iMenuId )
    {
#if (MENU_MANUAL_SCENE_EN || MENU_STILL_SCENE_EN || MENU_MOVIE_SCENE_EN)
        case MENUID_SUB_MENU_SCENCE:
            DefaultValue = MenuSettingConfig()->uiScene;
            break;
#endif
#if (MENU_MANUAL_EV_EN || MENU_STILL_EV_EN || MENU_MOVIE_EV_EN)
        case MENUID_SUB_MENU_EV:
            DefaultValue = MenuSettingConfig()->uiEV;
            break;
#endif
#if (MENU_MANUAL_ISO_EN || MENU_STILL_ISO_EN || MENU_MOVIE_ISO_EN)
        case MENUID_SUB_MENU_ISO:
            DefaultValue = MenuSettingConfig()->uiISO;
            break;
#endif
#if (MENU_MANUAL_WB_EN || MENU_STILL_WB_EN || MENU_MOVIE_WB_EN)
        case MENUID_SUB_MENU_WB:
            DefaultValue = MenuSettingConfig()->uiWB ;
            break;
#endif
#if (MENU_MANUAL_COLOR_EN || MENU_STILL_COLOR_EN || MENU_MOVIE_COLOR_EN)
        case MENUID_SUB_MENU_COLOR:
            DefaultValue = MenuSettingConfig()->uiColor;
            break;
#endif
#if (MENU_MANUAL_EFFECT_EN || MENU_STILL_EFFECT_EN || MENU_MOVIE_EFFECT_EN)
        case MENUID_SUB_MENU_EFFECT:
            DefaultValue = MenuSettingConfig()->uiEffect;
            break;
#endif
#if (MENU_MANUAL_CONTRAST_EN || MENU_STILL_CONTRAST_EN || MENU_MOVIE_CONTRAST_EN)
        case MENUID_SUB_MENU_CONTRAST:
            DefaultValue = MenuSettingConfig()->uiContrast;
            break;
#endif
#if (MENU_MANUAL_SATURATION_EN || MENU_STILL_SATURATION_EN || MENU_MOVIE_SATURATION_EN)
        case MENUID_SUB_MENU_SATURATION:
            DefaultValue = MenuSettingConfig()->uiSaturation;
            break;
#endif
#if (MENU_MANUAL_SHARPNESS_EN || MENU_STILL_SHARPNESS_EN || MENU_MOVIE_SHARPNESS_EN)
        case MENUID_SUB_MENU_SHARPNESS:
            DefaultValue = MenuSettingConfig()->uiSharpness;
            break;
#endif
#if (MENU_MANUAL_GAMMA_EN || MENU_STILL_GAMMA_EN || MENU_MOVIE_GAMMA_EN)
        case MENUID_SUB_MENU_GAMMA:
            DefaultValue = MenuSettingConfig()->uiGamma;
            break;
#endif
    }
    return DefaultValue;
}

 
