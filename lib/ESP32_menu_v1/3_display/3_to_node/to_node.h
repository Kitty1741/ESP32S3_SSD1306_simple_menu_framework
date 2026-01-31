#ifndef __TO_DISPLAY_INFO__
#define __TO_DISPLAY_INFO__

//本文件声明了用于把各种类型转化为打印类型的函数
#include <Arduino.h>

//包含结构声明
#include "3_display/1_u8g2_print/u8g2_print_struct.h"

m_ui_node_t to_node( m_menu_t *MENU );
m_ui_node_t to_node( m_list_t *LIST );
m_ui_node_t to_node( m_image_t* IMAGE );
m_ui_node_t to_node( m_setting_t *SET);

m_ui_node_t to_node(m_menu_t *MENU,uint8_t x,uint8_t y);
m_ui_node_t to_node(m_list_t *LIST,uint8_t x,uint8_t y);
m_ui_node_t to_node(m_image_t* IMAGE,uint8_t x,uint8_t y);
m_ui_node_t to_node(m_setting_t *SET,uint8_t x,uint8_t y);

#endif