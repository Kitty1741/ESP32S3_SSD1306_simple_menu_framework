#ifndef __MENU_INTERNAL_H__
#define __MENU_INTERNAL_H__

//这个模块用来声明menu内部函数
//其他模块不应调用

#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu/menu.h>
#include <display/u8g2_print.h>

//extern声明u8g2类
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

//声明主菜单，这个loop()要用
extern menu MAIN_MENU;

//对内声明函数


//测试test
void test_loop();
extern bool test_print_num(void*);

#endif