#include <Arduino.h>

#include "3_display/1_u8g2_print/u8g2_print_internal.h"

#include "DisplayManager_setting.h"
#include "DisplayManager_internal.h"
#include "DisplayManager.h"

//自动打印的display_info变量
display_info PRINT_INFO;

//freeRTOS
SemaphoreHandle_t DisplayMutex = NULL;//显示互斥锁
QueueHandle_t  DisplayUpdateSem = NULL;//显示刷新信号
TaskHandle_t DisplayTask;//显示任务

/*
    函数名字：set_display_info
    函数功能：设置打印内容并打印一次
    返回值：没有
    参数：
        INFO
        类型：display_info*
        作用：设置打印链表的头
*///
void set_display_info( display_info *INFO ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("set_display_info()");
    #endif

    static display_info STATIC_INFO;//防止INFO指向临时变量
    STATIC_INFO = *INFO;

    if( xSemaphoreTake( DisplayMutex, 20 ) == pdTRUE ){//如果互斥锁打开
        PRINT_INFO = STATIC_INFO;//更新
        xSemaphoreGive( DisplayMutex );//开锁
        xSemaphoreGive( DisplayUpdateSem );//更新显示信号
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
        //检测到刷新信号就刷新
        xSemaphoreTake( DisplayUpdateSem , portMAX_DELAY );
                 /*关闭↓互斥锁，防止这时正好有人改动输出画面*/
        if( xSemaphoreTake( DisplayMutex, 0 ) == pdTRUE ){//如果关锁成功
            u8g2_print_display_info( &PRINT_INFO );//打印信息
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
        12288,               // 任务栈大小（字节）
        NULL,               // 传递给任务的参数（本例为空）
        3,                 // 任务优先级（1-24）
        &DisplayTask      //任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
    );
    xSemaphoreGive( DisplayUpdateSem );//初始化后发送刷新信号
}