#ifndef __IMAGE_STRUCT_H__
#define __IMAGE_STRUCT_H__

#include <Arduino.h>

//定义图片类型用来存储图片
typedef uint8_t* image_arrow;
typedef struct image_t{
    uint8_t width;//图片的宽度
    uint8_t height;//图片的高度
    image_arrow image_data;//一维数组指针，指向图片数据
    bool if_black_background;//选项，背景是否黑色(否则不是)
}image;

#endif