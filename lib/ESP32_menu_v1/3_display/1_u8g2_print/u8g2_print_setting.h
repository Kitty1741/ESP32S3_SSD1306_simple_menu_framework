#ifndef __U8G2_PRINT_SETTING_H__
#define __U8G2_PRINT_SETTING_H__

#include "0_config/config.h"

//是否启用动画风格(bool)
#define ENABLE_ANIM true


//定义U8G2使用的0.96屏幕类型
//IIC 或者 SPI
#define U8G2_MODE IIC
#if (U8G2_MODE == IIC)
//创建u8g2对象的SSD1306的IO接口
//只能选硬件IIC的接口
#define u8g2_SCL 9
#define u8g2_SDA 8
#elif (U8G2_MODE == SPI)
#endif

#endif