//这里有各种编译时的设置
//调整以适配你的功能


//菜单必须的五个键值的设置
//依次对应五个枚举
#define KEY_NULL_VALUE 0
#define KEY_UP_NUM_VALUE 1
#define KEY_OK_NUM_VALUE 2
#define KEY_DOWN_NUM_VALUE 3
#define KEY_BACK_NUM_VALUE 4

//菜单必须的四个GPIO的设置
//依次对应四个功能
#define UP_NUM_IO   10
#define OK_NUM_IO   11
#define DOWN_NUM_IO 12
#define BACK_NUM_IO 13


//中断扫描键盘的定时器选择
//可选 0 1 2 3 4     5  
//    ~~~~~~~~ ↑     ↑
//   硬件定时器 软件 不定时，你来操作
//
//默认用硬件定时器(3)
#define use_which_timer 3

//创建u8g2对象的SSD1306的IO接口
//只能选硬件IIC的接口
#define u8g2_SCL 9
#define u8g2_SDA 8

//是否启用动画?
#define ENABLE_ANIM true
#if( ENABLE_ANIM == true )
#endif