#ifndef __CONFIG_H___
#define __CONFIG_H___

#include "0_config/macro/get_time/get_time.h"
#include "0_config/macro/lengthof()/lengthof().h"

//全局设置

//长按时间阈值（ms）
#define LONG_PRESS_THRESHOLD 400

//是否开启调试模式(串口发送调试信息)(1/0)
#define IF_DEBUG 0
#if( IF_DEBUG == 1 )

#define IF_DEBUG_0 0//允许调试不同层
#define IF_DEBUG_1 0
#define IF_DEBUG_2 1
#define IF_DEBUG_3 1
#define IF_DEBUG_4 0

#endif

//该层初始化清单
#define INIT_LIST_0 \
    ;

#endif