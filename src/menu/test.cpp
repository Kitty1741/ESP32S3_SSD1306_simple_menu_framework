#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu\menu.h>
#include <menu\u8g2_print.h>

extern menu MAIN_MENU;

char test_str[64] = "hello";
static display_info TEST_INFO = {
    .mode = DISPLAY_MODE_INFO,//输出内容的类型
    .data = { .str = { test_str, test_str,test_str} },
    .x = 64,.y = 20,
    .next = NULL,//链表结构，方便叠加图层
};
static display_info TEST_MENU = {
    .mode = DISPLAY_MODE_MENU,//输出内容的类型
    .data = { .menu_data = &MAIN_MENU },
    .x = 0,.y = 0,
    .next = &TEST_INFO,//链表结构，方便叠加图层
};

//测试函数，检测这玩意能不能跑
void test_loop(){

    set_cursor( TEST_MENU.data.menu_data );
    u8g2_print_display_info( &TEST_MENU );
}
