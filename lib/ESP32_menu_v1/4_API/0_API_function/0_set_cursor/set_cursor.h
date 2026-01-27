#ifndef __SET_CURSOR_H__
#define __SET_CURSOR_H__

//本文件声明了用于设置各种光标的函数

//下级依赖函数
#include "2_engine/engine.h"
#include "2_engine/engine_struct.h"
#include "3_display/display_struct.h"

bool set_cursor( display_info* INFO );
bool set_cursor( menu* MENU );
bool set_cursor( list* LIST );
bool set_cursor( setting* SET );

#endif