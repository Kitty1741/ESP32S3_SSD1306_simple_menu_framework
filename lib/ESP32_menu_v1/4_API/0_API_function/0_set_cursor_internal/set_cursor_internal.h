#ifndef __SET_CURSOR_INTERNAL_H__
#define __SET_CURSOR_INTERNAL_H__

//本文件声明了用于设置各种光标的函数

//下级依赖函数
#include "2_engine/engine_struct.h"
#include "3_display/display_struct.h"

bool set_cursor( m_ui_node_t* node );
bool set_cursor( m_menu_t* MENU );
bool set_cursor( m_list_t* LIST );
bool set_cursor( m_setting_t* SET );

#endif