//image_macro.h
#ifndef __IMAGE_MACRO_H__
#define __IMAGE_MACRO_H__

#include "0_config/config.h"
#include "image_struct.h"

//定义了快速创建图像的宏

#define CREATE_IMAGE(NAME,WIDTH, ... )                                  \
static uint8_t NAME##_image_data[] = __VA_ARGS__;                       \
m_image_t NAME##_image = {                                              \
    .width = WIDTH,                                                     \
    .height = (lengthof(NAME##_image_data)+(WIDTH+7)/8-1)/((WIDTH+7)/8),\
    .image_data = NAME##_image_data,                                    \
    .if_black_background = true                                         \
};                                                                      \

//eg.
/*
CREATE_IMAGE( name , 8 , {
    0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,
} )

意味着
创建一个叫 "name_image" 的图像
图像内容是一个8x8实心方块
具体说是
{0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,}(低位优先)
*/

#endif