#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <global.h>
#include "internal.h"//内部模块
#include "u8g2_print.h"
#include "image.h"




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


/*
    函数名字：u8g2_print_MEM_CPU
    函数功能：打印内存和CPU占用信息
    返回值：没有
    参数：
        x
        类型：uint8_t
        作用：声明打印的x位置
        y
        类型：uint8_t
        作用：声明打印的y位置
*///
void u8g2_print_MEM_CPU(uint8_t x,uint8_t y){

    //打印图片
    display_info INFO = {
        .mode = DISPLAY_MODE_IMAGE,
        .data = {
            .img = &MEM_CPU_image
        },
        .x = x,
        .y = y,
        .next = NULL,
    };
    u8g2_print_BMP( &INFO );

    //得到CPU/MEM（还没做）
    //float MEM = getCpuUsage();
    //float CPU = getCpuUsage();


    //打印CPU/MEM/
    //u8g2.drawBox(x+INFO.data.img->width, y+1, MEM*32 , 3);
    //u8g2.drawBox(x+INFO.data.img->width, y+7, CPU*32 , 3);

}