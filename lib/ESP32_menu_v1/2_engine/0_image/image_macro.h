#ifndef __IMAGE_MACRO_H__
#define __IMAGE_MACRO_H__

#include "0_config/config.h"
#include "image_struct.h"

#define CREATE_IMAGE(NAME,WIDTH, ... )                                  \
static uint8_t NAME##_image_data[] = __VA_ARGS__;                       \
image NAME##_image = {                                                  \
    .width = WIDTH,                                                     \
    .height = (lengthof(NAME##_image_data)+(WIDTH+7)/8-1)/((WIDTH+7)/8),\
    .image_data = NAME##_image_data,                                    \
    .if_black_background = true                                         \
};                                                                      \

#endif