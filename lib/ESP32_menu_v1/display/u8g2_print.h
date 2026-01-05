#ifndef __U8G2_PRINT_H__
#define __U8G2_PRINT_H__

#include <global.h>
//menu.h
typedef struct option_t option;
typedef struct menu_t menu;

//最常用的那个
void set_display_info( display_info *INFO );

//初始化函数
void menu_init_u8g2();

#endif