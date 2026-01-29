#ifndef __U8G2_PRINT_H__
#define __U8G2_PRINT_H__

//u8g2库依赖文件
#include <U8g2lib.h>
#include <Wire.h>

//设置
#include "u8g2_print_setting.h"

//初始化函数
void u8g2_print_init();

//对外声明u8g2类
#if (U8G2_MODE == IIC)
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
#endif

#endif