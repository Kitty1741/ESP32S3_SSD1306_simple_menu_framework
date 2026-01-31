#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "2_engine/engine_struct.h"
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
    函数名字：u8g2_print_title
    函数功能：打印title
    返回值：没有
    参数：
        name
        类型：const char*
        作用：传递打印数据
*///
inline void u8g2_print_title( const char* title ){

    //显示到U8G2
    u8g2.drawUTF8(3 ,4 , title );//画菜单名字
    u8g2.drawFrame(0, 1, 128, 16); //画空心矩形
}


/*
    函数名字：u8g2_print_ui_node_once
    函数功能：打印链表的一个节点
    返回值：没有
    参数：
        node
        类型：m_ui_node_t*
        作用：传递打印数据
*///
inline void u8g2_print_ui_node_once(m_ui_node_t* node){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_ui_node_once()");
    #endif

    switch( node->type ){
        case UI_TYPE_NONE :break;// 不显示
        case UI_TYPE_LOADING:{
            u8g2_print_LOADING();
        }break;// 加载中
        case UI_TYPE_MENU   :{
            u8g2_print_menu( node );
        }break;// 菜单显示
        case UI_TYPE_LIST   :{
            u8g2_print_list( node );
        }break;// 文字列表
        case UI_TYPE_IMAGE  :{
            u8g2_print_image( node );
        }break;// 图片显示
        case UI_TYPE_SETTING:{
            u8g2_print_setting( node );
        }break;// 设置界面显示
    }
}

/*
    函数名字：u8g2_print_ui_node
    函数功能：打印一大根链表
    返回值：没有
    参数：
        node
        类型：m_ui_node_t*
        作用：告诉函数打印链表的起点
*///
void u8g2_print_ui_node( m_ui_node_t* node ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_ui_node()");
    #endif

    u8g2.clearBuffer();    // 清Buffer缓冲区的数

    while( node != NULL ){//如果当前指针不是空指针
        u8g2_print_ui_node_once( node );//每打印一次
        node = node->next;//指针向后移位
    }

    u8g2.sendBuffer();    // 将Buffer帧缓冲区的内容发送到显示器,发送刷新消息
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
    m_image_t* WORD_IMG = &mystery_chinese_word_loading;
    m_ui_node_t WORD;
    
    //设置显示文字  
    WORD.type = UI_TYPE_IMAGE; 
    WORD.x = 41;  WORD.y = 23;
    WORD.data.image = WORD_IMG;
    u8g2_print_image( &WORD );//不要引入新字体，吃我内存
    
    //显示动画
    vTaskDelay( 20 );
    frame < 0xffff ? frame++ : frame = 0;
    
    float_t x1,x2;
    if( frame % 30 < 15 ){
      x2 = 88 + 48 * sin( frame % 15 * PI/2/15 + 1.5*PI );
      x1 = 40;
    }
    else{
      x1 = 40 + 48 * sin( frame % 15 * PI/2/15 );
      x2 = 88;
    }
    if( x2 > x1 )
    u8g2.drawLine(x1, 40, x2, 40);

}


/*
    函数名字：u8g2_print_menu
    函数功能：打印菜单
    返回值：没有
    参数：
        node
        类型：m_ui_node_t*
        作用：告诉函数应该打印哪个菜单
*///
void u8g2_print_menu( m_ui_node_t* node ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_menu()");
    #endif

    uint8_t view_line = 0;//显示的第一行
    uint8_t width = 0;//打印字符的宽度(用来设置光标)
    m_menu_t* menu = node->data.menu;

    //通过光标计算屏幕所在行
    if( menu->length < 4 ){
      view_line = 0;
    }else{
      menu->cursor == 0                 ? view_line = 0 :
      menu->cursor == menu->length -2   ? view_line = menu->cursor -2 :
      menu->cursor == menu->length -1   ? view_line = menu->cursor -3 :
      /*default*/view_line = menu->cursor -1;
    }

    //显示到U8G2
    u8g2_print_title( menu->name );

    for(int i=0; i<4; i++){
      if( i < menu->length ){
        u8g2.drawUTF8(4 ,18+12*i , menu->items[ i + view_line ].name );//打印选项名字
      }
    } 
    width = u8g2.getUTF8Width( menu->items[ menu->cursor ].name) +7;//打印光标
    u8g2.drawBox( 0 , ( menu->cursor - view_line )*12 +16 , width , 13 ); 
    u8g2.drawBox( 127 , ( menu->cursor / 1.0 / ( menu->length -1 ) )*40+17 , 1 , 7 ); //打印位置指示器

    return;
}



/*
    函数名字：u8g2_print_list
    函数功能：打印列表
    返回值：没有
    参数：
        node
        类型：m_ui_node_t*
        作用：传递要打印的列表信息
*///
void u8g2_print_list( m_ui_node_t* node ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_list()");
    #endif

    m_list_t* list = node->data.list;
    uint16_t list_view_line = list->cursor;//列表显示在屏幕上的第一行对应光标行数

    for(int i=0;i<6;i++){
        if( i + list_view_line >= list->length ){
            return;
        }//防空指针
        u8g2.drawUTF8(//打印对应行内容
            /*起始横坐标*/node->x ,
            /*起始纵坐标*/node->y + 12*i,
            /* 打印内容 */list->items[ i + list_view_line ]
        );
    }
}

/*
    函数名字：u8g2_print_image
    函数功能：打印m_image_t类型图片，支持简单地叠加处理（是否涂黑背景）
    返回值：没有
    参数：
        node
        类型：m_ui_node_t*
        作用：传递要打印的图片信息
*/
void u8g2_print_image( m_ui_node_t* node ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_image()");
    #endif

    u8g2.setDrawColor(1);
    
    m_image_t* IMAGE = node->data.image;
    uint8_t bmp_data = 0;
    uint8_t x_cursor = 0;
    uint8_t y_cursor = 0;
    uint8_t draw_x = 0 ;
    uint8_t draw_y = 0 ;
    uint8_t bit = 0 ;
    const uint8_t width =  IMAGE->width;
    const uint8_t height = IMAGE->height;
    const uint8_t x = node->x;
    const uint8_t y = node->y;
    const uint8_t bytes_per_line = (width + 7) / 8;//每行包含字节数

    //涂黑背景
    if( IMAGE->if_black_background ){
        u8g2.setDrawColor(0);
        u8g2.drawBox(x, y, 
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

/*
    函数名字：u8g2_print_setting
    函数功能：打印设置界面
    返回值：没有
    参数：
        node
        类型：m_ui_node_t*
        作用：传递要打印的设置参数
*///
void u8g2_print_setting( m_ui_node_t* node ){

    #if( IF_DEBUG_3 ==true )//debug
    Serial.println("u8g2_print_setting()");
    #endif

    m_setting_t* set = node->data.setting;
    char str[24];
    double_t value = 0;

    //打印
    u8g2_print_title( set->name );//打印标题
    switch( set->MODE ){//设置打印内容
        case SETTING_MODE_DOUBLE:
            value = *(double_t*)set->object;
            sprintf( str , "value -> %.6g", *(double_t*)set->object );
        break;
        case SETTING_MODE_CHAR:
            value = *(int8_t*)set->object;
            sprintf( str , "char -> %c", *(int8_t*)set->object );
            char char_value_str[7];//显示char值
            sprintf( char_value_str , "0x%x" , *(uint8_t*)set->object );
            u8g2.drawUTF8( 88 , 24 , char_value_str );//打印内容
        break;
        case SETTING_MODE_INT:
            value = *(int64_t*)set->object;
            sprintf( str , "value -> %d", *(int64_t*)set->object );
        break;
    }
    u8g2.drawUTF8( 8 , 24 , str );//打印内容
    u8g2.drawUTF8( 8 , 38 , "min" );//打印UI
    u8g2.drawUTF8( 100 , 38 , "max" );
    u8g2.drawBox( 28 , 42 , (value - set->min)/(set->max - set->min) *66 , 3 );
    
    u8g2.drawUTF8( 4 , 51 , "2/4.确认并退出" );
}