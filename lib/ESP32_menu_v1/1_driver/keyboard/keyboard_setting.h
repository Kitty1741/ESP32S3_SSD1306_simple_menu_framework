#ifndef __KEYBOARD_SETTING_H__
#define __KEYBOARD_SETTING_H__

#include "0_config/config.h"

//键值枚举对应数值
#define KEY_NULL_VALUE 0
#define KEY_UP_NUM_VALUE 1
#define KEY_OK_NUM_VALUE 2
#define KEY_DOWN_NUM_VALUE 3
#define KEY_BACK_NUM_VALUE 4

//菜单必须的四个GPIO的设置
//依次对应四个功能
#define UP_NUM_IO   10
#define OK_NUM_IO   11
#define DOWN_NUM_IO 12
#define BACK_NUM_IO 13


//中断扫描键盘的定时器选择
//可选 0 1 2 3 4     5  
//    ~~~~~~~~ ↑     ↑
//   硬件定时器 软件 不定时，你来操作
//
//默认用硬件定时器(3)
#define use_which_timer 3

#endif