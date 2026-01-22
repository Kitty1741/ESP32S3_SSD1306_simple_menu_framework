#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "image_struct.h"

//模式设置函数
void set_black_image_background( image* IMAGE , bool if_black );
void rotate_image(image* IMAGE, uint8_t n);

#endif