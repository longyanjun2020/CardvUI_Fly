#include "entry/EasyUIContext.h"
#include "uart/UartContext.h"
#include "manager/ConfigManager.h"
#include "carimpl/MenuCommon.h"
#include "carimpl/KeyEventContext.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

void onEasyUIInit(EasyUIContext *pContext) {
    // 初始化时打开串口
    //printf("get uart name %s\n", CONFIGMANAGER->getUartName().c_str());

    if(ParseMenuSet(MenuCfgFile, MenuSettingConfig()) != 0) {
        printf("###############################\r\n"
                "--E-- No Default Settings\r\n"
                "###############################\r\n");
        MenuSettingInit();
    }

    //UARTCONTEXT->openUart(CONFIGMANAGER->getUartName().c_str(), CONFIGMANAGER->getUartBaudRate());
    start_key_event_ctx();
}

void onEasyUIDeinit(EasyUIContext *pContext) {
    //UARTCONTEXT->closeUart();
    stop_key_event_ctx();
}

const char* onStartupApp(EasyUIContext *pContext) {
    //	return "emptyActivity";
    return "mainActivity";
	//return "VideoMenuActivity";
}


#ifdef __cplusplus
}
#endif  /* __cplusplus */

