//image.h
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "image_struct.h"
#include "image_macro.h"

//模式设置函数
void set_black_image_background( m_image_t* IMAGE , bool if_black );
void rotate_image(m_image_t* IMAGE, uint8_t n);

#endif