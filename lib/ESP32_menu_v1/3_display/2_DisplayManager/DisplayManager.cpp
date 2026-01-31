#include <Arduino.h>

#include "3_display/1_u8g2_print/u8g2_print_internal.h"

#include "DisplayManager_setting.h"
#include "DisplayManager_internal.h"
#include "DisplayManager.h"

//打印调用的指针
m_ui_node_t* PRINT_INFO;

//freeRTOS
SemaphoreHandle_t DisplayMutex = NULL;//显示互斥锁
QueueHandle_t  DisplayUpdateSem = NULL;//显示刷新信号
TaskHandle_t DisplayTask;//显示任务

/*
    函数名字：display_set
    函数功能：设置打印内容
    返回值：
        类型：bool
        意义：设置是否成功
    参数：
        node
        类型：m_ui_node_t*
        作用：设置打印链表的头
*///
bool display_set( m_ui_node_t* node ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("set_display_info()");
    #endif

    //脏检测待实现
    if( xSemaphoreTake( DisplayMutex, 20 ) == pdTRUE ){//如果没上锁，上锁
        PRINT_INFO = node;//更新显示信息
        xSemaphoreGive( DisplayMutex );//开锁
        return true;//设置成功
    }   return false;//没等到锁算设置失败
}

/*
    函数名字：display_refresh
    函数功能：打印一次打印内容
    返回值：没有
    参数：没有
*///
void display_refresh(){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("display_refresh()");
    #endif

    if( xSemaphoreTake( DisplayMutex, 20 ) == pdTRUE ){//如果没上锁
        xSemaphoreGive( DisplayMutex );//开锁
        xSemaphoreGive( DisplayUpdateSem );//发送更新显示信号
    }
}

/*
    函数名字：DisplayManager
    函数功能：打印数据管理器的打印内容，由freeRTOS事件调用
    返回值：没有
    参数：
        no_param
        类型：void*
        意义：由freeRTOS调用的回调函数必须要有个void*参数
*///
void DisplayManager( void* no_param ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("DisplayManager()");
    #endif

    while(1){
        xSemaphoreTake( DisplayUpdateSem , portMAX_DELAY );//检测到刷新信号，从这里开始执行
        if( xSemaphoreTake( DisplayMutex, 200 ) == pdTRUE ){//如果没上锁
            u8g2_print_ui_node( PRINT_INFO );//打印信息
            xSemaphoreGive( DisplayMutex );//开锁
        }vTaskDelay(1);
    }
}

void DisplayManager_init(){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("DisplayManager_init()");
    #endif

    //初始化互斥锁
    DisplayMutex = xSemaphoreCreateMutex();//创建互斥锁
    DisplayUpdateSem = xSemaphoreCreateBinary();//创建二进制信号

    xTaskCreate(
        DisplayManager,        // 任务函数指针
        "DisplayManager",     // 任务名称（调试用）
        10240,               // 任务栈大小（字节）
        NULL,               // 传递给任务的参数（本例为空）
        3,                 // 任务优先级（1-24）
        &DisplayTask      //任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
    );
    xSemaphoreGive( DisplayUpdateSem );//初始化后发送刷新信号
}