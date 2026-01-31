#ifndef __DISPLAY_H__
#define __DISPLAY_H__


#include "3_display/1_u8g2_print/u8g2_print.h"
#include "3_display/2_set_node/set_node.h"
#include "3_display/2_DisplayManager/DisplayManager.h"
#include "3_display/3_to_node/to_node.h"
#include "3_display/4_macro/create_node_macro.h"

//该层初始化清单
#define INIT_LIST_3     \
    u8g2_print_init();   \
    DisplayManager_init();\

#endif