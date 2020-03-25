/*===========================================================================
 * Include file
 *===========================================================================*/
#include <string.h>
#include "MenuCommon.h"

/*===========================================================================
 * Local function
 *===========================================================================*/
static int MenuSetting_Get_General(int icur_val, va_list *ap);
static int ParamFun(SETTING_ATOM *pa, int idx, char *szVal, void *arg);
 /*===========================================================================
 * Extern varible
 *===========================================================================*/

  /*===========================================================================
 * Global varible :
 *===========================================================================*/
static MenuInfo gCurMenuInfo = {0};

static MENU_ATOMS  temp_menu_atoms;
static MENU_ATOMS  menu_atoms =
{
    MAGIC_NUM,
    HDRTAIL_NUM,
	{
        // Still
        {/* 000 */COMMON_KEY_STILL_CAP_SIZE, 3, MENU_STILL_SIZE_EN, ParamFun, MenuSetting_Get_General,
        	{
			#if (MENU_STILL_SIZE_30M_EN)
			"30M",	IMAGE_SIZE_30M,     ///< 6400*4800
			#endif
			#if (MENU_STILL_SIZE_14M_EN)
			"14M",	IMAGE_SIZE_14M,     ///< 4352*3264
			#endif
			#if (MENU_STILL_SIZE_12M_EN)
			"12M",	IMAGE_SIZE_12M,     ///< 4000*3000
			#endif
			#if (MENU_STILL_SIZE_8M_EN)
			"8M",	IMAGE_SIZE_8M,      ///< 3264*2448
			#endif
			#if (MENU_STILL_SIZE_6M_WIDE_EN)
			"6M WIDE",	IMAGE_SIZE_6M_WIDE, ///<
			#endif
			#if (MENU_STILL_SIZE_6M_EN)
			"6M",	IMAGE_SIZE_6M,      ///<
			#endif
			#if (MENU_STILL_SIZE_5M_EN)
			"5M",	IMAGE_SIZE_5M,      ///< 2560*1920
			#endif
			#if (MENU_STILL_SIZE_3M_EN)
			"3M",	IMAGE_SIZE_3M,      ///< 2048*1536
			#endif
			#if (MENU_STILL_SIZE_2M_WIDE_EN)
			"2M WIDE",	IMAGE_SIZE_2M,      ///< 1920*1080
			#endif
			#if (MENU_STILL_SIZE_1d2M_EN)
			"1.2M", IMAGE_SIZE_1_2M,    ///< 1280*960
			#endif
			#if (MENU_STILL_SIZE_VGA_EN)
			"VGA", IMAGE_SIZE_VGA,     ///< 640*480
			#endif
        	NULL, 0
        	},
        },
        {/* 001 */COMMON_KEY_STILL_QUALITY, 0, MENU_STILL_QUALITY_EN, ParamFun, MenuSetting_Get_General,
        	{
			#if (MENU_STILL_QUALITY_SUPER_FINE_EN || MENU_MOVIE_QUALITY_SUPER_FINE_EN)
			"Super Fine", QUALITY_SUPER_FINE,
			#endif
			#if (MENU_STILL_QUALITY_FINE_EN || MENU_MOVIE_QUALITY_FINE_EN)
			"Fine", QUALITY_FINE,
			#endif
        	NULL, 0
        	},
        },
        {/* 002 */COMMON_KEY_BURST_SHOT,	0, MENU_STILL_BURST_SHOT_EN, ParamFun, NULL,
        	{NULL, 0},
        },
		// Movie
        {/* 003 */COMMON_KEY_MOVIE_SIZE, 0, MENU_MOVIE_SIZE_EN, ParamFun, MenuSetting_Get_General,
        	{
			#if MENU_MOVIE_SIZE_4K_24P_EN
			"4K24fps", MOVIE_SIZE_4K_24P,
			#endif
			#if(MENU_MOVIE_SIZE_1440_30P_EN)
			"1440P30fps", MOVIE_SIZE_1440_30P,
			#endif
			#if MENU_MOVIE_SIZE_SHD_30P_EN
			"1296P30fps", MOVIE_SIZE_SHD_30P,
			#endif
			#if MENU_MOVIE_SIZE_SHD_25P_EN
			"1296P25fps", MOVIE_SIZE_SHD_25P,
			#endif
			#if MENU_MOVIE_SIZE_1080P_30_HDR_EN
			"1080P30fps_hdr", MOVIE_SIZE_1080_30P_HDR,
			#endif
			#if MENU_MOVIE_SIZE_1080_60P_EN
			"1080P60fps", MOVIE_SIZE_1080_60P,
			#endif
			#if MENU_MOVIE_SIZE_1080_25P_EN
			"1080P25fps", MOVIE_SIZE_1080_25P,
			#endif
			#if MENU_MOVIE_SIZE_1080P_EN
			"1080P30fps", MOVIE_SIZE_1080P,
			#endif
			#if (MENU_MOVIE_SIZE_960P_30P_EN)
			"960P30fps", MOVIE_SIZE_960P_30P,
			#endif
			#if MENU_MOVIE_SIZE_900P_30P_EN
			"900P30fps", MOVIE_SIZE_900P_30P,
			#endif
			#if MENU_MOVIE_SIZE_720P_EN
			"720P30fps", MOVIE_SIZE_720P,
			#endif
			#if MENU_MOVIE_SIZE_720_120P_EN
			"720P120fps", MOVIE_SIZE_720_120P,
			#endif
			#if MENU_MOVIE_SIZE_720_60P_EN
			"720P60fps", MOVIE_SIZE_720_60P,
			#endif
			#if MENU_MOVIE_SIZE_720_50P_EN
			"720P50fps", MOVIE_SIZE_720_50P,
			#endif
			#if MENU_MOVIE_SIZE_VGA30P_EN
			"360P30fps", MOVIE_SIZE_VGA30P,
			#endif
			NULL, 0,
        	}
        },
        {/* 004 */COMMON_KEY_MOVIE_QUALITY, 0, MENU_MOVIE_QUALITY_EN, ParamFun, MenuSetting_Get_General,
			{
			#if (MENU_STILL_QUALITY_SUPER_FINE_EN || MENU_MOVIE_QUALITY_SUPER_FINE_EN)
			"Super Fine", QUALITY_SUPER_FINE,
			#endif
			#if (MENU_STILL_QUALITY_FINE_EN || MENU_MOVIE_QUALITY_FINE_EN)
			"Fine", QUALITY_FINE,
			#endif
			NULL, 0
			},
        },
        {/* 005 */COMMON_KEY_MIC_SENSITIVITY, 0, MENU_MOVIE_MIC_SEN_EN, ParamFun, NULL,
        	{
			#if (MENU_MOVIE_MIC_SEN_STANDARD_EN)
			"Standard", MIC_SEN_STANDARD,
			#endif
			#if (MENU_MOVIE_MIC_SEN_LOW_EN)
			"Low", MIC_SEN_LOW,
			#endif
        	NULL, 0
        	},
        },
        {/* 006 */COMMON_KEY_PRE_RECD, 0, MENU_MOVIE_PRE_RECORD_EN, ParamFun, NULL,
        	{
			#if (MENU_MOVIE_PRE_RECORD_ON_EN)
			"ON", MOVIE_PRE_RECORD_ON,
			#endif
			#if (MENU_MOVIE_PRE_RECORD_OFF_EN)
			"OFF", MOVIE_PRE_RECORD_OFF,
			#endif
        	NULL, 0
        	},
        },
        {/* 007 */COMMON_KEY_VR_CLIP_TIME, 2, MENU_MOVIE_CLIP_TIME_EN, ParamFun, NULL,
        	{
			#if (MENU_MOVIE_CLIP_TIME_OFF_EN)
			"OFF", MOVIE_CLIP_TIME_OFF,
			#endif
			#if (MENU_MOVIE_CLIP_TIME_1MIN_EN)
			"1MIN", MOVIE_CLIP_TIME_1MIN,
			#endif
			#if (MENU_MOVIE_CLIP_TIME_2MIN_EN)
			"2MIN", MOVIE_CLIP_TIME_2MIN,
			#endif
			#if (MENU_MOVIE_CLIP_TIME_3MIN_EN)
			"3MIN", MOVIE_CLIP_TIME_3MIN,
			#endif
			#if (MENU_MOVIE_CLIP_TIME_5MIN_EN)
			"5MIN", MOVIE_CLIP_TIME_5MIN,
			#endif
			#if (MENU_MOVIE_CLIP_TIME_10MIN_EN)
			"10MIN", MOVIE_CLIP_TIME_10MIN,
			#endif
			#if (MENU_MOVIE_CLIP_TIME_30MIN_EN)
			"30MIN", MOVIE_CLIP_TIME_30MIN,
			#endif
        	NULL, 0
        	},
        },
        {/* 008 */COMMON_KEY_POWER_OFF_DELAY, 0, MENU_MOVIE_POWER_OFF_DELAY_EN, ParamFun, NULL,
        	{
			#if (MENU_MOVIE_POWER_OFF_DELAY_0SEC_EN)
			"0", MOVIE_POWEROFF_TIME_0MIN,
			#endif
			#if (MENU_MOVIE_POWER_OFF_DELAY_5SEC_EN)
			"5s", MOVIE_POWEROFF_TIME_5SEC,
			#endif
			#if (MENU_MOVIE_POWER_OFF_DELAY_10SEC_EN)
			"10s", MOVIE_POWEROFF_TIME_10SEC,
			#endif
			#if (MENU_MOVIE_POWER_OFF_DELAY_15SEC_EN)
			"15s", MOVIE_POWEROFF_TIME_15SEC,
			#endif
			#if (MENU_MOVIE_POWER_OFF_DELAY_30SEC_EN)
			"30s", MOVIE_POWEROFF_TIME_30SEC,
			#endif
			#if (MENU_MOVIE_POWER_OFF_DELAY_1MIN_EN)
			"60s", MOVIE_POWEROFF_TIME_1MIN,
			#endif
        	NULL, 0
        	},
        },
        {/* 009 */COMMON_KEY_RECD_SOUND, 0, MENU_MOVIE_SOUND_RECORD_EN, ParamFun, NULL,
        	{
			#if (MENU_MOVIE_SOUND_RECORD_ON_EN)
			"ON", MOVIE_SOUND_RECORD_ON,
			#endif
			#if (MENU_MOVIE_SOUND_RECORD_OFF_EN)
			"OFF", MOVIE_SOUND_RECORD_OFF,
			#endif
        	NULL, 0
        	},
        },
        {/* 010 */COMMON_KEY_VMD_REC_TIME, 0, MENU_MOVIE_VMD_REC_TIME_EN, ParamFun, NULL,
        	{
			#if (MENU_MOVIE_VMD_REC_TIME_5SEC_EN)
			"5s", VMD_REC_TIME_5SEC,
			#endif
			#if (MENU_MOVIE_VMD_REC_TIME_10SEC_EN)
			"10s", VMD_REC_TIME_10SEC,
			#endif
			#if (MENU_MOVIE_VMD_REC_TIME_30SEC_EN)
			"30s", VMD_REC_TIME_30SEC,
			#endif
			#if (MENU_MOVIE_VMD_REC_TIME_1MIN_EN)
			"1min", VMD_REC_TIME_1MIN,
			#endif
        	NULL, 0
        	},
        },
        {/* 011 */COMMON_KEY_AUTO_RECORD, 0, MENU_MOVIE_AUTO_REC_EN, ParamFun, NULL,
        	{
        	"ON", AUTO_REC_ON,
        	"OFF", AUTO_REC_OFF,
        	NULL, 0
        	},
        },
        {/* 012 */COMMON_KEY_TIMELAPSE, 0, MENU_VIDEO_TIMELAPSE_MODE_EN, ParamFun, NULL,
        	{
			#if (MENU_STILL_TIMELAPSE_TIME1_EN)
			"0s", TIMELAPSE_INTERVAL_1,
			#endif
			#if (MENU_STILL_TIMELAPSE_TIME2_EN)
			"1s", TIMELAPSE_INTERVAL_2,
			#endif
			#if (MENU_STILL_TIMELAPSE_TIME3_EN)
			"2s", TIMELAPSE_INTERVAL_3,
			#endif
			#if (MENU_STILL_TIMELAPSE_TIME4_EN)
			"5s", TIMELAPSE_INTERVAL_4,
			#endif
			#if (MENU_STILL_TIMELAPSE_TIME5_EN)
			"10s", TIMELAPSE_INTERVAL_5,
			#endif
			#if (MENU_STILL_TIMELAPSE_TIME6_EN)
			"30s", TIMELAPSE_INTERVAL_6,
			#endif
			#if (MENU_STILL_TIMELAPSE_TIME7_EN)
			"60s", TIMELAPSE_INTERVAL_7,
			#endif
        	NULL, 0
        	},
        },
        {/* 013 */COMMON_KEY_SLOWMOTION_EN, 0, MENU_MOVIE_SLOWMOTION_MODE_EN, ParamFun, NULL,
        	{
			"x1", SLOWMOTION_EN_X1,
			"x3", SLOWMOTION_EN_X3,
			"x5", SLOWMOTION_EN_X5,
			"x7", SLOWMOTION_EN_X7,
        	NULL, 0
        	},
        },
        {/* 014 */COMMON_KEY_HDR_EN, 0, MENU_MOVIE_HDR_MODE_EN, ParamFun, NULL,
        	{
			"ON", HDR_EN_ON,
			"OFF", HDR_EN_OFF,
        	NULL, 0
        	},
        },
        {/* 015 */COMMON_KEY_WNR_EN, 0, MENU_MOVIE_WNR_MODE_EN, ParamFun, NULL,
        	{
			"OFF", WNR_EN_OFF,
			"ON", WNR_EN_ON,
        	NULL, 0
        	},
        },
        {/* 016 */COMMON_KEY_NIGHT_MODE_EN, 0, MENU_MOVIE_NIGHT_MODE_EN, ParamFun, NULL,
        	{
			#if (MENU_MOVIE_NIGHT_MODE_ON_EN)
			"ON", MOVIE_NIGHT_MODE_ON,
			#endif
			#if (MENU_MOVIE_NIGHT_MODE_OFF_EN)
			"OFF", MOVIE_NIGHT_MODE_OFF,
			#endif
        	NULL, 0
        	},
        },
        {/* 017 */COMMON_KEY_PARK_TYPE, 0, MENU_MOVIE_PARKING_MODE_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 018 */COMMON_KEY_LDWS_EN, 0, MENU_MOVIE_LDWS_MODE_EN, ParamFun, NULL,
			{
			"ON", LDWS_EN_ON,
			"OFF", LDWS_EN_OFF,
			NULL, 0
			},
        },
        {/* 019 */COMMON_KEY_FCWS_EN, 0, MENU_MOVIE_FCWS_MODE_EN, ParamFun, NULL,
			{
			"ON", FCWS_EN_ON,
			"OFF", FCWS_EN_OFF,
			NULL, 0
			},
        },
        {/* 020 */COMMON_KEY_SAG_EN, 0, MENU_MOVIE_SAG_MODE_EN, ParamFun, NULL,
        	{
			"ON", SAG_EN_ON,
			"OFF", SAG_EN_OFF,
        	NULL, 0
        	},
        },
        {/* 021 */COMMON_KEY_CONTRAST, 0, MENU_STILL_CONTRAST_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 022 */COMMON_KEY_SATURATION, 0, MENU_MOVIE_SATURATION_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 023 */COMMON_KEY_SHARPNESS, 0, MENU_MOVIE_SHARPNESS_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 024 */COMMON_KEY_GAMMA, 0, MENU_MOVIE_GAMMA_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        // Manual
        {/* 025 */COMMON_KEY_SCENE, 0, MENU_MANUAL_SCENE_EN, ParamFun, NULL,
        	{
			#if (MENU_MANUAL_SCENE_AUTO_EN)
			"Auto", SCENE_AUTO,
			#endif
			#if (MENU_MANUAL_SCENE_SPORT_EN)
			"Sport", SCENE_SPORT,
			#endif
			#if (MENU_MANUAL_SCENE_PORTRAIT_EN)
			"Portait", SCENE_PORTRAIT,
			#endif
			#if (MENU_MANUAL_SCENE_LANDSCAPE_EN)
			"Landscape", SCENE_LANDSCAPE,
			#endif
			#if (MENU_MANUAL_SCENE_TWILIGHT_PORTRAIT_EN)
			"TPortait", SCENE_TWILIGHT_PORTRAIT,
			#endif
			#if (MENU_MANUAL_SCENE_TWILIGHT_EN)
			"TWilight", SCENE_TWILIGHT,
			#endif
			#if (MENU_MANUAL_SCENE_SNOW_EN)
			"Snow", SCENE_SNOW,
			#endif
			#if (MENU_MANUAL_SCENE_BEACH_EN)
			"Beach", SCENE_BEACH,
			#endif
			#if (MENU_MANUAL_SCENE_FIREWORKS_EN)
			"Fireworks", SCENE_FIREWORKS,
			#endif
        	NULL, 0
        	},
        },
        {/* 026 */COMMON_KEY_EV,    6, MENU_MANUAL_EV_EN, ParamFun, NULL,
        	{
			#if (MENU_MANUAL_EV_N20_EN)
			"EVN20", EVVALUE_N20 ,
			#endif
			#if (MENU_MANUAL_EV_N17_EN)
			"EVN17", EVVALUE_N17 ,
			#endif
			#if (MENU_MANUAL_EV_N15_EN)
			"EVN15", EVVALUE_N15 ,
			#endif
			#if (MENU_MANUAL_EV_N13_EN)
			"EVN13", EVVALUE_N13 ,
			#endif
			#if (MENU_MANUAL_EV_N10_EN)
			"EVN10", EVVALUE_N10 ,
			#endif
			#if (MENU_MANUAL_EV_N07_EN)
			"EVN07", EVVALUE_N07 ,
			#endif
			#if (MENU_MANUAL_EV_N05_EN)
			"EVN05", EVVALUE_N05 ,
			#endif
			#if (MENU_MANUAL_EV_N03_EN)
			"EVN03", EVVALUE_N03 ,
			#endif
			//#if (MENU_MANUAL_EV_00_EN)    // always exist
			"EV0", EVVALUE_00  ,
			//#endif
			#if (MENU_MANUAL_EV_P03_EN)
			"EVP03", EVVALUE_P03 ,
			#endif
			#if (MENU_MANUAL_EV_P05_EN)
			"EVP05", EVVALUE_P05 ,
			#endif
			#if (MENU_MANUAL_EV_P07_EN)
			"EVP07", EVVALUE_P07 ,
			#endif
			#if (MENU_MANUAL_EV_P10_EN)
			"EVP10", EVVALUE_P10 ,
			#endif
			#if (MENU_MANUAL_EV_P13_EN)
			"EVP13", EVVALUE_P13 ,
			#endif
			#if (MENU_MANUAL_EV_P15_EN)
			"EVP15", EVVALUE_P15 ,
			#endif
			#if (MENU_MANUAL_EV_P17_EN)
			"EVP17", EVVALUE_P17 ,
			#endif
			#if (MENU_MANUAL_EV_P20_EN)
			"EVP20", EVVALUE_P20 ,
			#endif
        	NULL, 0
        	},
        },
        {/* 027 */COMMON_KEY_ISO,   0, MENU_MANUAL_ISO_EN, ParamFun, NULL,
        	{
			#if (MENU_MANUAL_ISO_AUTO_EN)
			"ISO_AUTO", ISO_AUTO,
			#endif
			//  ISO_80,
			#if (MENU_MANUAL_ISO_100_EN)
			"ISO_100", ISO_100,
			#endif
			#if (MENU_MANUAL_ISO_200_EN)
			"ISO_200", ISO_200,
			#endif
			#if (MENU_MANUAL_ISO_400_EN)
			"ISO_400", ISO_400,
			#endif
			#if (MENU_MANUAL_ISO_800_EN)
			"ISO_800", ISO_800,
			#endif
			#if (MENU_MANUAL_ISO_1200_EN)
			"ISO_1200", ISO_1200,
			#endif
			#if (MENU_MANUAL_ISO_1600_EN)
			"ISO_1600", ISO_1600,
			#endif
			#if (MENU_MANUAL_ISO_3200_EN)
			"ISO_3200", ISO_3200,
			#endif
        	NULL, 0
        	},
        },
        {/* 028 */COMMON_KEY_WB,    1, MENU_MANUAL_WB_EN, ParamFun, NULL,
			{
			#if (MENU_MANUAL_WB_AUTO_EN)
			"Auto", WB_AUTO,
			#endif
			#if (MENU_MANUAL_WB_DAYLIGHT_EN)
			"Daylight", WB_DAYLIGHT,
			#endif
			#if (MENU_MANUAL_WB_CLOUDY_EN)
			"Cloudy", WB_CLOUDY,
			#endif
			#if (MENU_MANUAL_WB_FLUORESCENT1_EN)
			"Fluorescent1", WB_FLUORESCENT1,
			#endif
			#if (MENU_MANUAL_WB_FLUORESCENT2_EN)
			"Fluorescent2", WB_FLUORESCENT2,
			#endif
			#if (MENU_MANUAL_WB_FLUORESCENT3_EN)
			"Fluorescent3", WB_FLUORESCENT3,
			#endif
			#if (MENU_MANUAL_WB_INCANDESCENT_EN)
			"Incandescent", WB_INCANDESCENT,
			#endif
			#if (MENU_MANUAL_WB_FLASH_EN)
			"Flash", WB_FLASH,
			#endif
			#if (MENU_MANUAL_WB_ONEPUSH_EN)
			"Onepush", WB_ONEPUSH,
			#endif
			#if (MENU_MANUAL_WB_ONE_PUSH_SET_EN)
			"Onepush set", WB_ONE_PUSH_SET,
			#endif
			#if (MENU_MANUAL_WB_UNDERWATER)
			"Underwater", WB_UNDERWATER,
			#endif
			NULL, 0
			},
        },
        {/* 029 */COMMON_KEY_COLOR, 0, MENU_MANUAL_COLOR_EN, ParamFun, NULL,
        	{
			#if (MENU_MANUAL_COLOR_NATURAL_EN)
			"natural", COLOR_NATURAL,
			#endif
			#if (MENU_MANUAL_COLOR_VIVID_EN)
			"vivid", COLOR_VIVID,
			#endif
			#if (MENU_MANUAL_COLOR_PALE_EN)
			"pale", COLOR_PALE,
			#endif
        	NULL, 0
        	},
        },
        {/* 030 */COMMON_KEY_EFFECT, 0, MENU_MANUAL_EFFECT_EN, ParamFun, NULL,
        	{
			#if (MENU_MANUAL_EFFECT_NORMAL_EN)
			"noraml", EFFECT_NORMAL,
			#endif
			#if (MENU_MANUAL_EFFECT_SEPIA_EN)
			"sepia", EFFECT_SEPIA,
			#endif
			#if (MENU_MANUAL_EFFECT_BLACK_WHITE_EN)
			"black white", EFFECT_BLACK_WHITE,
			#endif
			#if (MENU_MANUAL_EFFECT_EMBOSS_EN)
			"emboss", EFFECT_EMBOSS,
			#endif
			#if (MENU_MANUAL_EFFECT_NEGATIVE_EN)
			"negative", EFFECT_NEGATIVE,
			#endif
			#if (MENU_MANUAL_EFFECT_SKETCH_EN)
			"sketch", EFFECT_SKETCH,
			#endif
			#if (MENU_MANUAL_EFFECT_OIL_EN)
			"oil", EFFECT_OIL,
			#endif
			#if (MENU_MANUAL_EFFECT_CRAYON_EN)
			"crayon", EFFECT_CRAYON,
			#endif
			#if (MENU_MANUAL_EFFECT_BEAUTY_EN)
			"beauty", EFFECT_BEAUTY,
			#endif
        	NULL, 0
        	},
        },
        // Playback
        {/* 031 */"PlaybackVideoType", 0, MENU_PLAYBACK_VIDEO_TYPE_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 032 */"SlideShow",            0, 0,    NULL, NULL,
        	{NULL, 0},
        },
        {/* 033 */"SlideShowFileType",  0, MENU_PLAYBACK_SLIDESHOW_FILE_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 034 */"SlideShowEffect",    0, MENU_PLAYBACK_SLIDESHOW_EFFECT_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 035 */"SlideShowMusic",     0, MENU_PLAYBACK_SLIDESHOW_MUSIC_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 036 */COMMON_KEY_PB_VOLUME,     4, MENU_PLAYBACK_VOLUME_EN, ParamFun, NULL,
        	{
			#if (MENU_PLAYBACK_VOLUME_LV0_EN)
			"0", VOLUME_00,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV1_EN)
			"1", VOLUME_01 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV2_EN)
			"2", VOLUME_02 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV3_EN)
			"3", VOLUME_03 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV4_EN)
			"4", VOLUME_04 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV5_EN)
			"5", VOLUME_05 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV6_EN)
			"6", VOLUME_06 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV7_EN)
			"7", VOLUME_07 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV8_EN)
			"8", VOLUME_08 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV9_EN)
			"9", VOLUME_09 ,
			#endif
			#if (MENU_PLAYBACK_VOLUME_LV10_EN)
			"10", VOLUME_10 ,
			#endif
        	NULL, 0
        	},
        },
        // Edit Tool
        {/* 037 */"FileEdit",       0, 0, NULL, NULL,
        	{NULL, 0},
        },
        // Media Tool
        {/* 038 */"MediaSelect",    0, MENU_MEDIA_SELECT_MDEIA_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        // General
        {/* 039 */COMMON_KEY_BEEP,  0, MENU_GENERAL_BEEP_EN, ParamFun, NULL,
			{
			#if (MENU_GENERAL_BEEP_ON_EN)
			"ON", BEEP_ON,
			#endif
			#if (MENU_GENERAL_BEEP_OFF_EN)
			"OFF", BEEP_OFF,
			#endif
			NULL, 0
			},
        },
        {/* 040 */COMMON_AUTO_POWER_OFF, 0, MENU_GENERAL_AUTO_POWEROFF_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_AUTO_POWEROFF_NEVER_EN)
			"never", AUTO_POWER_OFF_NEVER,
			#endif
			#if (MENU_GENERAL_AUTO_POWEROFF_15SEC_EN)
			"15s", AUTO_POWER_OFF_15SEC,
			#endif
			#if (MENU_GENERAL_AUTO_POWEROFF_30SEC_EN)
			"30s", AUTO_POWER_OFF_30SEC,
			#endif
			#if (MENU_GENERAL_AUTO_POWEROFF_1MIN_EN)
			"1min", AUTO_POWER_OFF_1MIN,
			#endif
			#if (MENU_GENERAL_AUTO_POWEROFF_2MIN_EN)
			"2min", AUTO_POWER_OFF_2MINS,
			#endif
			#if (MENU_GENERAL_AUTO_POWEROFF_3MIN_EN)
			"3min", AUTO_POWER_OFF_3MINS,
			#endif
			#if (MENU_GENERAL_AUTO_POWEROFF_5MIN_EN)
			"5min", AUTO_POWER_OFF_5MINS,
			#endif
        	NULL, 0
        	},
        },
        {/* 041 */COMMON_DATE_TIME_FMT, 1, MENU_GENERAL_DATE_FORMAT_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_DATE_FORMAT_NONE_EN)
			"NONE", DATETIME_SETUP_NONE,
			#endif
			#if (MENU_GENERAL_DATE_FORMAT_YMD_EN)
			"YMD", DATETIME_SETUP_YMD,
			#endif
			#if (MENU_GENERAL_DATE_FORMAT_MDY_EN)
			"MDY", DATETIME_SETUP_MDY,
			#endif
			#if (MENU_GENERAL_DATE_FORMAT_DMY_EN)
			"DMY", DATETIME_SETUP_DMY,
			#endif
        	NULL, 0
        	},
        },
        {/* 042 */COMMON_KEY_STICKER_LOGO_TXT, 1, MENU_GENERAL_DATE_LOGO_STAMP_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_LOGO_EN)
			"date+logo", DATELOGO_STAMP,
			#endif
			#if (MENU_GENERAL_DATE_LOGO_STAMP_DATE_EN)
			"date", DATE_STAMP,
			#endif
			#if (MENU_GENERAL_DATE_LOGO_STAMP_LOGO_EN)
			"logo", LOGO_STAMP,
			#endif
			#if (MENU_GENERAL_DATE_LOGO_STAMP_OFF_EN)
			"off", OFF_STAMP,
			#endif
        	NULL, 0
        	},
        },
        {/* 043 */COMMON_KEY_STICKER_GPS, 1, MENU_GENERAL_GPS_STAMP_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_GPS_STAMP_ON_EN)
			"ON", GPS_STAMP_ON,
			#endif
			#if (MENU_GENERAL_GPS_STAMP_OFF_EN)
			"OFF", GPS_STAMP_OFF,
			#endif
        	NULL, 0
        	},
        },
        {/* 044 */COMMON_KEY_STICKER_SPEED, 1, MENU_GENERAL_SPEED_STAMP_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_SPEED_STAMP_ON_EN)
			"ON", SPEED_STAMP_ON,
			#endif
			#if (MENU_GENERAL_SPEED_STAMP_OFF_EN)
			"OFF", SPEED_STAMP_OFF,
			#endif
        	NULL, 0
        	},
        },
        {/* 045 */COMMON_KEY_LANGUAGE,       0, MENU_GENERAL_LANGUAGE_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_LANGUAGE_ENGLISH_EN)
			"English", LANGUAGE_ENGLISH,
			#endif
			#if (MENU_GENERAL_LANGUAGE_SPANISH_EN)
			"Spanish", LANGUAGE_SPANISH,
			#endif
			#if (MENU_GENERAL_LANGUAGE_PORTUGUESE_EN)
			"Portuguese", LANGUAGE_PORTUGUESE,
			#endif
			#if (MENU_GENERAL_LANGUAGE_RUSSIAN_EN)
			"Russian", LANGUAGE_RUSSIAN,
			#endif
			#if (MENU_GENERAL_LANGUAGE_SCHINESE_EN)
			"SChinese", LANGUAGE_SCHINESE,
			#endif
			#if (MENU_GENERAL_LANGUAGE_TCHINESE_EN)
			"TChinese", LANGUAGE_TCHINESE,
			#endif
			#if (MENU_GENERAL_LANGUAGE_GERMAN_EN)
			"German", LANGUAGE_GERMAN,
			#endif
			#if (MENU_GENERAL_LANGUAGE_ITALIAN_EN)
			"Italian", LANGUAGE_ITALIAN,
			#endif
			#if (MENU_GENERAL_LANGUAGE_LATVIAN_EN)
			"Latvian", LANGUAGE_LATVIAN,
			#endif
			#if (MENU_GENERAL_LANGUAGE_POLISH_EN)
			"Polish", LANGUAGE_POLISH,
			#endif
			#if (MENU_GENERAL_LANGUAGE_ROMANIAN_EN)
			"Romanian", LANGUAGE_ROMANIAN,
			#endif
			#if (MENU_GENERAL_LANGUAGE_SLOVAK_EN)
			"Slovak", LANGUAGE_SLOVAK,
			#endif
			#if (MENU_GENERAL_LANGUAGE_UKRANINIAN_EN)
			"Ukraninian", LANGUAGE_UKRANINIAN,
			#endif
			#if (MENU_GENERAL_LANGUAGE_FRENCH_EN)
			"French", LANGUAGE_FRENCH,
			#endif
			#if (MENU_GENERAL_LANGUAGE_JAPANESE_EN)
			"Japanese", LANGUAGE_JAPANESE,
			#endif
			#if (MENU_GENERAL_LANGUAGE_KOREAN_EN)
			"Korean", LANGUAGE_KOREAN,
			#endif
			#if (MENU_GENERAL_LANGUAGE_CZECH_EN)
			"Czech", LANGUAGE_CZECH,
			#endif
        	NULL, 0
        	},
        },
        {/* 046 */"ResetSetting",          0, MENU_GENERAL_RESET_SETUP_EN, ParamFun, NULL,
        	{NULL, 0},
        },
        {/* 047 */COMMON_KEY_FLICKER,          0, MENU_GENERAL_FLICKER_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_FLICKER_50HZ_EN)
			"50HZ", FLICKER_50HZ  ,
			#endif
			#if (MENU_GENERAL_FLICKER_60HZ_EN)
			"60HZ", FLICKER_60HZ  ,
			#endif
        	NULL, 0
        	},
        },
        {/* 048 */COMMON_KEY_USB_FUNC,            0, MENU_GENERAL_USB_FUNCTION_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_USB_FUNCTION_MSDC_EN)
        	"MSDC", MENU_SETTING_USB_MSDC  ,
			#endif
			#if (MENU_GENERAL_USB_FUNCTION_PCAM_EN)
			"PCAM", MENU_SETTING_USB_PCAM  ,
			#endif
        	NULL, 0
        	},
        },
        {/* 049 */COMMON_KEY_LCD_POWERS,          0, MENU_GENERAL_LCD_POWER_SAVE_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_LCD_POWER_SAVE_OFF_EN)
			"OFF", LCD_POWER_SAVE_OFF,
			#endif
			#if (MENU_GENERAL_LCD_POWER_SAVE_10SEC_EN)
			"10s", LCD_POWER_SAVE_10SEC,
			#endif
			#if (MENU_GENERAL_LCD_POWER_SAVE_30SEC_EN)
			"30s", LCD_POWER_SAVE_30SEC,
			#endif
			#if (MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN)
			"1min", LCD_POWER_SAVE_1MIN,
			#endif
			#if (MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN)
			"3min", LCD_POWER_SAVE_3MIN,
			#endif
        	NULL, 0
        	},
        },
        {/* 050 */COMMON_KEY_GSENSOR_SENS, 3, MENU_GENERAL_GSENSOR_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_GSENSOR_OFF_EN)
			"OFF", GSENSOR_SENSITIVITY_OFF,
			#endif
			#if (MENU_GENERAL_GSENSOR_LEVEL0_EN)
			"LEVEL0", GSENSOR_SENSITIVITY_L0,
			#endif
			#if (MENU_GENERAL_GSENSOR_LEVEL1_EN)
			"LEVEL1", GSENSOR_SENSITIVITY_L1,
			#endif
			#if (MENU_GENERAL_GSENSOR_LEVEL2_EN)
			"LEVEL2", GSENSOR_SENSITIVITY_L2,
			#endif
			#if (MENU_GENERAL_GSENSOR_LEVEL3_EN)
			"LEVEL3", GSENSOR_SENSITIVITY_L3,
			#endif
			#if (MENU_GENERAL_GSENSOR_LEVEL4_EN)
			"LEVEL4", GSENSOR_SENSITIVITY_L4,
			#endif
        	NULL, 0
        	},
        },
        {/* 051 */COMMON_KEY_GSENSOR_PWR_ON_SENS, 3, MENU_GENERAL_POWERON_GSENSOR_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_POWERON_GSENSOR_OFF_EN)
			"OFF", GSENSOR_POWERON_SENSITIVITY_OFF,
			#endif
			#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL0_EN)
			"LEVEL0", GSENSOR_POWERON_SENSITIVITY_L0,
			#endif
			#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL1_EN)
			"LEVEL1", GSENSOR_POWERON_SENSITIVITY_L1,
			#endif
			#if (MENU_GENERAL_POWER_ON_GSENSOR_LEVEL2_EN)
			"LEVEL2", GSENSOR_POWERON_SENSITIVITY_L2,
			#endif
        	NULL, 0
        	},
        },
        {/* 052 */COMMON_KEY_TIME_ZONE,       13, MENU_GENERAL_TIME_ZONE_EN, ParamFun, NULL,
        	{
			"GMT-12:00", TIMEZONE_GMT_M_12,  //00:0x00
			"GMT-11:00", TIMEZONE_GMT_M_11,
			"GMT-10:00", TIMEZONE_GMT_M_10,
			"GMT-9:00", TIMEZONE_GMT_M_9,
			"GMT-8:00", TIMEZONE_GMT_M_8,
			"GMT-7:00", TIMEZONE_GMT_M_7,   //05:0x05
			"GMT-6:00", TIMEZONE_GMT_M_6,
			"GMT-5:00", TIMEZONE_GMT_M_5,
			"GMT-4:00", TIMEZONE_GMT_M_4,
			"GMT-4:30", TIMEZONE_GMT_M_3_30,
			"GMT-3:00", TIMEZONE_GMT_M_3,   //10:0x0A
			"GMT-2:00", TIMEZONE_GMT_M_2,
			"GMT-1:00", TIMEZONE_GMT_M_1,
			"GMT", TIMEZONE_GMT,
			"GMT+1:00", TIMEZONE_GMT_P_1,
			"GMT+2:00", TIMEZONE_GMT_P_2,   //15:0x0F
			"GMT+3:00", TIMEZONE_GMT_P_3,
			"GMT+3:30", TIMEZONE_GMT_P_3_30,
			"GMT+4:00", TIMEZONE_GMT_P_4,
			"GMT+4:30", TIMEZONE_GMT_P_4_30,
			"GMT+5:00", TIMEZONE_GMT_P_5,   //20:0x14
			"GMT+5:30", TIMEZONE_GMT_P_5_30,
			"GMT+5:45", TIMEZONE_GMT_P_5_45,
			"GMT+6:00", TIMEZONE_GMT_P_6,
			"GMT+6:30", TIMEZONE_GMT_P_6_30,
			"GMT+7:00", TIMEZONE_GMT_P_7,   //25:0x19
			"GMT+8:00", TIMEZONE_GMT_P_8,
			"GMT+9:00", TIMEZONE_GMT_P_9,
			"GMT+9:30", TIMEZONE_GMT_P_9_30,
			"GMT+10:00", TIMEZONE_GMT_P_10,
			"GMT+11:00", TIMEZONE_GMT_P_11,  //30:0x1E
        	NULL, 0
        	},
        },
        {/* 053 */COMMON_KEY_MOTION_SENS,    0, MENU_GENERAL_MOTION_DTC_EN, ParamFun, NULL,
        	{
			#if (MENU_GENERAL_MOTION_DTC_OFF_EN)
			"OFF", MOTION_DTC_SENSITIVITY_OFF,
			#endif
			#if (MENU_GENERAL_MOTION_DTC_LOW_EN)
			"LOW", MOTION_DTC_SENSITIVITY_LOW,
			#endif
			#if (MENU_GENERAL_MOTION_DTC_MID_EN)
			"MID", MOTION_DTC_SENSITIVITY_MID,
			#endif
			#if (MENU_GENERAL_MOTION_DTC_HIGH_EN)
			"HIGH", MOTION_DTC_SENSITIVITY_HIGH,
			#endif
        	NULL, 0
        	},
        },
        {/* 054 */"BatteryVoltage",       0, 0, NULL, NULL,
        	{NULL, 0},
        },
        {/* 055 */COMMON_KEY_WIFI_EN,       0, MENU_GENERAL_WIFI_EN, NULL, NULL,
        	{
			#if (MENU_GENERAL_WIFI_ON_EN)
			"ON", WIFI_MODE_ON,
			#endif
			#if (MENU_GENERAL_WIFI_OFF_EN)
			"OFF", WIFI_MODE_OFF,
			#endif
        	NULL, 0
        	},
        },
        {/* 056 */"version",       0, MENU_GENERAL_FW_VERSION_EN, NULL, NULL,
        	{
        	"v1.0.0", 0,
        	NULL, 0
        	},
        },
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /* NEW!! Extension setting */

        /* END OF MARK */
        {NULL,                      0, 0, NULL,       NULL,
        	{NULL, 0},
        }
	}
};

const char* osdstringpool[] = {
"",
"Manual Settings",
"Scene",
"Auto",
"Sports",
"Portrait",
"Landscape",
"Twi. Portrait",
"Twilight",
"Snow",
"Beach",
"Fireworks",
"Select mode for various scenes.",
"Focus Window",
"Multi",
"Center Spot",
"Select the focus window.",
"Focus Range",
"Normal",
"Macro",
"Select the focus range.",
"Exposure Metering",
"Center Weighted",
"Select the exposure metering method.",
"Exposure",
"2",
"1.7",
"1.3",
"1",
"0.7",
"0.3",
"0",
"-0.3",
"-0.7",
"-1",
"-1.3",
"-1.7",
"-2",
"Adjust the brightness.",
"ISO Sensitivity",
"ISO100",
"ISO200",
"ISO400",
"ISO800",
"ISO1600",
"ISO3200",
"Select the sensor sensitivity.",
"White Balance",
"Daylight",
"Cloudy",
"Fluoresc.",
"Fluoresc.1",
"Fluoresc.2",
"Incandesc.",
"Flash",
"One Push",
"One-Push Set",
"Adjust the color balance.",
"Color",
"Natural",
"Vivid",
"Pale",
"Adjust the color saturation.",
"Effect",
"Sepia",
"B&W",
"Emboss",
"Negative",
"Sketch",
"Oil",
"Crayon",
"Beauty",
"Select the image effect method.",
"Face Detection",
"On",
"Touch Focus",
"Switch LDWS",
"Smile Detection",
"1 Person",
"2 Persons",
"Take photo when smile is detected.",
"Smile Sensitivity",
"Low",
"High",
"Set the smile detection sensitivity.",
"Menu",
"Quick Menu",
"Movie Mode",
"SHD 30fps",
"SHD 25fps",
"SHD 24fps",
"FHD 60fps",
"FHD 30fps",
"FHD HDR 30fps",
"HD 30fps",
"VGA 30fps",
"HD 60fps",
"Select the movie mode.",
"Movie Record",
"Movie Quality",
"Super Fine ",
"Fine ",
"Select the movie quality.",
"Movie Stabilization",
"On",
"Off",
"Correct camera shake for movie recording.",
"Auto Slow Shutter",
"Records movies in dim environment.",
"MIC Sensitivity",
"Standard",
"Adjust the microphone level.",
"Still Image Size",
"30M",
"14M",
"12M",
"8M",
"5M",
"3M",
"2M",
"1.2M",
"VGA",
"Select the still image size.",
"Flash",
"Slow Sync",
"Select the flash mode.",
"Self Timer ",
"1 sec",
"2 sec",
"5 sec",
"10 sec ",
"15 sec",
"30 sec",
"60 sec",
"0min",
"1min",
"2min",
"3min",
"5min",
"10min",
"15min",
"25min",
"30min",
"60min",
"Select the self timer mode.",
"Still Capture",
"Still Quality",
"Select the still image quality.",
"Still Stabilization",
"Stabilize camera shake for still capture.",
"Flash Level",
"Adjust the flash brightness.",
"Red Eye Reduction",
"Prevent redeye when shooting with flash.",
"Burst Capture",
"Burst Lo",
"Burst Mid",
"Bustt Hi",
"Select the burst mode.",
"Delete",
"YES",
"NO",
"Protect",
"Cut",
"Volume",
"Movie playback volume.",
"Slide Show ",
"Rotate",
"OK",
"Cancel",
"Resize",
"Resize still image sizes.",
"Trimming",
"Playback",
"Slide Show Files",
"All Files",
"Still Files",
"Movie Files",
"Select the slideshow files.",
"Slide Show Effects",
"Simple",
"Nostalgic",
"Stylish",
"Active",
"Select the slideshow effects.",
"Slide Show Music",
"Select slideshow music.",
"Edit Tool",
"Delete movies or photos.",
"Delete All",
"Delete all files?",
"Protect movies or photos",
"Protect All",
"Protect all files?",
"Media Tool",
"Media Select",
"SD-Card",
"INT.Memory",
"Select media.",
"Format SD-Card",
"Format Card?",
"All data will be deleted.",
"Format INT.Mem.",
"Format Internal Memory?",
"SD-Card INFO",
"Card Information",
"Time Left",
"Photo Left",
"INT.Mem. INFO",
"INT.Memory Information",
"General Settings",
"Beep",
"Turn the beep on/off. ",
"LCD Brightness",
"Bright",
"Adjust LCD brightness.",
"Power Off",
"Never",
"Select the power off mode.",
"Power Save",
"Select the power save mode.",
"Clock Settings",
"Y",
"M",
"D",
"Date Format",
"None",
"YYYY MM DD",
"MM DD YYYY",
"DD MM YYYY",
"Select the date format.",
"Language",
"English",
"Espa?ol",
"Portugu��s",
"������ܧڧ�",
"��������",
"���w����",
"Deutsch",
"Italiano",
"Latviski",
"Polski",
"Roman?",
"Sloven?ina",
"���ܧ��?�ߧ��ܧ�",
"Fran?ais",
"???",
"�ձ��Z",
"?e?tina",
"Select language.",
"TV System",
"NTSC",
"PAL",
"Select TV system.",
"HDMI Output",
"1080P",
"1080i",
"720p",
"480p",
"Select the signal of HDMI.",
"Reset Setup",
"Reset Setup?",
"All setting will be deleted.",
"SD card is not formatted correctly.",
"This storage is full!",
"SD card is not inserted.",
"Battery level is low!",
"File error occurred!",
"This SD card is protected!",
"This SD card is slow.",
"Use recommended cards.",
"Power adapter error occurred!",
"This operation is invalid!",
"Cannot delete protected files!",
"Battery is full.",
"Lens error occurred!",
"HDMI/TV only for playback.",
"FHD and HD be stored in the SD card, please use the SD card media.",
"Flash Light",
"LED Light",
"Date Stamp",
"Record",
"Standby",
"Capture",
"Playback",
"Power",
"Shutter",
"Start",
"Stop",
"Zoom",
"Tele",
"Wide",
"Up",
"Down",
"Left",
"Right",
"Switch",
"Pause",
"Set",
"Panorama",
"FW Version",
"Version",
"Test",
"Branch",
"PreRecord",
"PreRecord",
"Exit Menu",
"Delete One",
"Protect One",
"Movie Clip Time",
"Movie Off Time",
"Flicker",
"50 Hz",
"60 Hz",
"Sound Record",
"Cycle Record Error",
"Clean More SD Space",
"Sure To Power Off",
"Delete Selected File?",
"Delete Selected File Error!",
"Unprotect One",
"Unprotect All",
"Protect Selected File?",
"UnProtect Selected File?",
"Please Format SD Card",
"Video File",
"Image File",
"Format SD Card Complete",
"Format SD Card Fail",
"Lock Current File",
"MSDC",
"PCam",
"USB Function",
"Wait SD Card Initialization Done",
"Please Insert SD Card Again",
"LCD Rotate",
"LCD Power Save",
"Delete File Complete",
"Protect File Complete",
"SD Card Is Plug Out",
"Going Power Off",
"LED Light",
"Protect Level",
"Level 0",
"Level 1",
"Level 2",
"Level 3",
"Level 4",
"SD Card Format is Processing",
"Power Off Delay",
"DSC",
"DV",
"Mode",
"Take Photos",
"Browser Photos",
"Browser Videos",
"Playback Photos",
"Playback Videos",
"GPS Status",
"Time Zone Select",
"GMT-12:00",
"GMT-11:00",
"GMT-10:00",
"GMT-09:00",
"GMT-08:00",
"GMT-07:00",
"GMT-06:00",
"GMT-05:00",
"GMT-04:00",
"GMT-03:30",
"GMT-03:00",
"GMT-02:00",
"GMT-01:00",
"GMT",
"GMT+01:00",
"GMT+02:00",
"GMT+03:00",
"GMT+03:30",
"GMT+04:00",
"GMT+04:30",
"GMT+05:00",
"GMT+05:30",
"GMT+05:45",
"GMT+06:00",
"GMT+06:30",
"GMT+07:00",
"GMT+08:00",
"GMT+09:00",
"GMT+09:30",
"GMT+10:00",
"GMT+11:00",
"GMT+12:00",
"GMT+13:00",
"Unlock files",
"No file",
"Capture the current screen",
"Date+Logo",
"Date",
"Logo",
"Stamp",
"Select Stamp format",
"Middle",
"H",
"M",
"Motion Detection",
"Enable Motion Detection",
"Select",
"Motion event REC",
"Motion event shot",
"Detects moving objects!",
"Shot",
"S",
"Auto Record",
"Last",
"All",
"s",
"Time lapes",
"Start",
"REC",
"DSC",
"Shots",
"Lapse",
"FHD",
"HD30",
"HD60",
"VGA",
"1min",
"5min",
"G-Sensor",
"Select a file",
"Night mode",
"Enable Night mode?",
"Long press MODE to switch LCD/AV",
"Event Browser",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Driver ID Settings",
"Parking Monitoring",
"Wifi CARCAM",
"General Settings",
"WIFI MODE",
"AP",
"STATION",
"AP SSID",
"AP PSWD",
"STA1 SSID",
"STA1 PSWD",
"STA2 SSID",
"STA2 PSWD",
"STA3 SSID",
"STA3 PSWD",
"STA4 SSID",
"STA4 PSWD",
"STA5 SSID",
"STA5 PSWD",
"STA6 SSID",
"STA6 PSWD",
"Video Type",
"Normal",
"Parking",
"Emergency",
"FW Reading ...",
"FW Updating ...",
"LDWS Calibration",
"LDWS",
"FCWS",
"Stop And Go",
"HDR",
"Please Wait ...",
"1920x1080 24fps",
"1280x720 24fps",
"Contrast",
"Adjust Sensor Contrast",
"Saturation",
"Adjust Sensor Saturation",
"Sharpness",
"Adjust Sensor Sharpness",
"Gamma",
"Adjust Sensor Gamma",
"SlowMotion",
"Off",
"X2",
"X4",
"X8",
"Video Time Lapse",
"WNR",
"RearCam Type",
"NONE",
"AIT",
"SONIXM2H",
"SONIXM",
"TVDecord",
"BayerSensor",
"YUVSensor",
"ColorTemp",
"default",
"Warm Color",
"Cool Color",
"Mode 1",
"Mode 2",
"Mode 3",
"Mode 4",
"Mode 5",
"+",
"-",
};
/*===========================================================================
 * Main body
 *===========================================================================*/
bool Menu_General_EnGet(char *key, char *value, int len)
{
    FILE * fp = NULL;
    char str[64] = {0};
    bool ret = true;

    sprintf(str, "%s%s", GET_CONFIG_SETTING, key);

    fp = popen(str, "r");
    if (fp != NULL) {
        if (value != NULL) {
            while (fgets(value, len, fp) != NULL) {
            	if(value[strlen(value) - 1] == '\n')
            		value[strlen(value) - 1] = '\0';
            }
        }
        pclose(fp);
    }
    else {
        ret = false;
    }
    return ret;
}

bool Menu_General_EnSet(const char *key, char *value)
{
	bool ret = true;
	int status = 0;
	char str[64] = {0};
	sprintf(str, "%s%s %s", SET_CONFIG_SETTING, key, value);
	status = system(str);
	if (status < 0) {
	    printf("[%s]fail\n", str);
	    ret = false;
	}
	return ret;
}

static int MenuSetting_Get_General(int icur_val, va_list *ap)
{
    int* pSetting;

    pSetting = va_arg(*ap, int *);        // Get next argument (note: typedef must be correct)
    *pSetting = icur_val;
    return 0;
}

//menu_atoms.sAtom[i].fnSet(&menu_atoms.sAtom[0], i, val, pmi);
static int ParamFun(SETTING_ATOM *pa, int idx, char *szVal, void *arg)
{
    int    *p; // point to MenuInfo
    int     v = 0;
    int     i = 0;

    /* pmi is menu struct (MenuInfo), here use it as char* to set value.
     * BE CAREFUL the order of MenuInfo and SETTING_ATOM must be same! */
    p = (int *) arg;

    for(i = 0; i < NUMBER_ITEM_VALS; i++) {
    	if((pa+idx)->szItemMaps[i].szItemKey != NULL) {
    		if(strcmp(szVal, (pa+idx)->szItemMaps[i].szItemKey) == 0) {
    			v = (pa+idx)->szItemMaps[i].nItemValue;
    			break;
    		}
    		else
    			v = 0;
    	}
    	else
    		v = 0;
    }

    (pa + idx)->nSVal = v;

    if (idx  < (int)sizeof(MenuInfo)/4)
    {
        *(p + idx) = (int)(pa + idx)->nSVal;
    }

    return  0;
}

/* Read cgi_config.bin  File Setting to MENU_ATOMS and MenuInfo */
int ParseMenuSet(const char *file, MenuInfo* pmi /*out*/)
{
	FILE *fp = NULL;
	char file_buf[128] = {0};
	
	//printf("open:%s\n",file);
	fp = fopen(file, "r");
	if(fp == NULL)
		return -1;

	while(!feof(fp)) {
		memset(file_buf, 0, sizeof(file_buf));
		if(fgets(file_buf, sizeof(file_buf), fp) != NULL) {
			char    *key, *val;
        	int     i;

			if(strstr(file_buf, ";;\n") == NULL)
				continue;
			key = strtok(file_buf, "=");
			val = strtok(NULL, ";;\n");
			if(key == NULL)
				continue;
			if(val == NULL)
				continue;
			
			for(i = 0; i< NUMBER_SETTING && menu_atoms.sAtom[i].szSKey != NULL; i++) {
				if(strcmp(key, menu_atoms.sAtom[i].szSKey) == 0) {
					//printf("%d:%s=%s\n",i,key,val);
					if(menu_atoms.sAtom[i].fnSet != NULL)
						menu_atoms.sAtom[i].fnSet(&menu_atoms.sAtom[0], i, val, pmi);
					break;
				}
			}
		}
	}
	fclose(fp);
	//printf("close:%s\n",file);
	return 0;
}
/*Get MENU_ATOMS value*/
bool MenuSetting_GetCB(char *cmenu_string, ...)
{
	bool retVal = false;
	int uloop;
	va_list ap;

	for (uloop = 0; menu_atoms.sAtom[uloop].szSKey != NULL; uloop++){
		//case sensitive
		if (/*strcmpi*/strcmp(cmenu_string, menu_atoms.sAtom[uloop].szSKey) == 0){
			va_start(ap, cmenu_string);     // Set pointer to 1st argument of "Varaible List"
			if(menu_atoms.sAtom[uloop].fnGet != NULL){
				retVal = menu_atoms.sAtom[uloop].fnGet(menu_atoms.sAtom[uloop].nSVal, &ap);
			}
			va_end(ap);
			return retVal;
		}
	}

	return false;
}

bool ImportMenuInfo(MenuInfo *pmi)
{
    int *p;
    unsigned int i = 0;

    p = (int *)pmi;

    for (i = 0; i < sizeof(MenuInfo)/4; i++) {
        menu_atoms.sAtom[i].nSVal = *(p + i);
    }
    return true;
}

int ExportMenuInfo(const char *file)
{
	unsigned int i = 0;
	int nValue = 0;
	char szValue[20] = {0};
	for (i = 0; i < sizeof(MenuInfo)/4; i++) {
		if(menu_atoms.sAtom[i].szSKey != NULL &&
				menu_atoms.sAtom[i].nSVal != temp_menu_atoms.sAtom[i].nSVal) {
			nValue = menu_atoms.sAtom[i].nSVal;
			strcpy(szValue, menu_atoms.sAtom[i].szItemMaps[nValue].szItemKey);
			Menu_General_EnSet(menu_atoms.sAtom[i].szSKey, szValue);
			break;
		}
	}
	return 0;
}

bool MenuSetting_CheckMenuAtoms(void)
{
    if (memcmp((char *) &temp_menu_atoms, (char *) &menu_atoms, sizeof(MENU_ATOMS)) == 0) {
        return true;
    }
    printf("Menu setting is changed\r\n");
    return false;
}

void MenuSetting_BackupMenuAtoms(void)
{
    memcpy((char *) &temp_menu_atoms, (char *) &menu_atoms, sizeof(MENU_ATOMS));
}

void Menu_WriteSetting(void)
{
	if(MenuSetting_CheckMenuAtoms() == false) {
		MenuSetting_BackupMenuAtoms();

		ImportMenuInfo(&gCurMenuInfo);
		ExportMenuInfo(MenuCfgFile);
	}
}

pMenuInfo MenuSettingConfig(void)
{
    return &gCurMenuInfo;
}

void MenuSettingInit(void)
{
    gCurMenuInfo.uiIMGSize              = IMAGE_SIZE_2M;
    gCurMenuInfo.uiIMGQuality           = QUALITY_SUPER_FINE;
    gCurMenuInfo.uiBurstShot            = BURST_SHOT_OFF;

    gCurMenuInfo.uiMOVSize              = MOVIE_SIZE_1080_30P;
    gCurMenuInfo.uiMOVQuality           = QUALITY_SUPER_FINE;
    gCurMenuInfo.uiMicSensitivity       = MIC_SEN_STANDARD;
    gCurMenuInfo.uiMOVPreRecord         = MOVIE_PRE_RECORD_OFF;
    gCurMenuInfo.uiMOVClipTime          = MOVIE_CLIP_TIME_1MIN;

    gCurMenuInfo.uiMOVPowerOffTime      = MOVIE_POWEROFF_TIME_DEFAULT;
    gCurMenuInfo.uiMOVSoundRecord       = MOVIE_SOUND_RECORD_ON;
    gCurMenuInfo.uiVMDRecTime           = VMD_REC_TIME_5SEC;
    gCurMenuInfo.uiAutoRec              = AUTO_REC_ON;
    gCurMenuInfo.uiTimeLapseTime        = TIMELAPSE_INTERVAL_DEFAULT;
    gCurMenuInfo.uiSlowMotion           = SLOWMOTION_EN_DEFAULT;
    gCurMenuInfo.uiHDR                  = HDR_EN_DEFAULT;
    gCurMenuInfo.uiWNR                  = WNR_EN_DEFAULT;
    gCurMenuInfo.uiNightMode        	= MOVIE_NIGHT_MODE_DEFAULT;
    gCurMenuInfo.uiParkingMode			= 0;
    gCurMenuInfo.uiLDWS					= LDWS_EN_DEFAULT;
    gCurMenuInfo.uiFCWS					= FCWS_EN_DEFAULT;
    gCurMenuInfo.uiSAG					= SAG_EN_DEFAULT;
    gCurMenuInfo.uiContrast				= 50;
    gCurMenuInfo.uiSaturation			= 50;
    gCurMenuInfo.uiSharpness			= 50;
    gCurMenuInfo.uiGamma				= 50;

    gCurMenuInfo.uiScene                = SCENE_AUTO;
    gCurMenuInfo.uiEV                   = EVVALUE_00;
    gCurMenuInfo.uiISO                  = ISO_AUTO;
    gCurMenuInfo.uiWB                   = WB_AUTO;
    gCurMenuInfo.uiColor                = COLOR_NATURAL;
    gCurMenuInfo.uiEffect               = EFFECT_NORMAL;

    gCurMenuInfo.uiSlideShowStart       = SLIDESHOW_DISABLE;
    gCurMenuInfo.uiSlideShowFile        = SLIDESHOW_FILE_ALL;
    gCurMenuInfo.uiSlideShowEffect      = SLIDESHOW_EFFECT_SIMPLE;
    gCurMenuInfo.uiSlideShowMusic       = SLIDESHOW_MUSIC_OFF;
    gCurMenuInfo.uiVolume               = VOLUME_05;

    gCurMenuInfo.uiFileEdit             = FILEEDIT_DELETE;
    gCurMenuInfo.uiMediaSelect          = MEDIA_SETTING_SD_CARD;

    gCurMenuInfo.uiBeep                 = BEEP_OFF;
    gCurMenuInfo.uiAutoPowerOff         = AUTO_POWER_OFF_NEVER;
    gCurMenuInfo.uiDateTimeFormat       = DATETIME_SETUP_YMD;

    gCurMenuInfo.uiDateLogoStamp        = DATE_STAMP;
    gCurMenuInfo.uiGPSStamp             = GPS_STAMP_ON;
    gCurMenuInfo.uiSpeedStamp           = SPEED_STAMP_OFF;
    gCurMenuInfo.uiLanguage             = LANGUAGE_ENGLISH;
    gCurMenuInfo.uiResetSetting         = 0;
    gCurMenuInfo.uiFlickerHz            = FLICKER_50HZ;
    gCurMenuInfo.uiUSBFunction          = MENU_SETTING_USB_MSDC;
    gCurMenuInfo.uiLCDPowerSave         = LCD_POWER_SAVE_OFF;
    gCurMenuInfo.uiGsensorSensitivity   = GSENSOR_SENSITIVITY_OFF;
    gCurMenuInfo.uiMotionDtcSensitivity = MOTION_DTC_SENSITIVITY_OFF;
    gCurMenuInfo.uiTimeZone             = TIMEZONE_GMT_P_8;
    gCurMenuInfo.uiBatteryVoltage       = BATTERY_VOLTAGE_FULL;
    gCurMenuInfo.uiWifi					= WIFI_MODE_OFF;
}

void ListAllMenuSetting(MenuInfo *Info)
{
    printf("---------------------------------------------------\n");
    printf(" uiIMGSize          = %d \n", Info->uiIMGSize          );
    printf(" uiIMGQuality       = %d \n", Info->uiIMGQuality       );
    printf(" uiBurstShot        = %d \n", Info->uiBurstShot        );

    printf(" uiMOVSize          = %d \n", Info->uiMOVSize          );
    printf(" uiMOVQuality       = %d \n", Info->uiMOVQuality       );
    printf(" uiMicSensitivity   = %d \n", Info->uiMicSensitivity   );
    printf(" uiMOVPreRecord     = %d \n", Info->uiMOVPreRecord     );
    printf(" uiMOVClipTime      = %d \n", Info->uiMOVClipTime      );
    printf(" uiMOVPowerOffTime  = %d \n", Info->uiMOVPowerOffTime  );
    printf(" uiMOVSoundRecord   = %d \n", Info->uiMOVSoundRecord   );
    printf(" uiVMDRecTime       = %d \n", Info->uiVMDRecTime       );
    printf(" uiAutoRec          = %d \n", Info->uiAutoRec          );
    printf(" uiSlowMotion    = %d \n", Info->uiSlowMotion);
    printf(" uiWNR    = %d \n", Info->uiWNR    );
    printf(" uiWNR    = %d \n", Info->uiWNR    );
    printf(" uiNightMode    = %d \n", Info->uiNightMode     );
    printf(" uiParkingMode    = %d \n", Info->uiParkingMode   );
    printf(" uiLDWS    = %d \n", Info->uiLDWS      );
    printf(" uiFCWS    = %d \n", Info->uiFCWS      );
    printf(" uiSAG    = %d \n", Info->uiSAG      );
    printf(" uiContrast    = %d \n", Info->uiContrast      );
    printf(" uiSaturation    = %d \n", Info->uiSaturation    );
    printf(" uiSharpness    = %d \n", Info->uiSharpness     );
    printf(" uiGamma    = %d \n", Info->uiGamma     );

    printf(" uiScene            = %d \n", Info->uiScene            );
    printf(" uiEV               = %d \n", Info->uiEV               );
    printf(" uiISO              = %d \n", Info->uiISO              );
    printf(" uiWB               = %d \n", Info->uiWB               );
    printf(" uiColor            = %d \n", Info->uiColor            );
    printf(" uiEffect           = %d \n", Info->uiEffect           );

    printf(" uiSlideShowStart   = %d \n", Info->uiSlideShowStart   );
    printf(" uiSlideShowFile    = %d \n", Info->uiSlideShowFile    );
    printf(" uiSlideShowEffect  = %d \n", Info->uiSlideShowEffect  );
    printf(" uiSlideShowMusic   = %d \n", Info->uiSlideShowMusic   );
    printf(" uiVolume           = %d \n", Info->uiVolume           );

    printf(" uiFileEdit         = %d \n", Info->uiFileEdit         );
    printf(" uiMediaSelect      = %d \n", Info->uiMediaSelect      );

    printf(" uiBeep             = %d \n", Info->uiBeep             );
    printf(" uiAutoPowerOff     = %d \n", Info->uiAutoPowerOff     );
    printf(" uiDateTimeFormat   = %d \n", Info->uiDateTimeFormat   );
    printf(" uiDateLogoStamp    = %d \n", Info->uiDateLogoStamp    );
    printf(" uiGPSStamp         = %d \n", Info->uiGPSStamp         );
    printf(" uiSpeedStamp       = %d \n", Info->uiSpeedStamp       );
    printf(" uiLanguage         = %d \n", Info->uiLanguage         );
    printf(" uiResetSetting     = %d \n", Info->uiResetSetting     );
    printf(" uiFlickerHz        = %d \n", Info->uiFlickerHz        );
    printf(" uiUSBFunction      = %d \n", Info->uiUSBFunction      );
    printf(" uiLCDPowerSave     = %d \n", Info->uiLCDPowerSave     );
    printf(" uiGsensorSensitivity   = %d \n", Info->uiGsensorSensitivity);
    printf(" uiPowerOnGsensorSensitivity   = %d \n", Info->uiPowerOnGsensorSensitivity);
    printf(" uiTimeZone         = %d \n", Info->uiTimeZone         );
    printf(" uiMotionDtcSensitivity = %d \n", Info->uiMotionDtcSensitivity);
    
    printf(" uiBatteryVoltage              = %d \n", Info->uiBatteryVoltage);
    printf(" uiWifi              = %d \n", Info->uiWifi);
    printf(" uiVersion              = %d \n", Info->uiVersion);
    printf("---------------------------------------------------\n");
}

int MenuSetting_GetStringPool(const char *file)
{
	FILE *fp = NULL;
	char stringpool[32][IDS_DS_END] = {0};
	int i = 0;

	fp = fopen(file, "r+");
	if(fp == NULL)
		return -1;

	while(!feof(fp)) {
		fgets(stringpool[i], 32, fp);
		printf("%d=%s\n", i, stringpool[i]);
		i++;
	}
	fclose(fp);
	return 0;
}
