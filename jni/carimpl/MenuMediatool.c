#include "MenuCommon.h"

/*===========================================================================
 * Local function
 *===========================================================================*/
bool MenuItemMediaSelect(PSMENUITEM pItem);
bool MenuItemFormatSDCard(PSMENUITEM pItem);
bool MenuItemFormatINTMemory(PSMENUITEM pItem);
bool MenuItemSDCardINFO(PSMENUITEM pItem);
bool MenuItemINTMemoryINFO(PSMENUITEM pItem);

int  MenuGetDefault_MediaTool(PSMENUSTRUCT pMenu);
 /*===========================================================================
 * Extern varible
 *===========================================================================*/
extern SMENUSTRUCT sMainMenuMedia;

extern SMENUSTRUCT sSubMediaSelect;
extern SMENUSTRUCT sSubFormatSDCard;
extern SMENUSTRUCT sSubFormatINTMemory;
extern SMENUSTRUCT sSubSDCardINFO;
extern SMENUSTRUCT sSubINTMemoryINFO;
 /*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/
// Media Select
#if (MENU_MEDIA_SELECT_MDEIA_EN)
SMENUITEM sItemMediaSelect       = { ITEMID_MEDIA_SELECT,  IDS_DS_MEDIA_SELECT,	&sSubMediaSelect, 0 };
SMENUITEM sItemMedia_SDCard      = { ITEMID_MEDIA_SD_CARD,   	 IDS_DS_MEDIA_SD_CARD,	NULL, MenuItemMediaSelect };
SMENUITEM sItemMedia_Internal    = { ITEMID_MEDIA_INTERNAL,  IDS_DS_MEDIA_INTERNAL, NULL, MenuItemMediaSelect };
#endif

// Format SD-Card
#if (MENU_MEDIA_FORMAT_SD_EN)
SMENUITEM sItemFormatCard        = { ITEMID_FORMAT_SD_CARD,  IDS_DS_FORMAT_SD_CARD,	&sSubFormatSDCard, 0 };
SMENUITEM sItemFormatCard_Yes    = { ITEMID_FORMAT_CARD_YES,  	IDS_DS_YES, NULL, MenuItemFormatSDCard };
SMENUITEM sItemFormatCard_No     = { ITEMID_FORMAT_CARD_NO,   	IDS_DS_NO,  NULL, MenuItemFormatSDCard };
#endif

//Format INT.Memory
#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
SMENUITEM sItemFormatINTMem      = { ITEMID_FORMAT_INTMEM,  IDS_DS_FORMAT_INTMEM,	&sSubFormatINTMemory, 0 };
SMENUITEM sItemFormatINTMem_Yes  = { ITEMID_FORMAT_INTMEM_YES,  IDS_DS_YES,	NULL, MenuItemFormatINTMemory };
SMENUITEM sItemFormatINTMem_No   = { ITEMID_FORMAT_INTMEM_NO,   IDS_DS_NO,     NULL, MenuItemFormatINTMemory };
#endif

// SD-Card INFO
#if (MENU_MEDIA_SHOW_SD_INFO)
SMENUITEM sItemSDCardINFO        = { ITEMID_SD_CARD_INFO,  IDS_DS_SD_CARD_INFO, &sSubSDCardINFO, 0 };
SMENUITEM sItemCardTimeLeft      = { ITEMID_CARD_TIME_LEFT,   IDS_DS_TIME_LEFT,  NULL, MenuItemSDCardINFO };
SMENUITEM sItemCardPhotoLeft     = { ITEMID_CARD_PHOTO_LEFT,  IDS_DS_PHOTO_LEFT, NULL, MenuItemSDCardINFO };
#endif

// INT.Memory INFO
#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
SMENUITEM sItemINTMemINFO        = { ITEMID_INTMEM_INFO,  IDS_DS_INTMEM_INFO, &sSubINTMemoryINFO, 0 };
SMENUITEM sItemINTTimeLeft       = { ITEMID_INT_TIME_LEFT,   IDS_DS_TIME_LEFT,  NULL, MenuItemINTMemoryINFO };
SMENUITEM sItemINTPhotoLeft      = { ITEMID_INT_PHOTO_LEFT,  IDS_DS_PHOTO_LEFT, NULL, MenuItemINTMemoryINFO };
#endif

 /*===========================================================================
 * Global varible : Item List
 *===========================================================================*/
#if (MENU_MEDIA_SELECT_MDEIA_EN)
PSMENUITEM   sMenuListMediaSelect[] =
{
    &sItemMedia_SDCard,
    &sItemMedia_Internal
};
#endif

#if (MENU_MEDIA_FORMAT_SD_EN)
PSMENUITEM   sMenuListFormatSDCard[] =
{
    &sItemFormatCard_Yes,
    &sItemFormatCard_No
};
#endif

#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
PSMENUITEM   sMenuListFormatINTMemory[] =
{
    &sItemFormatINTMem_Yes,
    &sItemFormatINTMem_No
};
#endif

#if (MENU_MEDIA_SHOW_SD_INFO)
PSMENUITEM   sMenuListSDCardInfo[] =
{
    &sItemCardTimeLeft,
    &sItemCardPhotoLeft
};
#endif

#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
PSMENUITEM   sMenuListINTMemoryInfo[] =
{
    &sItemINTTimeLeft,
    &sItemINTPhotoLeft
};
#endif

PSMENUITEM   sMenuListMainMedia[] =
{
#if (MENU_MEDIA_FORMAT_SD_EN)
    &sItemFormatCard,    
#endif
#if (MENU_MEDIA_SHOW_SD_INFO)    
    &sItemSDCardINFO
#endif    
};
 /*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/
SMENUSTRUCT   sMainMenuMedia =
{
    MENUID_MAIN_MENU_MEDIA,                                                                       
    IDS_DS_MEDIA_TOOL,                                 
    NULL,                                              
    sizeof(sMenuListMainMedia)/sizeof(PSMENUITEM),   
    sMenuListMainMedia,                                                        
    NULL,                                                                                
};

//--------------SUB MENU-------------------

#if (MENU_MEDIA_SELECT_MDEIA_EN)
SMENUSTRUCT sSubMediaSelect =
{
    MENUID_SUB_MENU_MEDIA_SELECT,
    IDS_DS_MEDIA_SELECT,
    &sMainMenuMedia,
    sizeof(sMenuListMediaSelect)/sizeof(PSMENUITEM),
    sMenuListMediaSelect,
    MenuGetDefault_MediaTool,
};
#endif

#if (MENU_MEDIA_FORMAT_SD_EN)
SMENUSTRUCT sSubFormatSDCard =
{
    MENUID_SUB_MENU_FORMAT_SD_CARD,
    IDS_DS_FORMAT_SD_CARD,
    &sMainMenuMedia,
    sizeof(sMenuListFormatSDCard)/sizeof(PSMENUITEM),
    sMenuListFormatSDCard,
    NULL,
};
#endif

#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
SMENUSTRUCT sSubFormatINTMemory =
{
    MENUID_SUB_MENU_FORMAT_INTMEM,
    IDS_DS_FORMAT_INTMEM,
    &sMainMenuMedia,
    sizeof(sMenuListFormatINTMemory)/sizeof(PSMENUITEM),
    sMenuListFormatINTMemory,
    NULL,
};
#endif

#if (MENU_MEDIA_SHOW_SD_INFO)
SMENUSTRUCT sSubSDCardINFO =
{
    MENUID_SUB_MENU_SD_CARD_INFO,
    IDS_DS_CARD_INFO,
    &sMainMenuMedia,
    sizeof(sMenuListSDCardInfo)/sizeof(PSMENUITEM),
    sMenuListSDCardInfo,
    NULL,
};
#endif

#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
SMENUSTRUCT sSubINTMemoryINFO =
{
    MENUID_SUB_MENU_INTMEM_INFO,
    IDS_DS_INTMEM_INFORMATION,
    &sMainMenuMedia,
    sizeof(sMenuListINTMemoryInfo)/sizeof(PSMENUITEM),
    sMenuListINTMemoryInfo,
    NULL,
};
#endif
 /*===========================================================================
 * Main body
 *===========================================================================*/
 #if (MENU_MEDIA_SELECT_MDEIA_EN)
 bool MenuItemMediaSelect(PSMENUITEM pItem)
{
    MenuSettingConfig()->uiMediaSelect= pItem->iItemId - ITEMID_MEDIA_SELECT-1; 
    return true;
}
#endif
#if (MENU_MEDIA_FORMAT_SD_EN)
bool MenuItemFormatSDCard(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_MEDIA_FORMAT_INT_MEM_EN)
bool MenuItemFormatINTMemory(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_MEDIA_SHOW_SD_INFO)
bool MenuItemSDCardINFO(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_MEDIA_SHOW_INT_MEM_INFO)
bool MenuItemINTMemoryINFO(PSMENUITEM pItem)
{
    return true;
}
#endif
int  MenuGetDefault_MediaTool(PSMENUSTRUCT pMenu)
{
    int DefaultValue = 0;

    switch( pMenu->iMenuId )
    {
    #if (MENU_MEDIA_SELECT_MDEIA_EN)
        case MENUID_SUB_MENU_MEDIA_SELECT:
            DefaultValue = MenuSettingConfig()->uiMediaSelect;
            break;
    #endif
    	default:
    		break;        
    }
    return DefaultValue;
}