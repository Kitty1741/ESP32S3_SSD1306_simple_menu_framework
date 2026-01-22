#ifndef __KEYBOARD_STRUCT_H__
#define __KEYBOARD_STRUCT_H__

#include <Arduino.h>

//设置
#include "keyboard_setting.h"

/*  键盘  */
/*
键盘定时自动扫描,键值存储在全局变量中
keyboard里面的函数可以读取全局变量的键值
*/


//枚举键值
typedef enum KEY_VALUE_t{

    KEY_NULL     =   KEY_NULL_VALUE,//没有按键按下
    KEY_UP_NUM   =   KEY_UP_NUM_VALUE,//“上”键
    KEY_OK_NUM   =   KEY_OK_NUM_VALUE,//确认键
    KEY_DOWN_NUM =   KEY_DOWN_NUM_VALUE,//“下”键
    KEY_BACK_NUM =   KEY_BACK_NUM_VALUE,//返回键

}KEY_VALUE;

//按键信息结构体
typedef struct menu_keyboard_t{

    uint8_t key_enum;
    uint8_t key_value;
    uint8_t press_time;

}menu_keyboard;

//声明
extern menu_keyboard keyboard_status;

#endif