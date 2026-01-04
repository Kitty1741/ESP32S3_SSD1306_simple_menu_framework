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





//声明主菜单，这个loop()要用
extern menu MAIN_MENU;

//对外声明函数
void task_loop( bool (*function)(void*) , void* param );
bool do_nothing( void* do_nothing );
void menu_init_u8g2();
bool set_menu_cursor( menu *MENU );
bool set_list_cursor( list *LIST );
display_info image_to_display_info( char IMAGE[1024] );
display_info config_menu_display_info(menu *MENU);
display_info config_list_display_info(list *LIST);

//测试test
void test_loop();

#endif