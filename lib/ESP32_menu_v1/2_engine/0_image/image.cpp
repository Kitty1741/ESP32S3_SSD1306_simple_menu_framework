//image.cpp
#include <Arduino.h>

#include "image_setting.h"
#include "image_struct.h"
#include "image.h"

// 定义最大图像尺寸
#define MAX_IMAGE_WIDTH 128
#define MAX_IMAGE_HEIGHT 64
#define MAX_IMAGE_BYTES ((MAX_IMAGE_WIDTH * MAX_IMAGE_HEIGHT) / 8)

//本文件装不直接参与打印的函数

/*
    函数名字：set_black_image_background
    函数功能：设置叠加处理方式（是否涂黑背景/异或显示）
    返回值：没有
    参数：
        IMAGE
        类型：m_image_t*
        作用：传递传递要打印的图片信息
        if_black
        类型：bool
        作用：设置是否黑色背景
*/
void set_black_image_background( m_image_t* IMAGE , bool if_black ){

    //涂黑背景
    IMAGE->if_black_background = if_black;
}


/*
    函数名字：rotate_image
    函数功能：顺时针旋转指向的图片90° n次(AI做的)
    返回值：没有
    参数：
        IMAGE
        类型：m_image_t*
        作用：传递要打印的图片信息
        n
        类型：uint8_t
        作用：设转动几次
*///
void rotate_image(m_image_t* IMAGE, uint8_t n) {

    __DEBUG_2("rotate_image()")

    if (IMAGE == NULL || IMAGE->image_data == NULL) return;
    
    // 计算实际旋转次数（模4运算）
    uint8_t rot_times = n % 4;
    if (rot_times == 0) return; // 不需要旋转
    
    // 静态临时缓冲区
    uint8_t temp_buffer[MAX_IMAGE_BYTES];
    
    // 当前图像尺寸
    uint8_t width = IMAGE->width;
    uint8_t height = IMAGE->height;
    
    // 计算每行字节数
    uint8_t row_bytes = (width + 7) / 8;
    
    // 根据旋转次数处理
    switch (rot_times) {
        case 1: // 旋转90°（顺时针）
        {
            // 新图像尺寸（宽高互换）
            uint8_t new_width = height;
            uint8_t new_height = width;
            uint8_t new_row_bytes = (new_width + 7) / 8;
            
            // 清空临时缓冲区
            memset(temp_buffer, 0, MAX_IMAGE_BYTES);
            
            // 遍历原图像每个像素
            for (uint8_t y = 0; y < height; y++) {
                for (uint8_t x = 0; x < width; x++) {
                    // 获取原图像像素值
                    uint8_t byte_idx = y * row_bytes + (x / 8);
                    uint8_t bit_pos = 7 - (x % 8);
                    uint8_t pixel_val = (IMAGE->image_data[byte_idx] >> bit_pos) & 0x01;
                    
                    // 计算新位置 (旋转90°顺时针)
                    uint8_t new_x = height - 1 - y;
                    uint8_t new_y = x;
                    
                    // 计算新图像中的位置
                    uint8_t new_byte_idx = new_y * new_row_bytes + (new_x / 8);
                    uint8_t new_bit_pos = 7 - (new_x % 8);
                    
                    // 设置新像素值
                    if (pixel_val) {
                        temp_buffer[new_byte_idx] |= (1 << new_bit_pos);
                    }
                }
            }
            
            // 更新图像数据
            memcpy(IMAGE->image_data, temp_buffer, new_row_bytes * new_height);
            
            // 更新图像尺寸
            IMAGE->width = new_width;
            IMAGE->height = new_height;
            break;
        }
        
        case 2: // 旋转180°
        {
            // 清空临时缓冲区
            memset(temp_buffer, 0, MAX_IMAGE_BYTES);
            
            // 遍历原图像每个像素
            for (uint8_t y = 0; y < height; y++) {
                for (uint8_t x = 0; x < width; x++) {
                    // 获取原图像像素值
                    uint8_t byte_idx = y * row_bytes + (x / 8);
                    uint8_t bit_pos = 7 - (x % 8);
                    uint8_t pixel_val = (IMAGE->image_data[byte_idx] >> bit_pos) & 0x01;
                    
                    // 计算新位置 (旋转180°)
                    uint8_t new_x = width - 1 - x;
                    uint8_t new_y = height - 1 - y;
                    
                    // 计算新图像中的位置
                    uint8_t new_byte_idx = new_y * row_bytes + (new_x / 8);
                    uint8_t new_bit_pos = 7 - (new_x % 8);
                    
                    // 设置新像素值
                    if (pixel_val) {
                        temp_buffer[new_byte_idx] |= (1 << new_bit_pos);
                    }
                }
            }
            
            // 更新图像数据
            memcpy(IMAGE->image_data, temp_buffer, row_bytes * height);
            // 尺寸不变
            break;
        }
        
        case 3: // 旋转270°（逆时针90°）
        {
            // 新图像尺寸（宽高互换）
            uint8_t new_width = height;
            uint8_t new_height = width;
            uint8_t new_row_bytes = (new_width + 7) / 8;
            
            // 清空临时缓冲区
            memset(temp_buffer, 0, MAX_IMAGE_BYTES);
            
            // 遍历原图像每个像素
            for (uint8_t y = 0; y < height; y++) {
                for (uint8_t x = 0; x < width; x++) {
                    // 获取原图像像素值
                    uint8_t byte_idx = y * row_bytes + (x / 8);
                    uint8_t bit_pos = 7 - (x % 8);
                    uint8_t pixel_val = (IMAGE->image_data[byte_idx] >> bit_pos) & 0x01;
                    
                    // 计算新位置 (旋转270°)
                    uint8_t new_x = y;
                    uint8_t new_y = width - 1 - x;
                    
                    // 计算新图像中的位置
                    uint8_t new_byte_idx = new_y * new_row_bytes + (new_x / 8);
                    uint8_t new_bit_pos = 7 - (new_x % 8);
                    
                    // 设置新像素值
                    if (pixel_val) {
                        temp_buffer[new_byte_idx] |= (1 << new_bit_pos);
                    }
                }
            }
            
            // 更新图像数据
            memcpy(IMAGE->image_data, temp_buffer, new_row_bytes * new_height);
            
            // 更新图像尺寸
            IMAGE->width = new_width;
            IMAGE->height = new_height;
            break;
        }
    }
}
