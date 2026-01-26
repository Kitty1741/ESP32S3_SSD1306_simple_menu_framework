#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "2_engine/engine.h"
#include "3_display/0_image_src/internal_image.h"

#include "u8g2_print_setting.h"
#include "u8g2_print_struct.h"
#include "u8g2_print_internal.h"
#include "u8g2_print.h"

//这里只放打印函数

#if (U8G2_MODE == IIC)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE , u8g2_SCL , u8g2_SDA );
#elif (U8G2_MODE == SPI)

#endif

/*
    函数名字：u8g2_print_init
    函数功能：初始化所有和u8g2有关的东西
    返回值：没有
    参数：没有
*///
void u8g2_print_init(){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_init()");
    #endif

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
        类型：display_info*
        作用：传递打印数据
*///
inline void u8g2_print_display_info_once(display_info *INFO){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_display_info_once()");
    #endif

    switch( INFO->mode ){
        case DISPLAY_MODE_NONE   :{}break;// 不显示
        case DISPLAY_MODE_LOADING:{
            u8g2_print_LOADING();
        }break;// 加载中
        case DISPLAY_MODE_TEXT   :{
            u8g2_print_TEXT( INFO );
        }break;// 信息显示(简单提示)
        case DISPLAY_MODE_MENU   :{
            u8g2_print_menu( INFO->data.menu_t );
        }break;// 菜单显示
        case DISPLAY_MODE_LIST   :{
            u8g2_print_list( INFO );
        }break;// 文字列表
        case DISPLAY_MODE_IMAGE  :{
            u8g2_print_BMP( INFO );
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

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_display_info()");
    #endif

    u8g2.clearBuffer();    // 清Buffer缓冲区的数

    display_info *INFOptr = INFO;//创建一个指针
    while( INFOptr != NULL ){//如果当前指针不是空指针
        u8g2_print_display_info_once(INFOptr);//每打印一次
        INFOptr = INFOptr->next;//指针向后移位
    }

    u8g2.sendBuffer();    // 将Buffer帧缓冲区的内容发送到显示器,发送刷新消息

}




/*
    函数名字：u8g2_print_TEXT
    函数功能：打印简单信息
    返回值：没有
    参数：
        INFO
        类型：display_info*
        作用：传递要打印的简单信息
*///
void u8g2_print_TEXT( display_info *INFO ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_TEXT()");
    #endif

    for(int i=0;i<6;i++){
        if( INFO->data.str[i] == NULL ){
            break;
        }
        u8g2.drawUTF8( INFO->x , 12*i + INFO->y , INFO->data.str[i] );
    }

}


/*
    函数名字：u8g2_print_LOADING
    函数功能：打印加载界面
    返回值：没有
    参数：没有
*///
void u8g2_print_LOADING(){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_LOADING()");
    #endif

    //初始化
    static uint32_t frame = 0;
    image* WORD_IMG = &mystery_chinese_word_loading;
    display_info WORD;
    
    //设置显示文字  
    WORD.mode = DISPLAY_MODE_IMAGE; 
    WORD.x = 40;  WORD.y = 23;             
    WORD.data.img = WORD_IMG;         
    u8g2_print_BMP( &WORD );//不要引入新字体，吃我内存
    
    //显示动画
    vTaskDelay( 50 );
    frame++;
    #if ( ENABLE_ANIM == true )
      float_t x1 = sin( frame * 0.2 );
      float_t x2 = sin( frame * 0.2 + 1.57 );
      if( x2 > x1 )
      u8g2.drawLine(x1, 40, x2, 40);
    #elif
      char c = '|';
      switch(frame % 4){
        case 0:c='|';break;case 1:c='/';break;
        case 2:c='-';break;case 3:c='\\';break;
      }u8g2.drawStr(90, 26, c);
    #endif
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

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_menu()");
    #endif

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
    u8g2.drawUTF8(3 ,4 , MENU->name );//画菜单名字
    u8g2.drawFrame(0, 1, 128, 16); //画空心矩形

    for(int i=0; i<4; i++){
      if( i < MENU->length ){
        u8g2.drawUTF8(4 ,18+12*i , MENU->menu_list[ i + view_line ].name );//打印选项名字
      }
    } 
    width = u8g2.getUTF8Width( MENU->menu_list[ MENU->cursor ].name) +7;//打印光标
    u8g2.drawBox( 0 , ( MENU->cursor - view_line )*12 +16 , width , 13 ); 
    u8g2.drawBox( 127 , ( MENU->cursor / 1.0 / ( MENU->length -1 ) )*40+17 , 1 , 7 ); //打印位置指示器

    return;
}



/*
    函数名字：u8g2_print_list
    函数功能：打印可以调整观看位置的列表
    返回值：没有
    参数：
        INFO
        类型：display_info*
        作用：传递要打印的列表信息
*///
void u8g2_print_list( display_info *INFO ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_list()");
    #endif

    uint8_t list_view_line = INFO->data.list_t->cursor;//列表显示在屏幕上的第一行对应光标行数

    for(int i=0;i<6;i++){//屏幕上一共可以完整的显示五行
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

/*
    函数名字：u8g2_print_BMP
    函数功能：打印image_data类型图片，支持简单地叠加处理（是否涂黑背景）
    返回值：没有
    参数：
        INFO
        类型：display_info*
        作用：传递要打印的图片信息
*/
void u8g2_print_BMP( display_info* INFO ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_BMP()");
    #endif

    u8g2.setDrawColor(1);
    
    image* IMAGE = INFO->data.img;
    uint8_t bmp_data = 0;
    uint8_t x_cursor = 0;
    uint8_t y_cursor = 0;
    uint8_t draw_x = 0 ;
    uint8_t draw_y = 0 ;
    uint8_t bit = 0 ;
    const uint8_t width =  IMAGE->width;
    const uint8_t height = IMAGE->height;
    const uint8_t x = INFO->x;
    const uint8_t y = INFO->y;
    const uint8_t bytes_per_line = (width + 7) / 8;//每行包含字节数

    //涂黑背景
    if( IMAGE->if_black_background ){
        u8g2.setDrawColor(0);
        u8g2.drawBox(INFO->x, INFO->y, 
            width,
            height
        );
    }
    
    u8g2.setDrawColor(1);

    for( y_cursor=0;  y_cursor < height      ; y_cursor++ ){
    for( x_cursor=0;  x_cursor<bytes_per_line; x_cursor++ ){
    bmp_data = IMAGE->image_data[y_cursor*bytes_per_line +x_cursor];//记录对应数据 

    for(bit=0;bit<8;bit++){//打印记录数据
        draw_x = x + 8*x_cursor +bit;
        draw_y = y + y_cursor ;
        if( draw_x < 128 && draw_y < 64 ){//屏幕边界检查
        if( 8*x_cursor +bit < width ){//图像边界检查
        if( bmp_data & ( 0x80 >> bit ) ){
          u8g2.drawPixel( draw_x , draw_y ); // 在xy位置绘制一个像素.
    }}}}}}u8g2.setDrawColor(2);
}