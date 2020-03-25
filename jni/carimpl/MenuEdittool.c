#include "MenuCommon.h"

/*===========================================================================
 * Local function
 *===========================================================================*/
bool MenuItemDeleteOne(PSMENUITEM pItem);
bool MenuItemDeleteAll(PSMENUITEM pItem);
bool MenuItemDeleteFile(PSMENUITEM pItem);
bool MenuItemUnProtectOne(PSMENUITEM pItem);
bool MenuItemProtectOne(PSMENUITEM pItem);
bool MenuItemProtectAll(PSMENUITEM pItem);
bool MenuItemUnProtectAll(PSMENUITEM pItem);
bool MenuItemEditOneConfirmOk(PSMENUITEM pItem);

 /*===========================================================================
 * Extern varible
 *===========================================================================*/
extern SMENUSTRUCT sMainMenuEdit;

extern SMENUSTRUCT sSubDelete;
extern SMENUSTRUCT sSubDeleteFile;
extern SMENUSTRUCT sSubDeleteAll;
extern SMENUSTRUCT sSubDeleteAll_Video;
extern SMENUSTRUCT sSubDeleteAll_Image;
extern SMENUSTRUCT sSubProtect;
extern SMENUSTRUCT sSubProtectAll;
extern SMENUSTRUCT sSubProtectAll_Video;
extern SMENUSTRUCT sSubProtectAll_Image;
extern SMENUSTRUCT sSubUnProtectAll;
extern SMENUSTRUCT sSubUnProtectAll_Video;
extern SMENUSTRUCT sSubUnProtectAll_Image;

extern SMENUSTRUCT sSubDeleteOne;
extern SMENUSTRUCT sSubProtectOne;
extern SMENUSTRUCT sSubUnProtectOne;
 /*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/
// Delete
#if (MENU_EDIT_DELETE_EN)
SMENUITEM sItemDelete         = { ITEMID_DELETE,  IDS_DS_DELETE,	&sSubDelete, 0 };

SMENUITEM sItemDeleteFile     = { ITEMID_DELETE_FILE,  IDS_DS_DELETE,	&sSubDeleteFile, 0 };
SMENUITEM sItemDelete_Cancel  = { ITEMID_DELETE_CANCEL, 	 IDS_DS_CANCEL, 		NULL, MenuItemDeleteFile };
SMENUITEM sItemDeleteFileLast = { ITEMID_DELETE_FILE_LAST, 	 IDS_DS_LAST,			NULL, MenuItemDeleteFile };
SMENUITEM sItemDeleteFileAll  = { ITEMID_DELETE_FILE_ALL, 	 IDS_DS_ALL,			NULL, MenuItemDeleteFile };
#endif

// Delete One
#if (MENU_EDIT_DELETE_ONE_EN)

#if (MENU_EDIT_DELETE_SELECT_FORMAT)
/* Show a submenu to select video or photo file before selecting a file to delete */
SMENUITEM sItemDeleteOne       = { ITEMID_DELETE_ONE,  	  	    IDS_DS_DELETE_ONE, &sSubDeleteOne, 		0 };
SMENUITEM sItemDeleteOne_Yes   = { ITEMID_DELETE_ONE_YES, 	 IDS_DS_YES, 	    NULL, NULL };
SMENUITEM sItemDeleteOne_No    = { ITEMID_DELETE_ONE_NO,  	  IDS_DS_NO,  	    NULL, NULL };
SMENUITEM sItemDeleteOne_Video = { ITEMID_DELETE_VIDEO_ONE,  IDS_VIDEO_FILE,		NULL, MenuItemDeleteOne };
SMENUITEM sItemDeleteOne_Image = { ITEMID_DELETE_IMAGE_ONE, IDS_IMAGE_FILE,		NULL, MenuItemDeleteOne };
#else
SMENUITEM sItemDeleteOne      = { ITEMID_DELETE_ONE,  	  IDS_DS_DELETE_ONE, 	NULL, MenuItemDeleteOne };
SMENUITEM sItemDeleteOne_Yes  = { ITEMID_DELETE_ONE_YES,  	IDS_DS_YES, 	NULL, NULL };
SMENUITEM sItemDeleteOne_No   = { ITEMID_DELETE_ONE_NO,   	IDS_DS_NO,  	NULL, NULL };
#endif

#endif

SMENUITEM sItemConfirmOne_Yes  = { ITEMID_DELETE_ONE_YES,  	IDS_DS_YES, 	NULL, MenuItemEditOneConfirmOk };
SMENUITEM sItemConfirmOne_No   = { ITEMID_DELETE_ONE_NO,   	IDS_DS_NO,  	NULL, MenuItemEditOneConfirmOk };

// Delete All
#if (MENU_EDIT_DELETE_ALL_EN)
SMENUITEM sItemDeleteAll      		= { ITEMID_DELETE_ALL, 	 IDS_DS_DELETE_ALL,	&sSubDeleteAll, 0 };

// Delete All Video
SMENUITEM sItemDeleteAll_Video 		= { ITEMID_DELETE_ALL_VIDEO, 	  IDS_VIDEO_FILE,	&sSubDeleteAll_Video, 0 };
SMENUITEM sItemDeleteAll_Video_Yes  = { ITEMID_DELETE_ALL_VIDEO_YES,  IDS_DS_YES, 	NULL, 	MenuItemDeleteAll };
SMENUITEM sItemDeleteAll_Video_No   = { ITEMID_DELETE_ALL_VIDEO_NO,    IDS_DS_NO,  	NULL, 	MenuItemDeleteAll };

// Delete All Image
SMENUITEM sItemDeleteAll_Image 		= { ITEMID_DELETE_ALL_IMAGE, 	 IDS_IMAGE_FILE,	&sSubDeleteAll_Image, 0 };
SMENUITEM sItemDeleteAll_Image_Yes  = { ITEMID_DELETE_ALL_IMAGE_YES,  IDS_DS_YES, 	NULL, 	MenuItemDeleteAll };
SMENUITEM sItemDeleteAll_Image_No   = { ITEMID_DELETE_ALL_IMAGE_NO,    IDS_DS_NO,  	NULL, 	MenuItemDeleteAll };
#endif

// Protect
#if (MENU_EDIT_PROTECT_EN)
SMENUITEM sItemProtect        	= { ITEMID_PROTECT,  IDS_DS_PROTECT,	&sSubProtect, 0 };
#endif

// Protect One
#if (MENU_EDIT_PROTECT_ONE_EN)

#if (MENU_EDIT_PROTECT_SELECT_FORMAT)
/* Show a submenu to select video or photo file before selecting a file to protect */
SMENUITEM sItemProtectOne     	= { ITEMID_PROTECT_ONE, 		   IDS_DS_PROTECT_ONE, 	&sSubProtectOne, NULL };
SMENUITEM sItemProtectOne_Yes 	= { ITEMID_PROTECT_ONE_YES, 	 IDS_DS_YES, 	NULL, 	NULL };
SMENUITEM sItemProtectOne_No  	= { ITEMID_PROTECT_ONE_NO,  	 	IDS_DS_NO,  	NULL,	NULL };
SMENUITEM sItemProtectOne_Video = { ITEMID_PROTECT_VIDEO_ONE, 	 IDS_VIDEO_FILE,	NULL, 	MenuItemProtectOne };
SMENUITEM sItemProtectOne_Image = { ITEMID_PROTECT_IMAGE_ONE, 	IDS_IMAGE_FILE,	NULL, 	MenuItemProtectOne };
#else
SMENUITEM sItemProtectOne     	= { ITEMID_PROTECT_ONE, 	 IDS_DS_PROTECT_ONE, 	NULL, MenuItemProtectOne };
SMENUITEM sItemProtectOne_Yes 	= { ITEMID_PROTECT_ONE_YES,  IDS_DS_YES, 	NULL, NULL };
SMENUITEM sItemProtectOne_No  	= { ITEMID_PROTECT_ONE_NO,   	IDS_DS_NO,  	NULL, NULL };
#endif

#endif

// UnProtect One
#if (MENU_EDIT_UNPROTECT_ONE_EN)

#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
/* Show a submenu to select video or photo file before selecting a file to unlock */
SMENUITEM sItemUnProtectOne     	= { ITEMID_UNPROTECT_ONE, 	  	 IDS_DS_UNPROTECT_ONE, 	&sSubUnProtectOne,  NULL };
SMENUITEM sItemUnProtectOne_Yes		= { ITEMID_UNPROTECT_ONE_YES, 	 IDS_DS_YES, 	NULL, NULL };
SMENUITEM sItemUnProtectOne_No  	= { ITEMID_UNPROTECT_ONE_NO,  	  IDS_DS_NO,  	NULL, NULL };
SMENUITEM sItemUnProtectOne_Video 	= { ITEMID_UNPROTECT_VIDEO_ONE,  IDS_VIDEO_FILE,	NULL, MenuItemUnProtectOne };
SMENUITEM sItemUnProtectOne_Image 	= { ITEMID_UNPROTECT_IMAGE_ONE, IDS_IMAGE_FILE, NULL, MenuItemUnProtectOne };
#else
SMENUITEM sItemUnProtectOne     = { ITEMID_UNPROTECT_ONE, 	   IDS_DS_UNPROTECT_ONE, 	NULL, MenuItemUnProtectOne };
SMENUITEM sItemUnProtectOne_Yes = { ITEMID_UNPROTECT_ONE_YES,  IDS_DS_YES, 	NULL, NULL };
SMENUITEM sItemUnProtectOne_No  = { ITEMID_UNPROTECT_ONE_NO,   IDS_DS_NO,  	NULL, NULL };
#endif

#endif

// Protect All
#if (MENU_EDIT_PROTECT_ALL_EN)
SMENUITEM sItemProtectAll     		 = { ITEMID_PROTECT_ALL, 			 IDS_DS_PROTECT_ALL, &sSubProtectAll, 		0 };

// Protect All Video
SMENUITEM sItemProtectAll_Video 	 = { ITEMID_PROTECT_ALL_VIDEO, 	 	 IDS_VIDEO_FILE,	&sSubProtectAll_Video, 	0 };
SMENUITEM sItemProtectAll_Video_Yes  = { ITEMID_PROTECT_ALL_VIDEO_YES, 	 IDS_DS_YES, 	NULL, 	MenuItemProtectAll };
SMENUITEM sItemProtectAll_Video_No   = { ITEMID_PROTECT_ALL_VIDEO_NO,  	  IDS_DS_NO,  	NULL, 	MenuItemProtectAll };

// Protect All Image
SMENUITEM sItemProtectAll_Image 	 = { ITEMID_PROTECT_ALL_IMAGE, 	  	IDS_IMAGE_FILE,	&sSubProtectAll_Image, 	0 };
SMENUITEM sItemProtectAll_Image_Yes  = { ITEMID_PROTECT_ALL_IMAGE_YES, 	 IDS_DS_YES, 	NULL, 	MenuItemProtectAll };
SMENUITEM sItemProtectAll_Image_No   = { ITEMID_PROTECT_ALL_IMAGE_NO,  	  IDS_DS_NO,  	NULL, 	MenuItemProtectAll };
#endif

// UnProtect All
#if (MENU_EDIT_UNPROTECT_ALL_EN)
SMENUITEM sItemUnProtectAll     	   = { ITEMID_UNPROTECT_ALL, 			 IDS_DS_UNPROTECT_ALL, &sSubUnProtectAll, 0 };

// UnProtect All Video
SMENUITEM sItemUnProtectAll_Video 	   = { ITEMID_UNPROTECT_ALL_VIDEO, 		 IDS_VIDEO_FILE,	&sSubUnProtectAll_Video, 	0 };
SMENUITEM sItemUnProtectAll_Video_Yes  = { ITEMID_UNPROTECT_ALL_VIDEO_YES, 	 IDS_DS_YES, NULL, 	MenuItemUnProtectAll };
SMENUITEM sItemUnProtectAll_Video_No   = { ITEMID_UNPROTECT_ALL_VIDEO_NO,  	  IDS_DS_NO,  NULL, 	MenuItemUnProtectAll };

// UnProtect All Image
SMENUITEM sItemUnProtectAll_Image 	   = { ITEMID_UNPROTECT_ALL_IMAGE, 		 IDS_IMAGE_FILE,	&sSubUnProtectAll_Image, 0 };
SMENUITEM sItemUnProtectAll_Image_Yes  = { ITEMID_UNPROTECT_ALL_IMAGE_YES, 	 IDS_DS_YES, NULL, 	MenuItemUnProtectAll };
SMENUITEM sItemUnProtectAll_Image_No   = { ITEMID_UNPROTECT_ALL_IMAGE_NO,  	  IDS_DS_NO,  NULL, 	MenuItemUnProtectAll };
#endif


 /*===========================================================================
 * Global varible : Item List
 *===========================================================================*/
#if (MENU_EDIT_DELETE_EN)
PSMENUITEM   sMenuListDelete[]=
{	
#if (MENU_EDIT_DELETE_ONE_EN)	
	&sItemDeleteOne,
#endif	
#if (MENU_EDIT_DELETE_ALL_EN)
    &sItemDeleteAll
#endif  
};

PSMENUITEM   sMenuListDeleteFile[]=
{	
	&sItemDelete_Cancel,
    &sItemDeleteFileLast,
	&sItemDeleteFileAll
};
#endif

#if (MENU_EDIT_DELETE_ONE_EN)
PSMENUITEM   sMenuListDeleteOne[]=
{
    &sItemDeleteOne_Yes,
    &sItemDeleteOne_No
};
#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
PSMENUITEM   sMenuListDeleteOneFormat[]=
{
    &sItemDeleteOne_Video,
    &sItemDeleteOne_Image
};
#endif
#endif

#if (MENU_EDIT_DELETE_ALL_EN)
PSMENUITEM   sMenuListDeleteAll[]=
{
    &sItemDeleteAll_Video,
    &sItemDeleteAll_Image
};

PSMENUITEM   sMenuListDeleteAll_Video[]=
{
    &sItemDeleteAll_Video_Yes,
    &sItemDeleteAll_Video_No
};

PSMENUITEM   sMenuListDeleteAll_Image[]=
{
    &sItemDeleteAll_Image_Yes,
    &sItemDeleteAll_Image_No
};
#endif

#if (MENU_EDIT_PROTECT_EN)
PSMENUITEM   sMenuListProtect[]=
{
#if (MENU_EDIT_PROTECT_ONE_EN)
	&sItemProtectOne,
#endif
#if (MENU_EDIT_UNPROTECT_ONE_EN)	
	&sItemUnProtectOne,
#endif	
#if (MENU_EDIT_PROTECT_ALL_EN)	
    &sItemProtectAll,
#endif    
#if (MENU_EDIT_UNPROTECT_ALL_EN)    
    &sItemUnProtectAll
#endif    
};
#endif

#if (MENU_EDIT_PROTECT_ONE_EN)
PSMENUITEM   sMenuListProtectOne[]=
{
    &sItemProtectOne_Yes,
    &sItemProtectOne_No
};
#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
PSMENUITEM   sMenuListProtectOneFormat[]=
{
    &sItemProtectOne_Video,
    &sItemProtectOne_Image
};
#endif
#endif

#if (MENU_EDIT_UNPROTECT_ONE_EN)
PSMENUITEM   sMenuListUnProtectOne[]=
{
    &sItemUnProtectOne_Yes,
    &sItemUnProtectOne_No
};
#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
PSMENUITEM   sMenuListUnProtectOneFormat[] =
{
    &sItemUnProtectOne_Video,
    &sItemUnProtectOne_Image
};
#endif
#endif

#if (MENU_EDIT_PROTECT_ALL_EN)
PSMENUITEM   sMenuListProtectAll[]=
{
    &sItemProtectAll_Video,  
    &sItemProtectAll_Image
};

PSMENUITEM   sMenuListProtectAll_Video[]=
{
    &sItemProtectAll_Video_Yes,
    &sItemProtectAll_Video_No
};

PSMENUITEM   sMenuListProtectAll_Image[]=
{
    &sItemProtectAll_Image_Yes,
    &sItemProtectAll_Image_No
};
#endif

#if (MENU_EDIT_UNPROTECT_ALL_EN)  
PSMENUITEM   sMenuListUnProtectAll[]=
{
    &sItemUnProtectAll_Video, 
    &sItemUnProtectAll_Image
};

PSMENUITEM   sMenuListUnProtectAll_Video[]=
{
    &sItemUnProtectAll_Video_Yes,
    &sItemUnProtectAll_Video_No
};

PSMENUITEM   sMenuListUnProtectAll_Image[]=
{
    &sItemUnProtectAll_Image_Yes,
    &sItemUnProtectAll_Image_No
};
#endif

PSMENUITEM   sMenuListMainEdit[]=
{
#if (MENU_EDIT_DELETE_EN)
    &sItemDelete,
#endif
#if (MENU_EDIT_PROTECT_EN)    
    &sItemProtect 
#endif    
};
 /*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/
SMENUSTRUCT   sMainMenuEdit =
{
    MENUID_MAIN_MENU_EDIT,
    IDS_DS_EDIT_TOOL,                                  
    NULL,                                              
    sizeof(sMenuListMainEdit)/sizeof(PSMENUITEM),   
    sMenuListMainEdit,
    NULL,                                                                                 
};

//--------------SUB MENU-------------------

#if (MENU_EDIT_DELETE_EN)

SMENUSTRUCT sSubDeleteFile =
{
    MENUID_SUB_MENU_DELETE_FILE,
    IDS_DS_DELETE,
    &sMainMenuEdit,
    sizeof(sMenuListDeleteFile)/sizeof(PSMENUITEM),
    sMenuListDeleteFile,
    NULL,
};

SMENUSTRUCT sSubDelete =
{
    MENUID_SUB_MENU_DELETE,
    IDS_DS_DELETE,
    &sMainMenuEdit,
    sizeof(sMenuListDelete)/sizeof(PSMENUITEM),
    sMenuListDelete,
    NULL,
};
#endif

#if (MENU_EDIT_DELETE_ALL_EN)
SMENUSTRUCT sSubDeleteAll =
{
    MENUID_SUB_MENU_DELETE_ALL,
    IDS_DS_DELETE_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListDeleteAll)/sizeof(PSMENUITEM),
    sMenuListDeleteAll,
    NULL,
};

SMENUSTRUCT sSubDeleteAll_Video =
{
    MENUID_SUB_MENU_DELETE_ALL_VIDEO,
    IDS_DS_DELETE_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListDeleteAll_Video)/sizeof(PSMENUITEM),
    sMenuListDeleteAll_Video,
    NULL,
};

SMENUSTRUCT sSubDeleteAll_Image =
{
    MENUID_SUB_MENU_DELETE_ALL_IMAGE,
    IDS_DS_DELETE_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListDeleteAll_Image)/sizeof(PSMENUITEM),
    sMenuListDeleteAll_Image,
    NULL,
};
#endif

#if (MENU_EDIT_PROTECT_EN)
SMENUSTRUCT sSubProtect =
{
    MENUID_SUB_MENU_PROTECT,
    IDS_DS_PROTECT,
    &sMainMenuEdit,
    sizeof(sMenuListProtect)/sizeof(PSMENUITEM),
    sMenuListProtect,
    NULL,
};
#endif

#if (MENU_EDIT_PROTECT_ALL_EN)
SMENUSTRUCT sSubProtectAll =
{
    MENUID_SUB_MENU_PROTECT_ALL,
    IDS_DS_PROTECT_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListProtectAll)/sizeof(PSMENUITEM),
    sMenuListProtectAll,
    NULL,
};

SMENUSTRUCT sSubProtectAll_Video =
{
    MENUID_SUB_MENU_PROTECT_ALL_VIDEO,
    IDS_DS_PROTECT_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListProtectAll_Video)/sizeof(PSMENUITEM),
    sMenuListProtectAll_Video,
    NULL,
};

SMENUSTRUCT sSubProtectAll_Image =
{
    MENUID_SUB_MENU_PROTECT_ALL_IMAGE,
    IDS_DS_PROTECT_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListProtectAll_Image)/sizeof(PSMENUITEM),
    sMenuListProtectAll_Image,
    NULL,
};
#endif

#if (MENU_EDIT_UNPROTECT_ALL_EN)
SMENUSTRUCT sSubUnProtectAll =
{
    MENUID_SUB_MENU_UNPROTECT_ALL,
    IDS_DS_UNPROTECT_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListUnProtectAll)/sizeof(PSMENUITEM),
    sMenuListUnProtectAll,
    NULL,
};

SMENUSTRUCT sSubUnProtectAll_Video =
{
    MENUID_SUB_MENU_UNPROTECT_ALL_VIDEO,
    IDS_DS_UNPROTECT_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListUnProtectAll_Video)/sizeof(PSMENUITEM),
    sMenuListUnProtectAll_Video,
    NULL,
};

SMENUSTRUCT sSubUnProtectAll_Image=
{
    MENUID_SUB_MENU_UNPROTECT_ALL_IMAGE,
    IDS_DS_UNPROTECT_ALL,
    &sMainMenuEdit,
    sizeof( sMenuListUnProtectAll_Image)/sizeof(PSMENUITEM),
    sMenuListUnProtectAll_Image,
    NULL,
};
#endif

#if (MENU_EDIT_DELETE_SELECT_FORMAT)
SMENUSTRUCT sSubDeleteOne =
{
    MENUID_SUB_MENU_DELETE_ALL,
    IDS_DS_DELETE_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListDeleteOneFormat)/sizeof(PSMENUITEM),
    sMenuListDeleteOneFormat,
    NULL,
};
SMENUSTRUCT sSubProtectOne =
{
    MENUID_SUB_MENU_PROTECT_ALL,
    IDS_DS_PROTECT_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListProtectOneFormat)/sizeof(PSMENUITEM),
    sMenuListProtectOneFormat,
    NULL,
};

SMENUSTRUCT sSubUnProtectOne =
{
    MENUID_SUB_MENU_UNPROTECT_ALL,
    IDS_DS_UNPROTECT_ALL,
    &sMainMenuEdit,
    sizeof(sMenuListUnProtectOneFormat)/sizeof(PSMENUITEM),
    sMenuListUnProtectOneFormat,
    NULL,
};
#endif
 /*===========================================================================
 * Main body
 *===========================================================================*/
 #if (MENU_EDIT_DELETE_ONE_EN)
bool MenuItemDeleteOne(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_EDIT_DELETE_ALL_EN)
bool MenuItemDeleteAll(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_EDIT_DELETE_EN)
bool MenuItemDeleteFile(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_EDIT_PROTECT_ONE_EN)
bool MenuItemProtectOne(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_EDIT_PROTECT_ALL_EN)
bool MenuItemProtectAll(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_EDIT_UNPROTECT_ONE_EN)
bool MenuItemUnProtectOne(PSMENUITEM pItem)
{
    return true;
}
#endif
#if (MENU_EDIT_UNPROTECT_ALL_EN)
bool MenuItemUnProtectAll(PSMENUITEM pItem)
{
    return true;
}
#endif
bool MenuItemEditOneConfirmOk(PSMENUITEM pItem)
{
	return true;
}
