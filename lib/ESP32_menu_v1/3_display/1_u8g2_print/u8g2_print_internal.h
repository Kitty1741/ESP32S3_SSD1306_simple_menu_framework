#ifndef __U8G2_PRINT_INTERNAL_H__
#define __U8G2_PRINT_INTERNAL_H__

#include "u8g2_print_struct.h"

//内部打印函数
//通用打印函数
void u8g2_print_display_info( display_info *INFO );

//具体的打印函数
void u8g2_print_LOADING();
void u8g2_print_menu( menu *MENU );
void u8g2_print_TEXT( display_info *INFO );
void u8g2_print_list( display_info *INFO );
void u8g2_print_BMP(display_info* INFO);
void u8g2_print_setting( setting* SIT );

#endif
