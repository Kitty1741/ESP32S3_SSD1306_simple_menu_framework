#include <Arduino.h>
#include <global.h>

//我再在头文件建变量我是傻逼
menu_event MainEventManager;
menu_keybord MainEventManager_keybord_status;
display_info MainEventManager_display;

//初始化事件管理器
void init_MainEventManager(){

    MainEventManager.keybord_status = &MainEventManager_keybord_status;
    //MainEventManager.display = &MainEventManager_display;

    MainEventManager.keybord_status->key_enum = KEY_NULL;
    MainEventManager.keybord_status->key_value = 0;
    MainEventManager.keybord_status->press_time = 0;

    //MainEventManager.display->data.menu_t = NULL;
    //MainEventManager.display->mode = DISPLAY_MODE_NONE;
    //MainEventManager.display->next = NULL;
    //MainEventManager.display->x = 0;
    //MainEventManager.display->y = 0;
}
