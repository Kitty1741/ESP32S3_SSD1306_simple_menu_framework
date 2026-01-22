#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

//对上级声明的文件

#include <Arduino.h>

#include "keyboard_struct.h"

//这块别改
void keyboard_init();//向外部声明初始化函数
uint8_t get_key_value();//松手后得到一次键值，然后销毁键值
uint8_t get_last_key();//返回一次键值
uint16_t get_press_time();//得到按下时间


//用户可以在user_defined.cpp中
//自定义中断使用的扫描函数
//确保不同的键盘外设可以使用

//键盘扫到的值和按键时长会被存到静态结构体
//keyboard_status里面
//通过函数调用

#endif