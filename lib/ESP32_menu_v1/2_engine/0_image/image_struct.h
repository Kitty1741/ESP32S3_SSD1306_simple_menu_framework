#ifndef __IMAGE_STRUCT_H__
#define __IMAGE_STRUCT_H__

#include <Arduino.h>

//图片结构体
typedef uint8_t* image_arrow;
typedef struct image_t{
    uint8_t width;
    uint8_t height;
    image_arrow image_data;//图片数据
    bool if_black_background;//选项，背景是否黑色(否则不是)
}image;

#endif