#ifndef __MENU_H__
#define __MENU_H__

//这个模块包含了对外的函数接口
//用户应该调用这个模块

//显示类型结构定义

/*
菜单 MENU
*///----------------------------------------------------------
//菜单选项结构体
typedef struct option_t{

    char name[40];
    bool (*callback)(void*);//这里放回调函数指针和回调函数参数
    void* param;            //task_loop的参数

}option;

//菜单结构体
typedef struct menu_t{

    const char *name;//菜单的标题
    int length;//菜单的列表长度
    unsigned char cursor;//菜单的光标位置
    option *menu_list;//菜单对应的选项列表

}menu;

/*    
列表 LIST
*///----------------------------------------------------------
//列表结构体
typedef struct list_t{

    const char *name;//列表的标题
    unsigned char cursor;//列表的光标位置
    const char *list[64];//菜单对应的列表数组

}list;

/*    
设置 SITTING
*///----------------------------------------------------------
//设置结构体
//枚举设置参数类型
typedef enum setting_type_t{
    SET_TYPE_INT,       //整数
    SET_TYPE_FLOAT,     //浮点
    SET_TYPE_CHAR,     //字符
    SET_TYPE_STRING,    //字符串
    SET_TYPE_ARROW_LIST,//数组（列表格式复用）
}setting_type;

//设置结构体
typedef struct setting_t{

    const char* name;//设置选项名字
    setting_type type;//数据类型
    void* setting_object;//对应修改的数据指针
    uint8_t cursor;//光标
    bool select;//是否选中选项

}setting;





//声明主菜单，这个loop()要用
extern menu MAIN_MENU;
extern display_info MAIN_MENU_INFO;

//对外声明函数
void task_loop( bool (*function)(void*) , void* param );
bool set_menu_cursor( menu *MENU );
bool set_list_cursor( list *LIST );
bool set_setting_cursor( setting *SIT );
bool set_EZ_cursor( setting *SIT );

#endif

