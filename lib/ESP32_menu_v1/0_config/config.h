#ifndef __CONFIG_H___
#define __CONFIG_H___

//全局设置

//长按时间阈值（ms）
#define LONG_PRESS_THRESHOLD 500

//是否开启调试模式(串口发送调试信息)(true/false)
#define IF_DEBUG false
#if( IF_DEBUG == true )

#define IF_DEBUG_0 true//允许调试不同层?
#define IF_DEBUG_1 true
#define IF_DEBUG_2 true
#define IF_DEBUG_3 true
#define IF_DEBUG_4 true

#endif

//该层初始化清单
#define INIT_LIST_0 \
    ;

#endif