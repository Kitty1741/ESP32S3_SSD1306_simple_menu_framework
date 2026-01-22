#ifndef __API_RECALL_H__
#define __API_RECALL_H__

//包含下层文件
#include "1_driver/driver.h"
#include "2_engine/engine.h"
#include "3_display/display.h"

#include "4_API/0_API_function/API_function.h"

//recall
bool run_info(void* param);
bool run_list(void* param);
bool run_menu(void* param);
bool do_nothing( void* do_nothing );

#endif