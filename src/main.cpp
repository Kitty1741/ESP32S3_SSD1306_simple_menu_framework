#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <menu_API.h>
#include <WLAN/WLAN.h>

void setup() {

  //test
  Serial.begin(115200);

  //初始化事件管理器
  init_MainEventManager();

  //keybord_init
  keybord_setup();

  //menu_init
  menu_init_u8g2();
}

extern char test_str[];

void loop(){
    sprintf(test_str,"ms:%d",millis());
    //主菜单
    set_menu_cursor( MAIN_MENU_INFO.data.menu_t );
    set_display_info( &MAIN_MENU_INFO );
}
