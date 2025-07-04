/*
 * 20x4_lcd_parallel.h
 *
 *  Created on: Nov 13, 2024
 *      Author: muhammadali
 */

#ifndef INC_20X4_LCD_PARALLEL_H_
#define INC_20X4_LCD_PARALLEL_H_

#include "main.h"

typedef enum {
    LCD1 = 0,
    LCD2 = 1
} LCD_Select;

//void lcd_select(LCD_Select lcd);
void lcd_init(int lcd);
void lcd_send_cmd(uint8_t cmd,int lcd);
void lcd_send_data(uint8_t data,int lcd);
void lcd_send_string(char *str,int lcd);
void lcd_display_float(float num, int precision,int lcd);
void lcd_display_int(int num,int lcd);
void lcd_clear(int lcd);
void Set_cursor_position(char row, char col,int lcd);

#endif /* INC_20X4_LCD_PARALLEL_H_ */
