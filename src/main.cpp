#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <menu_API.h>

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

void loop() {

  test_loop();

}
