#ifndef __TO_DISPLAY_INFO__
#define __TO_DISPLAY_INFO__

//本文件声明了用于把各种类型转化为打印类型的函数

//包含下层结构声明
#include "3_display/display_struct.h"

void link_info(display_info* A,display_info* B);
display_info to_display_info( menu *MENU );
display_info to_display_info( list *LIST );
display_info to_display_info( image* IMAGE );
display_info to_display_info( image* IMAGE , uint8_t x , uint8_t y);

#endif