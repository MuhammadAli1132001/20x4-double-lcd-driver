///*
// * 20x4_lcd_parallel.c
// *
// *  Created on: Nov 13, 2024
// *      Author: muhammadali
// */
//
//
//#include "main.h"
//
//// Define GPIO ports and pins
//#define LCD_RS_PORT GPIOC
//#define LCD_RS_PIN GPIO_PIN_2
//#define LCD_EN_PORT GPIOC
//#define LCD_EN_PIN GPIO_PIN_3
//#define LCD_D4_PORT GPIOA
//#define LCD_D4_PIN GPIO_PIN_1
//#define LCD_D5_PORT GPIOA
//#define LCD_D5_PIN GPIO_PIN_5
//#define LCD_D6_PORT GPIOA
//#define LCD_D6_PIN GPIO_PIN_7
//#define LCD_D7_PORT GPIOC
//#define LCD_D7_PIN GPIO_PIN_5
//
//// Define helper macros for setting and clearing bits
//#define RS_HIGH() HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET)
//#define RS_LOW()  HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET)
//#define EN_HIGH() HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET)
//#define EN_LOW()  HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET)
//
//// Function to send a 4-bit nibble
//void lcd_send_nibble(uint8_t nibble) {
//    HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (nibble >> 0) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (nibble >> 1) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (nibble >> 2) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (nibble >> 3) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//
//    // Pulse the enable pin to latch the data
//    EN_HIGH();
//    HAL_Delay(1);  // Small delay
//    EN_LOW();
//    HAL_Delay(1);  // Small delay
//}
//
//// Send a command to the LCD
//void lcd_send_cmd(uint8_t cmd) {
//    RS_LOW();
//    lcd_send_nibble(cmd >> 4);                  // Send the higher nibble
//    lcd_send_nibble(cmd & 0x0F);                                   // Send the lower nibble
//    HAL_Delay(2);                                               // Small delay for command execution
//}
//
//// Send data to the LCD
//void lcd_send_data(uint8_t data) {
//    RS_HIGH();
//    lcd_send_nibble(data >> 4);                                 // Send the higher nibble
//    lcd_send_nibble(data & 0x0F);                                 // Send the lower nibble
//    HAL_Delay(2);                                       // Small delay for data execution
//}
//
//// Clear the LCD display
//void lcd_clear(void) {
//    lcd_send_cmd(0x01);                                      // Clear display command
//    HAL_Delay(2);                                               // Extra delay for clear command
//}
//
//// Initialize the LCD in 4-bit mode
//void lcd_init(void) {
//    HAL_Delay(50);                            // Wait for LCD to power up
//
//    // 4-bit mode initialization sequence
//    lcd_send_nibble(0x03);
//    HAL_Delay(5);
//    lcd_send_nibble(0x03);
//    HAL_Delay(1);
//    lcd_send_nibble(0x03);
//    HAL_Delay(1);
//    lcd_send_nibble(0x02);                                        // Set to 4-bit mode
//    HAL_Delay(1);
//
//    // Configure LCD
//    lcd_send_cmd(0x28);                           // Function set: 4-bit mode, 2 lines, 5x8 dots
//    lcd_send_cmd(0x08);                              // Display off
//    lcd_send_cmd(0x01);                           // Clear display
//    HAL_Delay(2);
//    lcd_send_cmd(0x06);                             // Entry mode set: increment cursor, no shift
//    lcd_send_cmd(0x0C);                               // Display on, cursor off, blink off
//}
//
//void Set_cursor_position(char row, char col)
//{
//	if (row == 1){
//		lcd_send_cmd(0x80 | col);
//	}
//	else if (row == 2 ){
//		lcd_send_cmd((0x80 | 0x40) + col);
//	}
//	else if (row == 3 ){
//		lcd_send_cmd((0x80 | 0x14) + col);
//	}
//	else if (row == 4 ){
//		lcd_send_cmd((0x80 | 0x54) + col);
//	}
//}
//
//
//void lcd_display_float(float num, int precision) {
//    char buffer[16];
//    sprintf(buffer, "%.*f", precision, num);                               // Convert float to string with specified precision
//    lcd_send_string(buffer);                                            // Display the string on the LCD
//}
//
//void lcd_display_int(int num) {
//    char buffer[16];
//    sprintf(buffer, "%02d", num);                               // Convert int to string
//    lcd_send_string(buffer);                                            // Display the string on the LCD
//}
//
//void lcd_send_string(char *str) {
//    while (*str) {
//        lcd_send_data(*str++);
//    }
//}
