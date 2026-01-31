#ifndef __TO_DISPLAY_INFO_PRIVATE__
#define __TO_DISPLAY_INFO_PRIVATE__

#include <Arduino.h>

//包含结构声明
#include "3_display/1_u8g2_print/u8g2_print_struct.h"

m_ui_node_t image_to_node( m_image_t* IMAGE,uint8_t x,uint8_t y );
m_ui_node_t menu_to_node(  m_menu_t *MENU );
m_ui_node_t list_to_node(  m_list_t *LIST ,uint8_t x,uint8_t y);
m_ui_node_t setting_to_node( m_setting_t *SET );

#endif