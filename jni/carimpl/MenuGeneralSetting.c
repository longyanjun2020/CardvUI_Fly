#include "MenuCommon.h"
#include "carimpl/carimpl.h"
/*===========================================================================
 * Local function
 *===========================================================================*/
bool MenuItemBeep(PSMENUITEM pItem);
bool MenuItemAutoPowerOff(PSMENUITEM pItem);
bool MenuItemClockSettings(PSMENUITEM pItem);
bool MenuItemDateTimeFormat(PSMENUITEM pItem);
bool MenuItemDateLogoStamp(PSMENUITEM pItem);
bool MenuItemGPSStamp(PSMENUITEM pItem);
bool MenuItemSpeedStamp(PSMENUITEM pItem);
bool MenuItemLanguage(PSMENUITEM pItem);
bool MenuItemResetSetup(PSMENUITEM pItem);
bool MenuItemFwVersion(PSMENUITEM pItem);
bool MenuItemGPSInfo(PSMENUITEM pItem);
bool MenuItemFlickerHz(PSMENUITEM pItem);
bool MenuItemUSBSelect(PSMENUITEM pItem);
bool MenuItemLCDPowerSave(PSMENUITEM pItem);
bool MenuItemGsensorSensitivity(PSMENUITEM pItem);
bool MenuItemGsensorPowerOnSensitivity(PSMENUITEM pItem);
bool MenuItemMotionDtcSensitivity(PSMENUITEM pItem);
bool MenuItemTimeZone(PSMENUITEM pItem);
bool MenuItemNightModeSelect(PSMENUITEM pItem);
bool MenuItemWiFiMode(PSMENUITEM pItem);

void MenuItemDateTimeFormatToAhcTimeStampSetting(void);

#if (MENU_GENERAL_PQ_CONTRAST_EN || MENU_GENERAL_PQ_BRIGHTNESS_EN || MENU_GENERAL_PQ_SATURATION_EN)
bool MenuItemPQAdjust(PSMENUITEM pItem);
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_EN)
bool MenuItemPQColorTemp(PSMENUITEM pItem);
#endif

int   MenuGetDefault_GeneralSetting(PSMENUSTRUCT pMenu );
 /*===========================================================================
 * Extern varible
 *===========================================================================*/
extern SMENUSTRUCT sMainMenuGeneral;

extern SMENUSTRUCT sSubBeep;
extern SMENUSTRUCT sSubAutoPowerOff;
extern SMENUSTRUCT sSubClockSettings;
extern SMENUSTRUCT sSubDateTimeFormat;
extern SMENUSTRUCT sSubDateLogoStamp;
extern SMENUSTRUCT sSubGPSStamp;
extern SMENUSTRUCT sSubSpeedStamp;
extern SMENUSTRUCT sSubLanguage;
extern SMENUSTRUCT sSubResetSetup;
extern SMENUSTRUCT sSubFwVersionInfo;
extern SMENUSTRUCT sSubGPSInfo;
extern SMENUSTRUCT sSubFlickerHz;
extern SMENUSTRUCT sSubUSBSelect;
extern SMENUSTRUCT sSubLCDPowerSave;
extern SMENUSTRUCT sSubGsensorSensitivity;
extern SMENUSTRUCT sSubPowerOnGsensorSensitivity;
extern SMENUSTRUCT sSubMotionDtcSensitivity;
extern SMENUSTRUCT sSubTimeZone;
extern SMENUSTRUCT sSubNightMode;
extern SMENUSTRUCT sSubWiFiMode;

#if (MENU_GENERAL_PQ_CONTRAST_EN)
extern SMENUSTRUCT sSubPQContrast;
#endif
#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
extern SMENUSTRUCT sSubPQBrightness;
#endif
#if (MENU_GENERAL_PQ_SATURATION_EN)
extern SMENUSTRUCT sSubPQSaturation;
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_EN)
extern SMENUSTRUCT sSubPQColorTemp;
#endif
 /*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/
// Beep
#if (MENU_GENERAL_BEEP_EN)
SMENUITEM sItemBeep                 = { ITEMID_BEEP,    IDS_DS_BEEP, &sSubBeep, 0 };
#if (MENU_GENERAL_BEEP_ON_EN)
SMENUITEM sItemBeep_On              = { ITEMID_BEEP_ON,  IDS_DS_ON, NULL, MenuItemBeep };
#endif
#if (MENU_GENERAL_BEEP_OFF_EN)
SMENUITEM sItemBeep_Off             = { ITEMID_BEEP_OFF, IDS_DS_OFF,NULL, MenuItemBeep };
#endif
#endif

// Power Save
#if (MENU_GENERAL_AUTO_POWEROFF_EN)
SMENUITEM sItemAutoPowerOff          = { ITEMID_AUTO_POWER_OFF,       IDS_DS_POWER_OFF,  &sSubAutoPowerOff, 0 };
#if (MENU_GENERAL_AUTO_POWEROFF_NEVER_EN)
SMENUITEM sItemAutoPowerOff_Never    = { ITEMID_AUTO_POWER_OFF_NEVER,   IDS_DS_POWER_OFF_NEVER,    NULL,   MenuItemAutoPowerOff };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_15SEC_EN)
SMENUITEM sItemAutoPowerOff_15Second = { ITEMID_AUTO_POWER_OFF_15SEC,  IDS_DS_POWER_OFF_15SEC,    NULL,   MenuItemAutoPowerOff };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_30SEC_EN)
SMENUITEM sItemAutoPowerOff_30Second = { ITEMID_AUTO_POWER_OFF_30SEC,  IDS_TIME_30SEC,    NULL,   MenuItemAutoPowerOff };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_1MIN_EN)
SMENUITEM sItemAutoPowerOff_1Minutes = { ITEMID_AUTO_POWER_OFF_1MIN,   IDS_TIME_1MIN,     NULL,   MenuItemAutoPowerOff };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_2MIN_EN)
SMENUITEM sItemAutoPowerOff_2Minutes = { ITEMID_AUTO_POWER_OFF_2MIN,   IDS_TIME_2MIN,     NULL,   MenuItemAutoPowerOff };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_3MIN_EN)
SMENUITEM sItemAutoPowerOff_3Minutes = { ITEMID_AUTO_POWER_OFF_3MIN,   IDS_TIME_3MIN,     NULL,   MenuItemAutoPowerOff };
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_5MIN_EN)
SMENUITEM sItemAutoPowerOff_5Minutes = { ITEMID_AUTO_POWER_OFF_5MIN,   IDS_TIME_5MIN,     NULL,   MenuItemAutoPowerOff };
#endif
#endif

// Clock Settings
#if (MENU_GENERAL_CLOCK_SETTING_EN)
SMENUITEM sItemClockSettings        = { ITEMID_CLOCK_SETTINGS,  IDS_DS_CLOCK_SETTINGS,   &sSubClockSettings, 0 };
SMENUITEM sItemClockSettings_Year   = { ITEMID_DATETIME_YEAR,    IDS_DS_DATETIME_Y,    NULL, MenuItemClockSettings };
SMENUITEM sItemClockSettings_Month  = { ITEMID_DATETIME_MONTH,   IDS_DS_DATETIME_M,    NULL, MenuItemClockSettings };
SMENUITEM sItemClockSettings_Day    = { ITEMID_DATETIME_DAY,     IDS_DS_DATETIME_D,    NULL, MenuItemClockSettings };
SMENUITEM sItemClockSettings_Hour   = { ITEMID_DATETIME_HOUR,    IDS_DS_DATETIME_H,    NULL, MenuItemClockSettings };
SMENUITEM sItemClockSettings_Minute = { ITEMID_DATETIME_MINUTE,  IDS_DS_DATETIME_MM,   NULL, MenuItemClockSettings };
SMENUITEM sItemClockSettings_Sec    = { ITEMID_DATETIME_SEC,     IDS_DS_DATETIME_S,    NULL, MenuItemClockSettings };
SMENUITEM sItemClockSettings_OK     = { ITEMID_DATETIME_OK,      IDS_DS_OK,            NULL, MenuItemClockSettings };
SMENUITEM sItemClockSettings_Cancel = { ITEMID_DATETIME_CANCEL,  IDS_DS_CANCEL,        NULL, MenuItemClockSettings };
#endif

// Date/Time Format
#if (MENU_GENERAL_DATE_FORMAT_EN)
SMENUITEM sItemDateTimeFormat       = { ITEMID_DATETIME_FORMAT,  IDS_DS_DATETIME_FORMAT, &sSubDateTimeFormat, 0 };
#if (MENU_GENERAL_DATE_FORMAT_NONE_EN)
SMENUITEM sItemDateTime_None        = { ITEMID_DATETIME_NONE,   IDS_DS_NONE,        NULL, MenuItemDateTimeFormat };
#endif
#if (MENU_GENERAL_DATE_FORMAT_YMD_EN)
SMENUITEM sItemDateTime_YMD         = { ITEMID_DATETIME_YMD,   IDS_DS_DATETIME_YMD,NULL, MenuItemDateTimeFormat };
#endif
#if (MENU_GENERAL_DATE_FORMAT_MDY_EN)
SMENUITEM sItemDateTime_MDY         = { ITEMID_DATETIME_MDY,   IDS_DS_DATETIME_MDY,NULL, MenuItemDateTimeFormat };
#endif
#if (MENU_GENERAL_DATE_FORMAT_DMY_EN)
SMENUITEM sItemDateTime_DMY         = { ITEMID_DATETIME_DMY,   IDS_DS_DATETIME_DMY,NULL, MenuItemDateTimeFormat };
#endif
#endif

// Time/Logo Stamp
#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
SMENUITEM sItemDateLogoStamp        = { ITEMID_DATE_LOGO_STAMP,  IDS_DS_STAMP, &sSubDateLogoStamp, 0 };
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_LOGO_EN)
SMENUITEM sItemStampDateLogo        = { ITEMID_STAMP_DATELOGO,   IDS_DS_STAMP_DATELOGO,    NULL, MenuItemDateLogoStamp };
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_EN)
SMENUITEM sItemStampDate            = { ITEMID_STAMP_DATE,       IDS_DS_STAMP_DATE,        NULL, MenuItemDateLogoStamp };
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_LOGO_EN)
SMENUITEM sItemStampLogo            = { ITEMID_STAMP_LOGO,       IDS_DS_STAMP_LOGO,        NULL, MenuItemDateLogoStamp };
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_OFF_EN)
SMENUITEM sItemStampOFF             = { ITEMID_STAMP_OFF,        IDS_DS_OFF,       NULL, MenuItemDateLogoStamp };
#endif
#endif

// GPS Stamp
#if (MENU_GENERAL_GPS_STAMP_EN)
SMENUITEM sItemGPSStamp         = { ITEMID_GPS_STAMP,                  IDS_DS_STAMP,   &sSubGPSStamp, 0 };
#if (MENU_GENERAL_GPS_STAMP_ON_EN)
SMENUITEM sItemGPSStampOn       = { ITEMID_GPS_STAMP_ON,            IDS_DS_ON,  NULL, MenuItemGPSStamp };
#endif
#if (MENU_GENERAL_GPS_STAMP_OFF_EN)
SMENUITEM sItemGPSStampOff      = { ITEMID_GPS_STAMP_OFF,          IDS_DS_OFF, NULL, MenuItemGPSStamp };
#endif
#endif

// Speed Stamp
#if (MENU_GENERAL_SPEED_STAMP_EN)
SMENUITEM sItemSpeedStamp       = { ITEMID_SPEED_STAMP,          IDS_DS_STAMP,     &sSubSpeedStamp, 0 };
#if (MENU_GENERAL_SPEED_STAMP_ON_EN)
SMENUITEM sItemSpeedStampOn     = { ITEMID_SPEED_STAMP_ON,          IDS_DS_ON,  NULL, MenuItemSpeedStamp };
#endif
#if (MENU_GENERAL_SPEED_STAMP_OFF_EN)
SMENUITEM sItemSpeedStampOff    = { ITEMID_SPEED_STAMP_OFF,        IDS_DS_OFF, NULL, MenuItemSpeedStamp };
#endif
#endif

// Language
#if (MENU_GENERAL_LANGUAGE_EN)
SMENUITEM sItemLanguage             = { ITEMID_LANGUAGE,      IDS_DS_LANGUAGE,                &sSubLanguage, 0 };
#if (MENU_GENERAL_LANGUAGE_ENGLISH_EN)
SMENUITEM sItemLanguage_English     = { ITEMID_LANGUAGES_ENGLISH,   IDS_DS_LANGUAGES_ENGLISH,       NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_SPANISH_EN)
SMENUITEM sItemLanguage_Spanish     = { ITEMID_LANGUAGES_SPANISH,     IDS_DS_LANGUAGES_SPANISH,       NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_PORTUGUESE_EN)
SMENUITEM sItemLanguage_Portuguese  = { ITEMID_LANGUAGES_PORTUGUESE,  IDS_DS_LANGUAGES_PORTUGUESE,    NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_RUSSIAN_EN)
SMENUITEM sItemLanguage_Russian     = { ITEMID_LANGUAGES_RUSSIAN,    IDS_DS_LANGUAGES_RUSSIAN,       NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_SCHINESE_EN)
SMENUITEM sItemLanguage_SChinese    = { ITEMID_LANGUAGES_SCHINESE,  IDS_DS_LANGUAGES_SCHINESE,      NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_TCHINESE_EN)
SMENUITEM sItemLanguage_TChinese    = { ITEMID_LANGUAGES_TCHINESE,  IDS_DS_LANGUAGES_TCHINESE,      NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_GERMAN_EN)
SMENUITEM sItemLanguage_German     = { ITEMID_LANGUAGES_GERMAN,                   IDS_DS_LANGUAGES_GERMAN,        NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_ITALIAN_EN)
SMENUITEM sItemLanguage_Italian    = { ITEMID_LANGUAGES_ITALIAN,                   IDS_DS_LANGUAGES_ITALIAN,       NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_LATVIAN_EN)
SMENUITEM sItemLanguage_Latvian     = { ITEMID_LANGUAGES_LATVIAN,                   IDS_DS_LANGUAGES_LATVIAN,       NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_POLISH_EN)
SMENUITEM sItemLanguage_Polish      = { ITEMID_LANGUAGES_POLISH,    IDS_DS_LANGUAGES_POLISH,        NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_ROMANIAN_EN)
SMENUITEM sItemLanguage_Romanian    = { ITEMID_LANGUAGES_ROMANIAN,                   IDS_DS_LANGUAGES_ROMANIAN,      NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_SLOVAK_EN)
SMENUITEM sItemLanguage_Slovak      = { ITEMID_LANGUAGES_SLOVAK,                   IDS_DS_LANGUAGES_SLOVAK,        NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_UKRANINIAN_EN)
SMENUITEM sItemLanguage_Ukraninian  = { ITEMID_LANGUAGES_UKRANINIAN,                   IDS_DS_LANGUAGES_UKRANINIAN,    NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_FRENCH_EN)
SMENUITEM sItemLanguage_French      = { ITEMID_LANGUAGES_FRENCH,                   IDS_DS_LANGUAGES_FRENCH,        NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_JAPANESE_EN)
SMENUITEM sItemLanguage_Japanese    = { ITEMID_LANGUAGES_JAPANESE,                   IDS_DS_LANGUAGES_JAPANESE,      NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_KOREAN_EN)
SMENUITEM sItemLanguage_Korean      = { ITEMID_LANGUAGES_KOREAN,                   IDS_DS_LANGUAGES_KOREAN,        NULL, MenuItemLanguage };
#endif
#if (MENU_GENERAL_LANGUAGE_CZECH_EN)
SMENUITEM sItemLanguage_Czech       = { ITEMID_LANGUAGES_CZECH,                   IDS_DS_LANGUAGES_CZECH,         NULL, MenuItemLanguage };
#endif
#endif

// Reset Setup
#if (MENU_GENERAL_RESET_SETUP_EN)
SMENUITEM sItemResetSetup           = { ITEMID_RESET_SETUP, IDS_DS_RESET_SETUP, &sSubResetSetup, 0 };
#if (MENU_GENERAL_RESET_SETUP_YES_EN)
SMENUITEM sItemResetSetup_Yes       = { ITEMID_RESET_YES, IDS_DS_YES, NULL, MenuItemResetSetup };
#endif
#if (MENU_GENERAL_RESET_SETUP_NO_EN)
SMENUITEM sItemResetSetup_No        = { ITEMID_RESET_NO,  IDS_DS_NO,  NULL, MenuItemResetSetup };
#endif
#endif

// FW Version Info
#if (MENU_GENERAL_FW_VERSION_EN)
SMENUITEM sItemFWVersionInfo        = { ITEMID_FW_VERSION_INFO, IDS_DS_FW_VERSION_INFO, &sSubFwVersionInfo, 0 };
SMENUITEM sItemFWVersion            = { ITEMID_FW_VERSION,  IDS_DS_FW_VERSION, NULL, MenuItemFwVersion };
#endif

// GPS Status
#if (MENU_GENERAL_GPSINFO_EN)
SMENUITEM sItemGPSInfoChart         = { ITEMID_GPS_INFO_CHART, IDS_DS_GPS_INFO_STATUS, &sSubGPSInfo, 0 };
SMENUITEM sItemGPSInfo              = { ITEMID_GPS_INFO,         IDS_DS_GPS_INFO_STATUS, NULL, MenuItemGPSInfo };
#endif

// Flicker Hz
#if (MENU_GENERAL_FLICKER_EN)
SMENUITEM sItemFlickerHz            = { ITEMID_FLICKER,   IDS_DS_FLICKER,   &sSubFlickerHz, 0 };
#if (MENU_GENERAL_FLICKER_50HZ_EN)
SMENUITEM sItemFlicker50Hz          = { ITEMID_FLICKER_50HZ, IDS_FLICKER_50HZ,     NULL, MenuItemFlickerHz };
#endif
#if (MENU_GENERAL_FLICKER_60HZ_EN)
SMENUITEM sItemFlicker60Hz          = { ITEMID_FLICKER_60HZ, IDS_FLICKER_60HZ,     NULL, MenuItemFlickerHz };
#endif
#endif

// USB Function Selection
#if (MENU_GENERAL_USB_FUNCTION_EN)
SMENUITEM sItemUSBFunction          = { ITEMID_USB_FUNCTION, IDS_USB_FUNCTION, &sSubUSBSelect,     0 };
#if (MENU_GENERAL_USB_FUNCTION_MSDC_EN)
SMENUITEM sItemUSBFunction_MSDC     = { ITEMID_USB_MSDC, IDS_MSDC_MODE,    NULL, MenuItemUSBSelect };
#endif
#if (MENU_GENERAL_USB_FUNCTION_PCAM_EN)
SMENUITEM sItemUSBFunction_PCam     = { ITEMID_USB_PCAM, IDS_PCAM_MODE,    NULL, MenuItemUSBSelect };
#endif
#endif

// LCD Power Save
#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
SMENUITEM sItemLCDPowerSave         = { ITEMID_LCD_POWER_SAVE, IDS_DS_LCD_POWER_SAVE,   &sSubLCDPowerSave,      0 };
#if (MENU_GENERAL_LCD_POWER_SAVE_OFF_EN)
SMENUITEM sItemLCDPowerSave_Off     = { ITEMID_LCD_POWER_SAVE_OFF,  IDS_DS_OFF,      NULL, MenuItemLCDPowerSave };
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN)
SMENUITEM sItemLCDPowerSave_1min    = { ITEMID_LCD_POWER_SAVE_1MIN, IDS_TIME_1MIN,   NULL, MenuItemLCDPowerSave };
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN)
SMENUITEM sItemLCDPowerSave_3min    = { ITEMID_LCD_POWER_SAVE_3MIN, IDS_TIME_3MIN,   NULL, MenuItemLCDPowerSave };
#endif
#endif

// G-sensor Sensitivity, 5 - level
#if (MENU_GENERAL_GSENSOR_EN==GSENSOR_5_LEVEL)

SMENUITEM sItemGsensorSensitivity       = { ITEMID_GSENSOR_SENSITIVITY, IDS_DS_GSENSOR_SENSITIVETY,         &sSubGsensorSensitivity,    0 };

#if (MENU_GENERAL_GSENSOR_OFF_EN)
SMENUITEM sItemGsensorSensitivity_Off   = { ITEMID_GSENSOR_SENSITIVITY_OFF, IDS_DS_OFF,                       NULL, MenuItemGsensorSensitivity };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL0_EN)
SMENUITEM sItemGsensorSensitivity_L0    = { ITEMID_GSENSOR_SENSITIVITY_L0, IDS_DS_GSENSOR_SENSITIVETY_LEVEL0,    NULL, MenuItemGsensorSensitivity };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL1_EN)
SMENUITEM sItemGsensorSensitivity_L1    = { ITEMID_GSENSOR_SENSITIVITY_L1, IDS_DS_GSENSOR_SENSITIVETY_LEVEL1,    NULL, MenuItemGsensorSensitivity };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL2_EN)
SMENUITEM sItemGsensorSensitivity_L2    = { ITEMID_GSENSOR_SENSITIVITY_L2, IDS_DS_GSENSOR_SENSITIVETY_LEVEL2,    NULL, MenuItemGsensorSensitivity };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL3_EN)
SMENUITEM sItemGsensorSensitivity_L3    = { ITEMID_GSENSOR_SENSITIVITY_L3, IDS_DS_GSENSOR_SENSITIVETY_LEVEL3,    NULL, MenuItemGsensorSensitivity };
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL4_EN)
SMENUITEM sItemGsensorSensitivity_L4    = { ITEMID_GSENSOR_SENSITIVITY_L4, IDS_DS_GSENSOR_SENSITIVETY_LEVEL4,    NULL, MenuItemGsensorSensitivity };
#endif
#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_4_LEVEL)
// G-sensor Sensitivity, 4 - level
SMENUITEM sItemGsensorSensitivity       = { ITEMID_GSENSOR_SENSITIVITY, IDS_DS_GSENSOR_SENSITIVETY,         &sSubGsensorSensitivity,    0 };
SMENUITEM sItemGsensorSensitivity_Off   = { ITEMID_GSENSOR_SENSITIVITY_OFF,   IDS_DS_OFF,     NULL, MenuItemGsensorSensitivity };
SMENUITEM sItemGsensorSensitivity_L0    = { ITEMID_GSENSOR_SENSITIVITY_L0,       IDS_DS_HIGH,    NULL, MenuItemGsensorSensitivity };
SMENUITEM sItemGsensorSensitivity_L1    = { ITEMID_GSENSOR_SENSITIVITY_L1,       IDS_DS_MIDDLE,  NULL, MenuItemGsensorSensitivity };
SMENUITEM sItemGsensorSensitivity_L2    = { ITEMID_GSENSOR_SENSITIVITY_L2,       IDS_DS_LOW,     NULL, MenuItemGsensorSensitivity,   0, true, NULL };
SMENUITEM sItemGsensorSensitivity_L4    = { ITEMID_GSENSOR_SENSITIVITY_L4,       IDS_DS_STANDARD,  NULL, MenuItemGsensorSensitivity };
#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_3_LEVEL)
// G-sensor Sensitivity, 3 - level
SMENUITEM sItemGsensorSensitivity       = { ITEMID_GSENSOR_SENSITIVITY, IDS_DS_GSENSOR_SENSITIVETY,         &sSubGsensorSensitivity,    0 };
SMENUITEM sItemGsensorSensitivity_Off   = { ITEMID_GSENSOR_SENSITIVITY_OFF,   IDS_DS_OFF,     NULL, MenuItemGsensorSensitivity };
SMENUITEM sItemGsensorSensitivity_L0    = { ITEMID_GSENSOR_SENSITIVITY_L0,      IDS_DS_HIGH,    NULL, MenuItemGsensorSensitivity };
SMENUITEM sItemGsensorSensitivity_L2    = { ITEMID_GSENSOR_SENSITIVITY_L2,      IDS_DS_MIDDLE,  NULL, MenuItemGsensorSensitivity };
SMENUITEM sItemGsensorSensitivity_L4    = { ITEMID_GSENSOR_SENSITIVITY_L4,      IDS_DS_LOW,     NULL, MenuItemGsensorSensitivity };
#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
SMENUITEM sItemPowerOnGsensorSensitivity    = { ITEMID_GSENSOR_POWERON_SENSITIVITY, IDS_DS_POWERON_GSENSOR_SENSITIVETY,         &sSubPowerOnGsensorSensitivity,     0 };
#if (MENU_GENERAL_POWERON_GSENSOR_OFF_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_Off    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_OFF, IDS_DS_OFF,      NULL, MenuItemGsensorPowerOnSensitivity };
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL0_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_L0    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_L0, IDS_DS_HIGH,      NULL, MenuItemGsensorPowerOnSensitivity };
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL1_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_L1    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_L1, IDS_DS_MIDDLE,    NULL, MenuItemGsensorPowerOnSensitivity };
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL2_EN)
SMENUITEM sItemPowerOnGsensorSensitivity_L2    = { ITEMID_GSENSOR_POWERON_SENSITIVITY_L2, IDS_DS_LOW,   NULL, MenuItemGsensorPowerOnSensitivity };
#endif
#endif
// Motion Detection Sensitivity
#if (MENU_GENERAL_MOTION_DTC_EN)
SMENUITEM sItemMotionDtcSensitivity     = { ITEMID_MOTION_DETECT, IDS_DS_MOTION_DETECTION,  &sSubMotionDtcSensitivity,  0 };
#if (MENU_GENERAL_MOTION_DTC_OFF_EN)
SMENUITEM sItemMotionDtcSensitivity_Off = { ITEMID_MOTION_DETECT_OFF, IDS_DS_OFF,   NULL, MenuItemMotionDtcSensitivity };
#endif
#if (MENU_GENERAL_MOTION_DTC_LOW_EN)
SMENUITEM sItemMotionDtcSensitivity_Low = { ITEMID_MOTION_DETECT_LOW, IDS_DS_LOW,      NULL, MenuItemMotionDtcSensitivity };
#endif
#if (MENU_GENERAL_MOTION_DTC_MID_EN)
SMENUITEM sItemMotionDtcSensitivity_Mid = { ITEMID_MOTION_DETECT_MID, IDS_DS_MIDDLE,NULL, MenuItemMotionDtcSensitivity };
#endif
#if (MENU_GENERAL_MOTION_DTC_HIGH_EN)
SMENUITEM sItemMotionDtcSensitivity_High= { ITEMID_MOTION_DETECT_HIGH, IDS_DS_HIGH,  NULL, MenuItemMotionDtcSensitivity };
#endif
#endif

// Time Zone
#if (MENU_GENERAL_TIME_ZONE_EN)
SMENUITEM sItemTimeZone            = { ITEMID_TIME_ZONE,     IDS_DS_TIME_ZONE,   &sSubTimeZone,  0 };
SMENUITEM sItemTimeZone_M_12       = { ITEMID_TIME_ZONE_GMT_M_12,      IDS_DS_TIME_ZONE_GMT_M_12,   NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_11       = { ITEMID_TIME_ZONE_GMT_M_11,      IDS_DS_TIME_ZONE_GMT_M_11,   NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_10       = { ITEMID_TIME_ZONE_GMT_M_10,      IDS_DS_TIME_ZONE_GMT_M_10,   NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_9        = { ITEMID_TIME_ZONE_GMT_M_9,      IDS_DS_TIME_ZONE_GMT_M_9,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_8        = { ITEMID_TIME_ZONE_GMT_M_8,      IDS_DS_TIME_ZONE_GMT_M_8,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_7        = { ITEMID_TIME_ZONE_GMT_M_7,      IDS_DS_TIME_ZONE_GMT_M_7,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_6        = { ITEMID_TIME_ZONE_GMT_M_6,      IDS_DS_TIME_ZONE_GMT_M_6,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_5        = { ITEMID_TIME_ZONE_GMT_M_5,      IDS_DS_TIME_ZONE_GMT_M_5,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_4        = { ITEMID_TIME_ZONE_GMT_M_4,      IDS_DS_TIME_ZONE_GMT_M_4,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_3_30     = { ITEMID_TIME_ZONE_GMT_M_3_30,     IDS_DS_TIME_ZONE_GMT_M_3_30, NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_3        = { ITEMID_TIME_ZONE_GMT_M_3,          IDS_DS_TIME_ZONE_GMT_M_3,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_2        = { ITEMID_TIME_ZONE_GMT_M_2,          IDS_DS_TIME_ZONE_GMT_M_2,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_M_1        = { ITEMID_TIME_ZONE_GMT_M_1,          IDS_DS_TIME_ZONE_GMT_M_1,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_GMT        = { ITEMID_TIME_ZONE_GMT,           IDS_DS_TIME_ZONE_GMT,        NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_1        = { ITEMID_TIME_ZONE_GMT_P_1,         IDS_DS_TIME_ZONE_GMT_P_1,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_2        = { ITEMID_TIME_ZONE_GMT_P_2,          IDS_DS_TIME_ZONE_GMT_P_2,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_3        = { ITEMID_TIME_ZONE_GMT_P_3,         IDS_DS_TIME_ZONE_GMT_P_3,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_3_30     = { ITEMID_TIME_ZONE_GMT_P_3_30,     IDS_DS_TIME_ZONE_GMT_P_3_30, NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_4        = { ITEMID_TIME_ZONE_GMT_P_4,         IDS_DS_TIME_ZONE_GMT_P_4,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_4_30     = { ITEMID_TIME_ZONE_GMT_P_4_30,     IDS_DS_TIME_ZONE_GMT_P_4_30, NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_5        = { ITEMID_TIME_ZONE_GMT_P_5,          IDS_DS_TIME_ZONE_GMT_P_5,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_5_30     = { ITEMID_TIME_ZONE_GMT_P_5_30,     IDS_DS_TIME_ZONE_GMT_P_5_30, NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_5_45     = { ITEMID_TIME_ZONE_GMT_P_5_45 ,     IDS_DS_TIME_ZONE_GMT_P_5_45, NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_6        = { ITEMID_TIME_ZONE_GMT_P_6 ,          IDS_DS_TIME_ZONE_GMT_P_6,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_6_30     = { ITEMID_TIME_ZONE_GMT_P_6_30 ,    IDS_DS_TIME_ZONE_GMT_P_6_30, NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_7        = { ITEMID_TIME_ZONE_GMT_P_7,          IDS_DS_TIME_ZONE_GMT_P_7,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_8        = { ITEMID_TIME_ZONE_GMT_P_8,         IDS_DS_TIME_ZONE_GMT_P_8,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_9        = { ITEMID_TIME_ZONE_GMT_P_9,          IDS_DS_TIME_ZONE_GMT_P_9,    NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_9_30     = { ITEMID_TIME_ZONE_GMT_P_9_30,     IDS_DS_TIME_ZONE_GMT_P_9_30, NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_10       = { ITEMID_TIME_ZONE_GMT_P_10,         IDS_DS_TIME_ZONE_GMT_P_10,   NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_11       = { ITEMID_TIME_ZONE_GMT_P_11,         IDS_DS_TIME_ZONE_GMT_P_11,   NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_12       = { ITEMID_TIME_ZONE_GMT_P_12,         IDS_DS_TIME_ZONE_GMT_P_12,   NULL, MenuItemTimeZone };
SMENUITEM sItemTimeZone_P_13       = { ITEMID_TIME_ZONE_GMT_P_13,         IDS_DS_TIME_ZONE_GMT_P_13,   NULL, MenuItemTimeZone };
#endif

// Night Mode
#if (MENU_GENERAL_NIGHT_MODE_EN)
SMENUITEM sItemNightMode            = { ITEMID_SCENE,            IDS_DS_NIGHT_MODE,  &sSubNightMode, 0 };
SMENUITEM sItemNightMode_NO         = { ITEMID_SCENE_AUTO,                    IDS_DS_OFF, NULL, MenuItemNightModeSelect };
SMENUITEM sItemNightMode_YES        = { ITEMID_SCENE_TWILIGHT,                 IDS_DS_ON,  NULL, MenuItemNightModeSelect };
#endif

#if (MENU_GENERAL_WIFI_EN)
SMENUITEM sItemWiFiMode             = { ITEMID_WIFI_MODE,            IDS_DS_WIFI, &sSubWiFiMode, 0 };
#if (MENU_GENERAL_WIFI_OFF_EN)
SMENUITEM sItemWiFiMode_NO          = { ITEMID_WIFI_MODE_OFF,   IDS_DS_OFF, NULL, MenuItemWiFiMode };
#endif
#if (MENU_GENERAL_WIFI_ON_EN)
SMENUITEM sItemWiFiMode_YES         = { ITEMID_WIFI_MODE_ON,    IDS_DS_ON,  NULL, MenuItemWiFiMode };
#endif
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN)
SMENUITEM sItemPQContrast       = { ITMEID_PQ_CONTRAST,  IDS_DS_CONTRAST, &sSubPQContrast, 0 };
SMENUITEM sItemPQContrastDec    = { ITMEID_PQ_CONTRAST_DEC,  IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust };
SMENUITEM sItemPQContrastInc    = { ITMEID_PQ_CONTRAST_INC,  IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust };
#endif

#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
SMENUITEM sItemPQBrightness     = { ITEMID_PQ_BRIGHTNESS, IDS_DS_LCD_BRIGHTNESS, &sSubPQBrightness, 0 };
SMENUITEM sItemPQBrightnessDec  = { ITEMID_PQ_BRIGHTNESS_DEC,  IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust };
SMENUITEM sItemPQBrightnessInc  = { ITEMID_PQ_BRIGHTNESS_INC,  IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust };
#endif

#if (MENU_GENERAL_PQ_SATURATION_EN)
SMENUITEM sItemPQSaturation     = { ITEMID_PQ_SATURATION,  IDS_DS_SATURATION, &sSubPQSaturation, 0 };
SMENUITEM sItemPQSaturationDec  = { ITEMID_PQ_SATURATION_DEC,  IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust };
SMENUITEM sItemPQSaturationInc  = { ITEMID_PQ_SATURATION_INC,  IDS_DS_FW_VERSION, NULL, MenuItemPQAdjust };
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
SMENUITEM sItemPQColorTemp      = { ITEMID_PQ_COLORTEMP,  IDS_DS_COLORTEMP, &sSubPQColorTemp, 0 };
SMENUITEM sItemPQColorTemp_Off  = { ITEMID_PQ_COLORTEMP_OFF,  IDS_DS_OFF, NULL, MenuItemPQColorTemp };
SMENUITEM sItemPQColorTemp_MODE1    = { ITEMID_PQ_COLORTEMP_MODE1,  IDS_DS_COLORTEMP_WARMCOLOR, NULL, MenuItemPQColorTemp };
SMENUITEM sItemPQColorTemp_MODE2    = { ITEMID_PQ_COLORTEMP_MODE2,  IDS_DS_COLORTEMP_COOLCOLOR, NULL, MenuItemPQColorTemp };
SMENUITEM sItemPQColorTemp_MODE3    = { ITEMID_PQ_COLORTEMP_MODE3,  IDS_DS_COLORTEMP_WARMCOLOR, NULL, MenuItemPQColorTemp };
SMENUITEM sItemPQColorTemp_MODE4    = { ITEMID_PQ_COLORTEMP_MODE4,  IDS_DS_COLORTEMP_COOLCOLOR, NULL, MenuItemPQColorTemp };
#endif
 /*===========================================================================
 * Global varible : Item List
 *===========================================================================*/
#if (MENU_GENERAL_BEEP_EN)
PSMENUITEM   sMenuListBeep[] =
{
#if (MENU_GENERAL_BEEP_ON_EN)
    &sItemBeep_On,
#endif
#if (MENU_GENERAL_BEEP_OFF_EN)
    &sItemBeep_Off
#endif
};
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_EN)
PSMENUITEM   sMenuListAutoPowerOff[] =
{
#if (MENU_GENERAL_AUTO_POWEROFF_NEVER_EN)
    &sItemAutoPowerOff_Never,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_15SEC_EN)
    &sItemAutoPowerOff_15Second,
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_30SEC_EN)
    &sItemAutoPowerOff_30Second,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_1MIN_EN)
    &sItemAutoPowerOff_1Minutes,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_2MIN_EN)
    &sItemAutoPowerOff_2Minutes,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_3MIN_EN)
    &sItemAutoPowerOff_3Minutes,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_5MIN_EN)
    &sItemAutoPowerOff_5Minutes
#endif
};
#endif

#if (MENU_GENERAL_CLOCK_SETTING_EN)
PSMENUITEM   sMenuListClockSettings[] =
{
    &sItemClockSettings_Year,
    &sItemClockSettings_Month,
    &sItemClockSettings_Day,
    &sItemClockSettings_Hour,
    &sItemClockSettings_Minute,
    &sItemClockSettings_Sec,
    &sItemClockSettings_OK
};
#endif

#if (MENU_GENERAL_DATE_FORMAT_EN)
PSMENUITEM   sMenuListDateTimeFormat[] =
{
#if (MENU_GENERAL_DATE_FORMAT_NONE_EN)
    &sItemDateTime_None,
#endif
#if (MENU_GENERAL_DATE_FORMAT_YMD_EN)
    &sItemDateTime_YMD,
#endif
#if (MENU_GENERAL_DATE_FORMAT_MDY_EN)
    &sItemDateTime_MDY,
#endif
#if (MENU_GENERAL_DATE_FORMAT_DMY_EN)
    &sItemDateTime_DMY
#endif
};
#endif

#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
PSMENUITEM   sMenuListDateLogoStamp[] =
{
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_LOGO_EN)
    &sItemStampDateLogo,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_EN)
    &sItemStampDate,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_LOGO_EN)
    &sItemStampLogo,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_OFF_EN)
    &sItemStampOFF
#endif
};
#endif

#if (MENU_GENERAL_GPS_STAMP_EN)
PSMENUITEM   sMenuListGPSStamp[] =
{
#if (MENU_GENERAL_GPS_STAMP_ON_EN)
    &sItemGPSStampOn,
#endif
#if (MENU_GENERAL_GPS_STAMP_OFF_EN)
    &sItemGPSStampOff,
#endif
};
#endif

#if (MENU_GENERAL_SPEED_STAMP_EN)
PSMENUITEM   sMenuListSpeedStamp[] =
{
#if (MENU_GENERAL_SPEED_STAMP_ON_EN)
    &sItemSpeedStampOn,
#endif
#if (MENU_GENERAL_SPEED_STAMP_OFF_EN)
    &sItemSpeedStampOff,
#endif
};
#endif

#if (MENU_GENERAL_LANGUAGE_EN)

PSMENUITEM   sMenuListLanguage[] =
{
#if (MENU_GENERAL_LANGUAGE_ENGLISH_EN)
    &sItemLanguage_English,
#endif
#if (MENU_GENERAL_LANGUAGE_SPANISH_EN)
    &sItemLanguage_Spanish,
#endif
#if (MENU_GENERAL_LANGUAGE_PORTUGUESE_EN)
    &sItemLanguage_Portuguese,
#endif
#if (MENU_GENERAL_LANGUAGE_RUSSIAN_EN)
    &sItemLanguage_Russian,
#endif
#if (MENU_GENERAL_LANGUAGE_SCHINESE_EN)
    &sItemLanguage_SChinese,
#endif
#if (MENU_GENERAL_LANGUAGE_TCHINESE_EN)
    &sItemLanguage_TChinese,
#endif
#if (MENU_GENERAL_LANGUAGE_GERMAN_EN)
    &sItemLanguage_German,
#endif
#if (MENU_GENERAL_LANGUAGE_ITALIAN_EN)
    &sItemLanguage_Italian,
#endif
#if (MENU_GENERAL_LANGUAGE_LATVIAN_EN)
    &sItemLanguage_Latvian,
#endif
#if (MENU_GENERAL_LANGUAGE_POLISH_EN)
    &sItemLanguage_Polish,
#endif
#if (MENU_GENERAL_LANGUAGE_ROMANIAN_EN)
    &sItemLanguage_Romanian,
#endif
#if (MENU_GENERAL_LANGUAGE_SLOVAK_EN)
    &sItemLanguage_Slovak,
#endif
#if (MENU_GENERAL_LANGUAGE_UKRANINIAN_EN)
    &sItemLanguage_Ukraninian,
#endif
#if (MENU_GENERAL_LANGUAGE_FRENCH_EN)
    &sItemLanguage_French,
#endif
#if (MENU_GENERAL_LANGUAGE_JAPANESE_EN)
    &sItemLanguage_Japanese,
#endif
#if (MENU_GENERAL_LANGUAGE_KOREAN_EN)
    &sItemLanguage_Korean,
#endif
#if (MENU_GENERAL_LANGUAGE_CZECH_EN)
    &sItemLanguage_Czech,
#endif
};

#endif

#if (MENU_GENERAL_RESET_SETUP_EN)
PSMENUITEM   sMenuListResetSetup[] =
{
#if (MENU_GENERAL_RESET_SETUP_YES_EN)
    &sItemResetSetup_Yes,
#endif
#if (MENU_GENERAL_RESET_SETUP_NO_EN)
    &sItemResetSetup_No
#endif
};
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
PSMENUITEM   sMenuListFWVersionInfo[] =
{
    &sItemFWVersion
};
#endif


#if (MENU_GENERAL_GPSINFO_EN)
PSMENUITEM   sMenuListGPSInfo[] =
{
    &sItemGPSInfo
};
#endif

#if (MENU_GENERAL_FLICKER_EN)
PSMENUITEM   sMenuListFlickerHz[] =
{
#if (MENU_GENERAL_FLICKER_50HZ_EN)
    &sItemFlicker50Hz,
#endif
#if (MENU_GENERAL_FLICKER_60HZ_EN)
    &sItemFlicker60Hz
#endif
};
#endif

#if (MENU_GENERAL_USB_FUNCTION_EN)
PSMENUITEM   sMenuListUSBFunction[] =
{
#if (MENU_GENERAL_USB_FUNCTION_MSDC_EN)
    &sItemUSBFunction_MSDC,
#endif
#if (MENU_GENERAL_USB_FUNCTION_PCAM_EN)
    &sItemUSBFunction_PCam
#endif
};
#endif

#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
PSMENUITEM   sMenuListLCDPowerSave[] =
{
#if (MENU_GENERAL_LCD_POWER_SAVE_OFF_EN)
    &sItemLCDPowerSave_Off,
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN)
    &sItemLCDPowerSave_1min,
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN)
    &sItemLCDPowerSave_3min
#endif
};
#endif

#if (MENU_GENERAL_GSENSOR_EN==GSENSOR_5_LEVEL)
PSMENUITEM   sMenuListGsensorSensitivity[] =
{
#if (MENU_GENERAL_GSENSOR_OFF_EN)
    &sItemGsensorSensitivity_Off,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL0_EN)
    &sItemGsensorSensitivity_L0,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL1_EN)
    &sItemGsensorSensitivity_L1,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL2_EN)
    &sItemGsensorSensitivity_L2,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL3_EN)
    &sItemGsensorSensitivity_L3,
#endif
#if (MENU_GENERAL_GSENSOR_LEVEL4_EN)
    &sItemGsensorSensitivity_L4
#endif
};

#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_4_LEVEL)

PSMENUITEM   sMenuListGsensorSensitivity[] =
{
    &sItemGsensorSensitivity_Off,
    &sItemGsensorSensitivity_L0,    // High
    &sItemGsensorSensitivity_L2,    // Middle
    &sItemGsensorSensitivity_L3,    // Low
    &sItemGsensorSensitivity_L4     // Standard
};

#elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_3_LEVEL)

PSMENUITEM   sMenuListGsensorSensitivity[] =
{
    &sItemGsensorSensitivity_Off,
    &sItemGsensorSensitivity_L0,
    &sItemGsensorSensitivity_L2,
    &sItemGsensorSensitivity_L4
};
#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
PSMENUITEM   sMenuListPowerOnGsensorSensitivity[] =
{
#if (MENU_GENERAL_POWERON_GSENSOR_OFF_EN)
    &sItemPowerOnGsensorSensitivity_Off,
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL0_EN)
    &sItemPowerOnGsensorSensitivity_L0,
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL1_EN)
    &sItemPowerOnGsensorSensitivity_L1,
#endif
#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL2_EN)
    &sItemPowerOnGsensorSensitivity_L2
#endif
};
#endif

#if (MENU_GENERAL_MOTION_DTC_EN)
PSMENUITEM   sMenuListMotionDtcSensitivity[] =
{
#if (MENU_GENERAL_MOTION_DTC_OFF_EN)
    &sItemMotionDtcSensitivity_Off,
#endif
#if (MENU_GENERAL_MOTION_DTC_LOW_EN)
    &sItemMotionDtcSensitivity_Low,
#endif
#if (MENU_GENERAL_MOTION_DTC_MID_EN)
    &sItemMotionDtcSensitivity_Mid,
#endif
#if (MENU_GENERAL_MOTION_DTC_HIGH_EN)
    &sItemMotionDtcSensitivity_High,
#endif
};
#endif

#if (MENU_GENERAL_TIME_ZONE_EN)
PSMENUITEM   sMenuListTimeZone[] =
{
    &sItemTimeZone_M_12,
    &sItemTimeZone_M_11,
    &sItemTimeZone_M_10,
    &sItemTimeZone_M_9,
    &sItemTimeZone_M_8,
    &sItemTimeZone_M_7,
    &sItemTimeZone_M_6,
    &sItemTimeZone_M_5,
    &sItemTimeZone_M_4,
    &sItemTimeZone_M_3_30,
    &sItemTimeZone_M_3,
    &sItemTimeZone_M_2,
    &sItemTimeZone_M_1,
    &sItemTimeZone_GMT,
    &sItemTimeZone_P_1,
    &sItemTimeZone_P_2,
    &sItemTimeZone_P_3,
    &sItemTimeZone_P_3_30,
    &sItemTimeZone_P_4,
    &sItemTimeZone_P_4_30,
    &sItemTimeZone_P_5,
    &sItemTimeZone_P_5_30,
    &sItemTimeZone_P_5_45,
    &sItemTimeZone_P_6,
    &sItemTimeZone_P_6_30,
    &sItemTimeZone_P_7,
    &sItemTimeZone_P_8,
    &sItemTimeZone_P_9,
    &sItemTimeZone_P_9_30,
    &sItemTimeZone_P_10,
    &sItemTimeZone_P_11,
    &sItemTimeZone_P_12,
    &sItemTimeZone_P_13
};
#endif

#if (MENU_GENERAL_NIGHT_MODE_EN)
PSMENUITEM   sMenuListNightMode[] =
{
    &sItemNightMode_NO,
    &sItemNightMode_YES
};
#endif

#if (MENU_GENERAL_WIFI_EN)
PSMENUITEM   sMenuListWiFiMode[] =
{
#if (MENU_GENERAL_WIFI_ON_EN)
    &sItemWiFiMode_YES,
#endif
#if (MENU_GENERAL_WIFI_OFF_EN)
    &sItemWiFiMode_NO
#endif
};
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN)
PSMENUITEM   sMenuListPQContrast[] =
{
    &sItemPQContrastDec,
    &sItemPQContrastInc
};
#endif

#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
PSMENUITEM   sMenuListPQBrightness[] =
{
    &sItemPQBrightnessDec,
    &sItemPQBrightnessInc
};
#endif

#if (MENU_GENERAL_PQ_SATURATION_EN)
PSMENUITEM   sMenuListPQSaturation[] =
{
    &sItemPQSaturationDec,
    &sItemPQSaturationInc
};
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
PSMENUITEM   sMenuListPQColorTemp[] =
{
#if (MENU_GENERAL_PQ_COLORTEMP_OFF_EN)
    &sItemPQColorTemp_Off,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE1_EN)
    &sItemPQColorTemp_MODE1,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE2_EN)
    &sItemPQColorTemp_MODE2,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE3_EN)
    &sItemPQColorTemp_MODE3,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_MODE4_EN)
    &sItemPQColorTemp_MODE4
#endif
};
#endif

PSMENUITEM   sMenuListMainGeneral[]=
{
#if (MENU_GENERAL_BEEP_EN)
    &sItemBeep,
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_EN)
    &sItemAutoPowerOff,
#endif
#if (MENU_GENERAL_CLOCK_SETTING_EN)
    &sItemClockSettings,
#endif
#if (MENU_GENERAL_DATE_FORMAT_EN)
    &sItemDateTimeFormat,
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
    &sItemDateLogoStamp,
#endif
#if (MENU_GENERAL_GPS_STAMP_EN)
    &sItemGPSStamp,
#endif
#if (MENU_GENERAL_SPEED_STAMP_EN)
    &sItemSpeedStamp,
#endif
#if (MENU_GENERAL_LANGUAGE_EN)
    &sItemLanguage,
#endif
#if (MENU_GENERAL_FLICKER_EN)
    &sItemFlickerHz,
#endif
#if (MENU_GENERAL_USB_FUNCTION_EN)
    &sItemUSBFunction,
#endif
#if (MENU_GENERAL_GSENSOR_EN)
    &sItemGsensorSensitivity,
#endif
#if (MENU_GENERAL_POWERON_GSENSOR_EN)
    &sItemPowerOnGsensorSensitivity,
#endif
#if (MENU_GENERAL_MOTION_DTC_EN)
    &sItemMotionDtcSensitivity,
#endif
#if (MENU_GENERAL_GPSINFO_EN)
    &sItemGPSInfoChart,
#endif
#if (MENU_GENERAL_TIME_ZONE_EN)
    &sItemTimeZone,
#endif
#if (MENU_GENERAL_RESET_SETUP_EN)
    &sItemResetSetup,
#endif
#if (MENU_GENERAL_NIGHT_MODE_EN)
    &sItemNightMode,
#endif
#if (MENU_GENERAL_WIFI_EN)
    &sItemWiFiMode,
#endif
#if (MENU_GENERAL_FW_VERSION_EN)
    &sItemFWVersionInfo,
#endif
#if (MENU_GENERAL_PQ_CONTRAST_EN)
    &sItemPQContrast,
#endif
#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
    &sItemPQBrightness,
#endif
#if (MENU_GENERAL_PQ_SATURATION_EN)
    &sItemPQSaturation,
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_EN)
    &sItemPQColorTemp,
#endif
};
 /*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/
SMENUSTRUCT   sMainMenuGeneral =
{
    MENUID_MAIN_MENU_GENERAL,
    IDS_DS_GENERAL_SETTINGS,
    NULL,
    sizeof(sMenuListMainGeneral)/sizeof(PSMENUITEM),
    sMenuListMainGeneral,
    NULL,
};
//--------------SUB MENU-------------------

#if (MENU_GENERAL_BEEP_EN)
SMENUSTRUCT sSubBeep =
{
    MENUID_SUB_MENU_BEEP,
    IDS_DS_BEEP,
    &sMainMenuGeneral,
    sizeof(sMenuListBeep)/sizeof(PSMENUITEM),
    sMenuListBeep,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_EN)
SMENUSTRUCT sSubAutoPowerOff =
{
    MENUID_SUB_MENU_AUTO_POWER_OFF,
    IDS_DS_POWER_OFF,
    &sMainMenuGeneral,
    sizeof(sMenuListAutoPowerOff)/sizeof(PSMENUITEM),
    sMenuListAutoPowerOff,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_CLOCK_SETTING_EN)
SMENUSTRUCT sSubClockSettings =
{
    MENUID_SUB_MENU_CLOCK_SETTINGS,
    IDS_DS_CLOCK_SETTINGS,
    &sMainMenuGeneral,
    sizeof(sMenuListClockSettings)/sizeof(PSMENUITEM),
    sMenuListClockSettings,
    NULL,
};
#endif

#if (MENU_GENERAL_DATE_FORMAT_EN)
SMENUSTRUCT sSubDateTimeFormat =
{
    MENUID_SUB_MENU_DATETIME_FORMAT,
    IDS_DS_DATETIME_FORMAT,
    &sMainMenuGeneral,
    sizeof(sMenuListDateTimeFormat)/sizeof(PSMENUITEM),
    sMenuListDateTimeFormat,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
SMENUSTRUCT sSubDateLogoStamp =
{
    MENUID_SUB_MENU_DATELOGO_STAMP,
    IDS_DS_STAMP,
    &sMainMenuGeneral,
    sizeof(sMenuListDateLogoStamp)/sizeof(PSMENUITEM),
    sMenuListDateLogoStamp,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_GPS_STAMP_EN)
SMENUSTRUCT sSubGPSStamp =
{
    MENUID_SUB_MENU_GPS_STAMP,
    IDS_DS_STAMP,
    &sMainMenuGeneral,
    sizeof(sMenuListGPSStamp)/sizeof(PSMENUITEM),
    sMenuListGPSStamp,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_SPEED_STAMP_EN)
SMENUSTRUCT sSubSpeedStamp =
{
    MENUID_SUB_MENU_SPEED_STAMP,
    IDS_DS_STAMP,
    &sMainMenuGeneral,
    sizeof(sMenuListSpeedStamp)/sizeof(PSMENUITEM),
    sMenuListSpeedStamp,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_LANGUAGE_EN)
SMENUSTRUCT sSubLanguage =
{
    MENUID_SUB_MENU_LANGUAGE,
    IDS_DS_LANGUAGE,
    &sMainMenuGeneral,
    sizeof(sMenuListLanguage)/sizeof(PSMENUITEM),
    sMenuListLanguage,
    MenuGetDefault_GeneralSetting,
};

SMENUSTRUCT sMainLanguage =
{
    MENUID_SUB_MENU_LANGUAGE,
    IDS_DS_LANGUAGE,
    &sMainMenuGeneral,
    sizeof(sMenuListLanguage)/sizeof(PSMENUITEM),
    sMenuListLanguage,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_RESET_SETUP_EN)
SMENUSTRUCT sSubResetSetup =
{
    MENUID_SUB_MENU_RESET_SETUP,
    IDS_DS_RESET_SETUP,
    &sMainMenuGeneral,
    sizeof(sMenuListResetSetup)/sizeof(PSMENUITEM),
    sMenuListResetSetup,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
SMENUSTRUCT sSubFwVersionInfo =
{
    MENUID_SUB_MENU_FW_VERSION_INFO,
    IDS_DS_FW_VERSION_INFO,
    &sMainMenuGeneral,
    sizeof(sMenuListFWVersionInfo)/sizeof(PSMENUITEM),
    sMenuListFWVersionInfo,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_GPSINFO_EN)
SMENUSTRUCT sSubGPSInfo =
{
    MENUID_SUB_MENU_GPS_INFO,
    IDS_DS_GPS_INFO_STATUS,
    &sMainMenuGeneral,
    sizeof(sMenuListGPSInfo)/sizeof(PSMENUITEM),
    sMenuListGPSInfo,
    NULL,
};
#endif

#if (MENU_GENERAL_FLICKER_EN)
SMENUSTRUCT sSubFlickerHz =
{
    MENUID_SUB_MENU_FLICKER_FREQUENCY,
    IDS_DS_FLICKER,
    &sMainMenuGeneral,
    sizeof(sMenuListFlickerHz)/sizeof(PSMENUITEM),
    sMenuListFlickerHz,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_USB_FUNCTION_EN)
SMENUSTRUCT sSubUSBSelect =
{
    MENUID_SUB_MENU_USB_FUNCTION,
    IDS_USB_FUNCTION,
    &sMainMenuGeneral,
    sizeof(sMenuListUSBFunction)/sizeof(PSMENUITEM),
    sMenuListUSBFunction,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
SMENUSTRUCT sSubLCDPowerSave =
{
    MENUID_SUB_MENU_LCD_POWER_SAVE,
    IDS_DS_LCD_POWER_SAVE,
    &sMainMenuGeneral,
    sizeof(sMenuListLCDPowerSave)/sizeof(PSMENUITEM),
    sMenuListLCDPowerSave,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_GSENSOR_EN)
SMENUSTRUCT sSubGsensorSensitivity =
{
    MENUID_SUB_MENU_GSENSOR_SENSITIVITY,
    IDS_DS_GSENSOR_SENSITIVETY,
    &sMainMenuGeneral,
    sizeof(sMenuListGsensorSensitivity)/sizeof(PSMENUITEM),
    sMenuListGsensorSensitivity,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
SMENUSTRUCT sSubPowerOnGsensorSensitivity =
{
    MENUID_SUB_MENU_GSENSOR_POWERON_SENSITIVITY,
    IDS_DS_POWERON_GSENSOR_SENSITIVETY,
    &sMainMenuGeneral,
    sizeof(sMenuListPowerOnGsensorSensitivity)/sizeof(PSMENUITEM),
    sMenuListPowerOnGsensorSensitivity,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_MOTION_DTC_EN)
SMENUSTRUCT sSubMotionDtcSensitivity =
{
    MENUID_SUB_MENU_MOTION_DTC_SENSITIVITY,
    IDS_DS_MOTION_DETECTION,
    &sMainMenuGeneral,
    sizeof(sMenuListMotionDtcSensitivity)/sizeof(PSMENUITEM),
    sMenuListMotionDtcSensitivity,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_TIME_ZONE_EN)
SMENUSTRUCT sSubTimeZone =
{
    MENUID_SUB_MENU_TIME_ZONE,
    IDS_DS_TIME_ZONE,
    &sMainMenuGeneral,
    sizeof(sMenuListTimeZone)/sizeof(PSMENUITEM),
    sMenuListTimeZone,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_NIGHT_MODE_EN)
SMENUSTRUCT sSubNightMode =
{
    MENUID_SUB_MENU_NIGHT_MODE,
    IDS_DS_NIGHT_MODE,
     &sMainMenuGeneral,
    sizeof(sMenuListNightMode)/sizeof(PSMENUITEM),
    sMenuListNightMode,
    MenuGetDefault_GeneralSetting,
};
#endif
#if (MENU_GENERAL_WIFI_EN)
SMENUSTRUCT sSubWiFiMode =
{
    MENUID_SUB_MENU_WIFI_MODE,
    IDS_DS_WIFI,
    &sMainMenuGeneral,
    sizeof(sMenuListWiFiMode)/sizeof(PSMENUITEM),
    sMenuListWiFiMode,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN)
SMENUSTRUCT sSubPQContrast =
{
    MENUID_SUB_MENU_PQ_CONTRAST,
    IDS_DS_CONTRAST,
    &sMainMenuGeneral,
    sizeof(sMenuListPQContrast)/sizeof(PSMENUITEM),
    sMenuListPQContrast,
    MenuGetDefault_GeneralSetting,

};
#endif

#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
SMENUSTRUCT sSubPQBrightness =
{
    MENUID_SUB_MENU_PQ_BRIGHTNESS,
    IDS_DS_FW_VERSION_INFO,
    &sMainMenuGeneral,
    sizeof(sMenuListPQBrightness)/sizeof(PSMENUITEM),
    sMenuListPQBrightness,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_PQ_SATURATION_EN)
SMENUSTRUCT sSubPQSaturation =
{
    MENUID_SUB_MENU_PQ_SATURATION,
    IDS_DS_SATURATION,
    &sMainMenuGeneral,
    sizeof(sMenuListPQSaturation)/sizeof(PSMENUITEM),
    sMenuListPQSaturation,
    MenuGetDefault_GeneralSetting,
};
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
SMENUSTRUCT sSubPQColorTemp =
{
    MENUID_SUB_MENU_PQ_COLORTEMP,
    IDS_DS_COLORTEMP,
    &sMainMenuGeneral,
    sizeof(sMenuListPQColorTemp)/sizeof(PSMENUITEM),
    sMenuListPQColorTemp,
    MenuGetDefault_GeneralSetting,
};
#endif
 /*===========================================================================
 * Main body
 *===========================================================================*/
 #if (MENU_GENERAL_BEEP_EN)
bool MenuItemBeep(PSMENUITEM pItem)
{
	char Longstr[16] = "";
    MenuSettingConfig()->uiBeep = pItem->iItemId - ITEMID_BEEP-1;
            if(!MenuSettingConfig()->uiBeep)
            	sprintf(Longstr,"voice 1");
            else
            {
             sprintf(Longstr,"voice 0");
            }
                printf("[pItem->iItemId] == %d\n",MenuSettingConfig()->uiBeep);// lyj add
                Carimpl_Send2Fifo(Longstr, sizeof(Longstr));
        return true;

}
#endif

#if (MENU_GENERAL_AUTO_POWEROFF_EN)
bool MenuItemAutoPowerOff(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiAutoPowerOff = pItem->iItemId - ITEMID_AUTO_POWER_OFF-1;
    return true;
}
#endif

#if (MENU_GENERAL_CLOCK_SETTING_EN)
bool MenuItemClockSettings(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_GENERAL_DATE_FORMAT_EN)
bool MenuItemDateTimeFormat(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiDateTimeFormat = pItem->iItemId - ITEMID_DATETIME_FORMAT-1;
    return true;
}
#endif

#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
bool MenuItemDateLogoStamp(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiDateLogoStamp = pItem->iItemId - ITEMID_DATE_LOGO_STAMP-1;
    return true;
}
#endif

#if (MENU_GENERAL_GPS_STAMP_EN)
bool MenuItemGPSStamp(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiGPSStamp = pItem->iItemId - ITEMID_GPS_STAMP-1;
    return true;
}
#endif

#if (MENU_GENERAL_SPEED_STAMP_EN)
bool MenuItemSpeedStamp(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiSpeedStamp = pItem->iItemId - ITEMID_SPEED_STAMP-1;
    return true;
}
#endif

#if (MENU_GENERAL_LANGUAGE_EN)
bool MenuItemLanguage(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiLanguage = pItem->iItemId - ITEMID_LANGUAGE-1;
    return true;
}
#endif

#if (MENU_GENERAL_RESET_SETUP_EN)
bool MenuItemResetSetup(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiResetSetting = pItem->iItemId - ITEMID_RESET_SETUP -1;
    return true;
}
#endif

#if (MENU_GENERAL_FW_VERSION_EN)
bool MenuItemFwVersion(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_GENERAL_GPSINFO_EN)
bool MenuItemGPSInfo(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_GENERAL_FLICKER_EN)
bool MenuItemFlickerHz(PSMENUITEM pItem)
{
	 char Longstr[16] = "";
    MenuSettingConfig()->uiFlickerHz = pItem->iItemId - ITEMID_FLICKER -1;



        if(!MenuSettingConfig()->uiFlickerHz)
        	sprintf(Longstr,"flicker 50");
        else
        {
         sprintf(Longstr,"flicker 60");
        }
            printf("[pItem->iItemId] == %d\n",MenuSettingConfig()->uiFlickerHz);// lyj add
            Carimpl_Send2Fifo(Longstr, sizeof(Longstr));
    return true;
}
#endif

#if (MENU_GENERAL_USB_FUNCTION_EN)
bool MenuItemUSBSelect(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiUSBFunction = pItem->iItemId - ITEMID_USB_FUNCTION -1;
    return true;
}
#endif

#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
bool MenuItemLCDPowerSave(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiLCDPowerSave = pItem->iItemId - ITEMID_LCD_POWER_SAVE-1;
    return true;
}
#endif

#if (MENU_GENERAL_GSENSOR_EN)
bool MenuItemGsensorSensitivity(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiGsensorSensitivity = pItem->iItemId - ITEMID_GSENSOR_SENSITIVITY-1;
    return true;
}
#endif

#if (MENU_GENERAL_POWERON_GSENSOR_EN)
bool MenuItemGsensorPowerOnSensitivity(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiGsensorSensitivity = pItem->iItemId - ITEMID_GSENSOR_SENSITIVITY-1;
    return true;
}
#endif

#if (MENU_GENERAL_MOTION_DTC_EN)
bool MenuItemMotionDtcSensitivity(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiMotionDtcSensitivity = pItem->iItemId - ITEMID_MOTION_DETECT-1;
    return true;
}
#endif

#if (MENU_GENERAL_TIME_ZONE_EN)
bool MenuItemTimeZone(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiTimeZone = pItem->iItemId - ITEMID_TIME_ZONE-1;
    return true;
}
#endif

#if(MENU_GENERAL_WIFI_EN)
bool MenuItemWiFiMode(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiWifi = pItem->iItemId - ITEMID_WIFI_MODE-1;
    return true;
}
#endif

#if (MENU_GENERAL_PQ_CONTRAST_EN || MENU_GENERAL_PQ_BRIGHTNESS_EN || MENU_GENERAL_PQ_SATURATION_EN)
bool MenuItemPQAdjust(PSMENUITEM pItem)
{
    return true;
}
#endif

#if (MENU_GENERAL_PQ_COLORTEMP_EN)
bool MenuItemPQColorTemp(PSMENUITEM pItem)
{
    return true;
}
#endif
int   MenuGetDefault_GeneralSetting(PSMENUSTRUCT pMenu )
{
	int DefaultValue = 0;

    switch( pMenu->iMenuId )
    {
#if (MENU_GENERAL_BEEP_EN)
        case MENUID_SUB_MENU_BEEP:
            DefaultValue = MenuSettingConfig()->uiBeep;
            break;
#endif
#if (MENU_GENERAL_LCD_BRIGHTNESS_EN)
        case MENUID_SUB_MENU_LCD_BRIGHTNESS:
            DefaultValue = MenuSettingConfig()->uiLCDBrightness;
            break;
#endif
#if (MENU_GENERAL_AUTO_POWEROFF_EN)
        case MENUID_SUB_MENU_AUTO_POWER_OFF:
            DefaultValue = MenuSettingConfig()->uiAutoPowerOff;
            break;
#endif
#if (MENU_GENERAL_DATE_FORMAT_EN)
        case MENUID_SUB_MENU_DATETIME_FORMAT:
            DefaultValue = MenuSettingConfig()->uiDateTimeFormat;
            break;
#endif
#if (MENU_GENERAL_DATE_LOGO_STAMP_EN)
        case MENUID_SUB_MENU_DATELOGO_STAMP:
            DefaultValue = MenuSettingConfig()->uiDateLogoStamp;
            break;
#endif
#if (MENU_GENERAL_GPS_STAMP_EN)
        case MENUID_SUB_MENU_GPS_STAMP:
            DefaultValue = MenuSettingConfig()->uiGPSStamp;
            break;
#endif
#if (MENU_GENERAL_SPEED_STAMP_EN)
        case MENUID_SUB_MENU_SPEED_STAMP:
            DefaultValue = MenuSettingConfig()->uiSpeedStamp;
            break;
#endif
#if (MENU_GENERAL_LANGUAGE_EN)
        case MENUID_SUB_MENU_LANGUAGE:
            DefaultValue = MenuSettingConfig()->uiLanguage;
            break;
#endif
#if (MENU_GENERAL_FLICKER_EN)
        case MENUID_SUB_MENU_FLICKER_FREQUENCY:
            DefaultValue = MenuSettingConfig()->uiFlickerHz;
            break;
#endif
#if (MENU_GENERAL_USB_FUNCTION_EN)
        case MENUID_SUB_MENU_USB_FUNCTION:
            DefaultValue = MenuSettingConfig()->uiUSBFunction;
            break;
#endif
#if (MENU_GENERAL_LCD_POWER_SAVE_EN)
        case MENUID_SUB_MENU_LCD_POWER_SAVE:
            DefaultValue = MenuSettingConfig()->uiLCDPowerSave;
            break;
#endif
#if (MENU_GENERAL_GSENSOR_EN)
        case MENUID_SUB_MENU_GSENSOR_SENSITIVITY:
            DefaultValue = MenuSettingConfig()->uiGsensorSensitivity;
            break;
#endif
#if (MENU_GENERAL_POWERON_GSENSOR_EN)
        case MENUID_SUB_MENU_GSENSOR_POWERON_SENSITIVITY:
            DefaultValue = MenuSettingConfig()->uiPowerOnGsensorSensitivity;
            break;
#endif
#if (MENU_GENERAL_MOTION_DTC_EN)
        case MENUID_SUB_MENU_MOTION_DTC_SENSITIVITY:
            DefaultValue = MenuSettingConfig()->uiMotionDtcSensitivity;
            break;
#endif
#if (MENU_GENERAL_TIME_ZONE_EN)
         case MENUID_SUB_MENU_TIME_ZONE:
            DefaultValue = MenuSettingConfig()->uiTimeZone;
            break;
#endif
#if (MENU_GENERAL_NIGHT_MODE_EN)
        case MENUID_SUB_MENU_NIGHT_MODE:
            DefaultValue = MenuSettingConfig()->uiScene;
            break;
#endif
#if (MENU_GENERAL_WIFI_EN)
        case MENUID_SUB_MENU_WIFI_MODE:
            DefaultValue = MenuSettingConfig()->uiWifi;
            break;
#endif
#if MENU_GENERAL_FW_VERSION_EN
        case MENUID_SUB_MENU_FW_VERSION_INFO:
            DefaultValue = MenuSettingConfig()->uiVersion;
            break;
#endif
#if (MENU_GENERAL_PQ_CONTRAST_EN)
        case MENUID_SUB_MENU_PQ_CONTRAST:
        break;
#endif
#if (MENU_GENERAL_PQ_BRIGHTNESS_EN)
        case MENUID_SUB_MENU_PQ_BRIGHTNESS:
        break;
#endif
#if (MENU_GENERAL_PQ_SATURATION_EN)
        case MENUID_SUB_MENU_PQ_SATURATION:
        break;
#endif
#if (MENU_GENERAL_PQ_COLORTEMP_EN)
        case MENUID_SUB_MENU_PQ_COLORTEMP:
        break;
#endif
    }
    return DefaultValue;
}
