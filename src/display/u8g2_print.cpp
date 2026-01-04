#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include <menu/internal.h>//内部模块
#include <display/u8g2_print.h>

//这里只放打印函数


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE , u8g2_SCL , u8g2_SDA );

/*
    函数名字：menu_init
    函数功能：初始化所有和u8g2有关的东西
    返回值：没有
    参数：没有
*///
void menu_init_u8g2(){

    static bool if_first_setup = false;

    //如果是第一次初始化
    if( if_first_setup == false ){
        if_first_setup =  true;
        //u8g2执行初始化
        u8g2.begin();

        //u8g2初始设置
        u8g2.enableUTF8Print();    // 启用UTF-8支持，用于显示中文:cite[2]
        u8g2.setFont(u8g2_font_ncenB08_tr);  // 设置字体:cite[5]
        u8g2.setFont(u8g2_font_wqy12_t_gb2312); // 设置文泉驿点阵宋体12px:cite[2]
        u8g2.setFontPosTop();      // 设置字体绘制基准为顶部（默认为基线）

    }

    //重置u8g2设置
    u8g2.setFont(u8g2_font_ncenB08_tr);  // 设置字体:cite[5]
    u8g2.setFont(u8g2_font_wqy12_t_gb2312); // 设置文泉驿点阵宋体12px:cite[2]s
    u8g2.setDrawColor(2); //设置颜色,0透显,1实显,2XOR (drawCircle,drawDisc,drawEllipse和drawFilledEllipse不支持XOR模式) 

}

/*
    函数名字：u8g2_print_display_info
    函数功能：打印链表的一个节点
    返回值：没有
    参数：
        INFO
        类型：display_info
        作用：传递打印数据
*///
inline void u8g2_print_display_info_once(display_info *INFO){

    switch( INFO->mode ){
        case DISPLAY_MODE_NONE   :{}break;// 不显示
        case DISPLAY_MODE_LOADING:{
            u8g2_print_LOADING();
        }break;// 加载中
        case DISPLAY_MODE_INFO   :{
            u8g2_print_INFO( INFO );// 信息显示(简单提示)
        }break;
        case DISPLAY_MODE_MENU   :{
            u8g2_print_menu( INFO->data.menu_t );
        }break;// 菜单显示
        case DISPLAY_MODE_LIST   :{
            u8g2_print_list( INFO );
        }break;// 文字列表
        case DISPLAY_MODE_IMAGE  :{

        }break;// 图片显示
    }
}

/*
    函数名字：u8g2_print_display_info
    函数功能：打印一大根链表
    返回值：没有
    参数：
        INFO
        类型：display_info*
        作用：作为一个含有打印信息的链表的头传递数据
*///
void u8g2_print_display_info( display_info *INFO ){

    u8g2.clearBuffer();    // 清Buffer缓冲区的数

    display_info *INFOptr = INFO;//创建一个指针
    while( INFOptr != NULL ){//如果当前指针不是空指针
        u8g2_print_display_info_once(INFOptr);//每打印一次
        INFOptr = INFOptr->next;//指针向后移位
    }

    u8g2.sendBuffer();    // 将Buffer帧缓冲区的内容发送到显示器,发送刷新消息

}




/*
    函数名字：u8g2_print_INFO
    函数功能：打印简单信息
    返回值：没有
    参数：
        INFO
        类型：display_info*
        作用：传递要打印的简单信息
*///
void u8g2_print_INFO( display_info *INFO ){

    for(int i=0;i<64;i++){
        if( INFO->data.str[i] == NULL ){
            break;
        }
        u8g2.drawUTF8( INFO->x , 12*i + INFO->y , INFO->data.str[i] );
    }

}

/*
    函数名字：u8g2_print_LOADING
    函数功能：打印“加载中...”
    返回值：没有
    参数：没有
*///
void u8g2_print_LOADING(){

    switch( millis() / 200 % 4 ){
        case 0:u8g2.drawUTF8( 4 , 2 , "加载中..." );break;
        case 1:u8g2.drawUTF8( 4 , 2 , "加载中...." );break;
        case 2:u8g2.drawUTF8( 4 , 2 , "加载中....." );break;
        case 3:u8g2.drawUTF8( 4 , 2 , "加载中......" );break;
    }
}


/*
    函数名字：u8g2_print_menu
    函数功能：打印给定菜单
    返回值：没有
    参数：
        MENU
        类型：menu*
        作用：告诉函数应该打印哪个菜单
*///
void u8g2_print_menu( menu *MENU ){

    static uint8_t view_line = 0;//显示的第一行
    static uint8_t width;//打印字符的宽度(用来设置光标)

    //通过光标计算屏幕所在行
    if( MENU->length < 4 ){
      view_line = 0;
    }else{
      MENU->cursor == 0                 ? view_line = 0 :
      MENU->cursor == MENU->length -2   ? view_line = MENU->cursor -2 :
      MENU->cursor == MENU->length -1   ? view_line = MENU->cursor -3 :
      /*default*/view_line = MENU->cursor -1;
    }

    //显示到U8G2
    u8g2.drawUTF8(3 ,3 , MENU->name );//画菜单名字
    u8g2.drawFrame(0, 1, 128, 16); //画空心矩形

    for(int i=0; i<4; i++){
      if( i < MENU->length ){
        u8g2.drawUTF8(4 ,18+12*i , MENU->menu_list[ i + view_line ].name );//打印选项名字
      }
    } 
    width = u8g2.getUTF8Width( MENU->menu_list[ MENU->cursor ].name) +6;//打印光标
    u8g2.drawBox( 2 , ( MENU->cursor - view_line )*12 +17 , width , 12 ); 
    u8g2.drawBox( 127 , ( MENU->cursor / 1.0 / ( MENU->length -1 ) )*40+17 , 1 , 7 ); //打印位置指示器

    return;
}



/*
    函数名字：u8g2_print_LIST
    函数功能：打印可以调整观看位置的列表
    返回值：没有
    参数：
        INFO
        类型：display_info*
        作用：传递要打印的列表信息
*///
void u8g2_print_list( display_info *INFO ){

    uint8_t list_view_line = INFO->data.list_t->cursor;//列表显示在屏幕上的第一行对应光标行数

    for(int i=0;i<5;i++){//屏幕上一共可以显示五行
        if( INFO->data.list_t->list[ i + list_view_line ] == NULL ){
            break;
        }//防空指针
        u8g2.drawUTF8(//打印对应行内容
            /*起始横坐标*/INFO->x ,
            /*起始纵坐标*/INFO->y + 12*i ,
            /* 打印内容 */INFO->data.list_t->list[ i + list_view_line ]
        );
    }
}