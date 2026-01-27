#ifndef __TO_DISPLAY_INFO__
#define __TO_DISPLAY_INFO__

//本文件声明了用于把各种类型转化为打印类型的函数

//包含结构声明
#include "3_display/1_u8g2_print/u8g2_print_struct.h"

void link_info(display_info* A,display_info* B);
display_info to_display_info( menu *MENU );
display_info to_display_info( list *LIST );
display_info to_display_info( image* IMAGE );
display_info to_display_info( image* IMAGE , uint8_t x , uint8_t y);
display_info to_display_info(setting *SET);

#endif