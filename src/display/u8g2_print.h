#ifndef __U8G2_PRINT_H__
#define __U8G2_PRINT_H__

#include <global.h>
//menu.h
typedef struct option_t option;
typedef struct menu_t menu;

//最常用的那个
void u8g2_print_display_info( display_info *INFO );

//具体的打印函数
void u8g2_print_INFO( display_info *INFO );
void u8g2_print_LOADING();
void u8g2_print_menu( menu *MENU );
void u8g2_print_INFO( display_info *INFO );
void u8g2_print_list( display_info *INFO );

#endif