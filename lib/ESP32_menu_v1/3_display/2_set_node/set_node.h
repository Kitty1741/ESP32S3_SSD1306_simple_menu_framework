#ifndef __SET_NODE_H__
#define __SET_NODE_H__

#include <Arduino.h>
#include "3_display/1_u8g2_print/u8g2_print_struct.h"

void node_link(m_ui_node_t* A,m_ui_node_t* B);
void node_init(m_ui_node_t* node);
void node_init( m_ui_node_t* node , uint8_t x , uint8_t y );
void node_set_xy( m_ui_node_t* node , uint8_t x ,uint8_t y );

#endif