#include <Arduino.h>
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

  //INIT()
  system_init();
}

void loop(){
    //主菜单
    run_info_data( &MAIN_MENU_INFO );
}
