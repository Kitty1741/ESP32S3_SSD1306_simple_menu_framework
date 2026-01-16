#include <Arduino.h>
#include <global.h>

//我再在头文件建变量我是傻逼
menu_event MainEventManager;
menu_keybord MainEventManager_keybord_status;
display_info MainEventManager_display;

//freeRTOS
SemaphoreHandle_t DisplayMutex = NULL;//显示互斥锁
QueueHandle_t  DisplayUpdateSem = NULL;//显示刷新信号
TaskHandle_t DisplayTask;//显示任务

/*
    函数名字：ManagerDisplay
    函数功能：调用数据管理器的打印内容并打印，由freeRTOS事件调用
    返回值：没有
    参数：
        no_param
        类型：void*
        意义：由freeRTOS调用的回调函数必须要有个void*参数
*///
void DisplayManager( void* no_param ){

    while(1){
        //检测到刷新信号就刷新
        xSemaphoreTake( DisplayUpdateSem , portMAX_DELAY );
                 /*关闭↓互斥锁，防止这时正好有人改动输出画面*/
        if( xSemaphoreTake( DisplayMutex, 0 ) == pdTRUE ){//如果关锁成功
            u8g2_print_display_info(MainEventManager.display);//打印信息
            xSemaphoreGive( DisplayMutex );//开锁
        }vTaskDelay(1);
    }
}

//初始化事件管理器
void init_MainEventManager(){

    //初始化互斥锁
    DisplayMutex = xSemaphoreCreateMutex();//这个信号量当互斥锁信号处理
    DisplayUpdateSem = xSemaphoreCreateBinary();//这个信号量当二进制信号处理

    xTaskCreate(
        DisplayManager,     // 任务函数指针
        "ManagerDisplay",   // 任务名称（调试用）
        12288,               // 任务栈大小（字节）
        NULL,               // 传递给任务的参数（本例为空）
        3,                 // 任务优先级（1-24）
        &DisplayTask      //任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
    );
    xSemaphoreGive( DisplayUpdateSem );//第一次时间刷新，防止开机黑屏

    MainEventManager.keybord_status = &MainEventManager_keybord_status;
    MainEventManager.display = &MainEventManager_display;

    MainEventManager.keybord_status->key_enum = KEY_NULL;
    MainEventManager.keybord_status->key_value = 0;
    MainEventManager.keybord_status->press_time = 0;

    MainEventManager.display->data.menu_t = NULL;
    MainEventManager.display->mode = DISPLAY_MODE_NONE;
    MainEventManager.display->next = NULL;
    MainEventManager.display->x = 0;
    MainEventManager.display->y = 0;
}