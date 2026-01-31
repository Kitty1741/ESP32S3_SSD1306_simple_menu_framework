#ifndef __U8G2_PRINT_INTERNAL_H__
#define __U8G2_PRINT_INTERNAL_H__

#include "u8g2_print_struct.h"

//内部打印函数
//通用打印函数
void u8g2_print_ui_node( m_ui_node_t* node );

//具体的打印函数
void u8g2_print_LOADING();
void u8g2_print_menu( m_ui_node_t* node );
void u8g2_print_list( m_ui_node_t* node );
void u8g2_print_image( m_ui_node_t* node );
void u8g2_print_setting( m_ui_node_t* node );

#endif
