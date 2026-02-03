#ifndef __U8G2_CREATE_SETTING_H__
#define __U8G2_CREATE_SETTING_H__

#include "0_config/config.h"

//本文件用来定义和声明U8G2对象

#define _U8G2_CLASS U8G2_SSD1306_128X64_NONAME_F_HW_I2C

#define _CREATE_U8G2                     \
_U8G2_CLASS u8g2(                        \
        /*rotation*/U8G2_R0,             \
        /*reset*/ U8X8_PIN_NONE ,        \
        /*SCL*/ 9,                       \
        /*SDA*/ 8                        \
);                                       
extern _U8G2_CLASS u8g2;

#endif