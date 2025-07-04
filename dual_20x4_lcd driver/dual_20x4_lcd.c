/*
 * dual_lcd_parallel.c
 *
 * Created for controlling two 20x4 LCDs independently
 * with separate data and control lines.
 *
 * Author: muhammadali
 */

#include "main.h"

/* ---------------- LCD 1 Pin Mapping ---------------- */
#define LCD1_RS_PORT GPIOC
#define LCD1_RS_PIN  GPIO_PIN_2
#define LCD1_EN_PORT GPIOC
#define LCD1_EN_PIN  GPIO_PIN_3
#define LCD1_D4_PORT GPIOA
#define LCD1_D4_PIN  GPIO_PIN_1
#define LCD1_D5_PORT GPIOA
#define LCD1_D5_PIN  GPIO_PIN_5
#define LCD1_D6_PORT GPIOA
#define LCD1_D6_PIN  GPIO_PIN_7
#define LCD1_D7_PORT GPIOC
#define LCD1_D7_PIN  GPIO_PIN_5

/* ---------------- LCD 2 Pin Mapping ---------------- */
#define LCD2_RS_PORT GPIOD
#define LCD2_RS_PIN  GPIO_PIN_3
#define LCD2_EN_PORT GPIOC
#define LCD2_EN_PIN  GPIO_PIN_1
#define LCD2_D4_PORT GPIOB
#define LCD2_D4_PIN  GPIO_PIN_9
#define LCD2_D5_PORT GPIOB
#define LCD2_D5_PIN  GPIO_PIN_4
#define LCD2_D6_PORT GPIOB
#define LCD2_D6_PIN  GPIO_PIN_5
#define LCD2_D7_PORT GPIOB
#define LCD2_D7_PIN  GPIO_PIN_6

/* ---------------- Helper Macros ---------------- */
#define RS_HIGH(port, pin) HAL_GPIO_WritePin((port), (pin), GPIO_PIN_SET)
#define RS_LOW(port, pin)  HAL_GPIO_WritePin((port), (pin), GPIO_PIN_RESET)
#define EN_HIGH(port, pin) HAL_GPIO_WritePin((port), (pin), GPIO_PIN_SET)
#define EN_LOW(port, pin)  HAL_GPIO_WritePin((port), (pin), GPIO_PIN_RESET)

/* ---------------- Core Functions ---------------- */
void lcd_send_nibble(GPIO_TypeDef* d4_port, uint16_t d4_pin,
                     GPIO_TypeDef* d5_port, uint16_t d5_pin,
                     GPIO_TypeDef* d6_port, uint16_t d6_pin,
                     GPIO_TypeDef* d7_port, uint16_t d7_pin,
                     uint8_t nibble,
                     GPIO_TypeDef* en_port, uint16_t en_pin) {
    HAL_GPIO_WritePin(d4_port, d4_pin, (nibble >> 0) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(d5_port, d5_pin, (nibble >> 1) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(d6_port, d6_pin, (nibble >> 2) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(d7_port, d7_pin, (nibble >> 3) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);

    EN_HIGH(en_port, en_pin);
    HAL_Delay(1);
    EN_LOW(en_port, en_pin);
    HAL_Delay(1);
}

void lcd_send_cmd(uint8_t cmd, int lcd) {

    if (lcd == 1) {
        RS_LOW(LCD1_RS_PORT, LCD1_RS_PIN);
        lcd_send_nibble(LCD1_D4_PORT, LCD1_D4_PIN,
                        LCD1_D5_PORT, LCD1_D5_PIN,
                        LCD1_D6_PORT, LCD1_D6_PIN,
                        LCD1_D7_PORT, LCD1_D7_PIN,
                        cmd >> 4,
                        LCD1_EN_PORT, LCD1_EN_PIN);
        lcd_send_nibble(LCD1_D4_PORT, LCD1_D4_PIN,
                        LCD1_D5_PORT, LCD1_D5_PIN,
                        LCD1_D6_PORT, LCD1_D6_PIN,
                        LCD1_D7_PORT, LCD1_D7_PIN,
                        cmd & 0x0F,
                        LCD1_EN_PORT, LCD1_EN_PIN);
    }
    else if (lcd == 2) {
        RS_LOW(LCD2_RS_PORT, LCD2_RS_PIN);
        lcd_send_nibble(LCD2_D4_PORT, LCD2_D4_PIN,
                        LCD2_D5_PORT, LCD2_D5_PIN,
                        LCD2_D6_PORT, LCD2_D6_PIN,
                        LCD2_D7_PORT, LCD2_D7_PIN,
                        cmd >> 4,
                        LCD2_EN_PORT, LCD2_EN_PIN);
        lcd_send_nibble(LCD2_D4_PORT, LCD2_D4_PIN,
                        LCD2_D5_PORT, LCD2_D5_PIN,
                        LCD2_D6_PORT, LCD2_D6_PIN,
                        LCD2_D7_PORT, LCD2_D7_PIN,
                        cmd & 0x0F,
                        LCD2_EN_PORT, LCD2_EN_PIN);
    }
    HAL_Delay(2);
}

void lcd_send_data(uint8_t data, int lcd) {

    if (lcd == 1) {
        RS_HIGH(LCD1_RS_PORT, LCD1_RS_PIN);
        lcd_send_nibble(LCD1_D4_PORT, LCD1_D4_PIN,
                        LCD1_D5_PORT, LCD1_D5_PIN,
                        LCD1_D6_PORT, LCD1_D6_PIN,
                        LCD1_D7_PORT, LCD1_D7_PIN,
                        data >> 4,
                        LCD1_EN_PORT, LCD1_EN_PIN);
        lcd_send_nibble(LCD1_D4_PORT, LCD1_D4_PIN,
                        LCD1_D5_PORT, LCD1_D5_PIN,
                        LCD1_D6_PORT, LCD1_D6_PIN,
                        LCD1_D7_PORT, LCD1_D7_PIN,
                        data & 0x0F,
                        LCD1_EN_PORT, LCD1_EN_PIN);
    }
    else if (lcd == 2) {
        RS_HIGH(LCD2_RS_PORT, LCD2_RS_PIN);
        lcd_send_nibble(LCD2_D4_PORT, LCD2_D4_PIN,
                        LCD2_D5_PORT, LCD2_D5_PIN,
                        LCD2_D6_PORT, LCD2_D6_PIN,
                        LCD2_D7_PORT, LCD2_D7_PIN,
                        data >> 4,
                        LCD2_EN_PORT, LCD2_EN_PIN);
        lcd_send_nibble(LCD2_D4_PORT, LCD2_D4_PIN,
                        LCD2_D5_PORT, LCD2_D5_PIN,
                        LCD2_D6_PORT, LCD2_D6_PIN,
                        LCD2_D7_PORT, LCD2_D7_PIN,
                        data & 0x0F,
                        LCD2_EN_PORT, LCD2_EN_PIN);
    }
    HAL_Delay(2);
}

void lcd_clear(int lcd) {
    lcd_send_cmd(0x01, lcd);
    HAL_Delay(2);
}

void lcd_init(int lcd) {
    HAL_Delay(50);
    lcd_send_cmd(0x33, lcd);
    lcd_send_cmd(0x32, lcd);
    lcd_send_cmd(0x28, lcd);
    lcd_send_cmd(0x08, lcd);
    lcd_send_cmd(0x01, lcd);
    HAL_Delay(2);
    lcd_send_cmd(0x06, lcd);
    lcd_send_cmd(0x0C, lcd);
}

void Set_cursor_position(char row, char col, int lcd) {
    uint8_t base[] = {0x00, 0x40, 0x14, 0x54};
    lcd_send_cmd(0x80 | (base[row - 1] + col), lcd);
}

void lcd_send_string(char *str, int lcd) {
    while (*str) {
        lcd_send_data(*str++, lcd);
    }
}

void lcd_display_int(int num, int lcd) {
    char buffer[16];
    sprintf(buffer, "%02d", num);
    lcd_send_string(buffer, lcd);
}

void lcd_display_float(float num, int precision, int lcd) {
    char buffer[16];
    sprintf(buffer, "%.*f", precision, num);
    lcd_send_string(buffer, lcd);
}

///*
// * dual_20x4_lcd_parallel.c
// * Modified for dual 20x4 LCD support
// * Author: muhammadali
// */
//
//#include "main.h"
//#include "dual_20x4_lcd.h"
//
//// Shared Pins (D4–D7)
//#define LCD_D4_PORT GPIOA
//#define LCD_D4_PIN  GPIO_PIN_1
//#define LCD_D5_PORT GPIOA
//#define LCD_D5_PIN  GPIO_PIN_5
//#define LCD_D6_PORT GPIOA
//#define LCD_D6_PIN  GPIO_PIN_7
//#define LCD_D7_PORT GPIOC
//#define LCD_D7_PIN  GPIO_PIN_5
//
//// LCD1 Control Pins
//#define LCD1_RS_PORT GPIOC
//#define LCD1_RS_PIN  GPIO_PIN_2
//#define LCD1_EN_PORT GPIOC
//#define LCD1_EN_PIN  GPIO_PIN_3
//
//// LCD2 Control Pins
//#define LCD2_RS_PORT GPIOC
//#define LCD2_RS_PIN  GPIO_PIN_0
//#define LCD2_EN_PORT GPIOC
//#define LCD2_EN_PIN  GPIO_PIN_1
//
//static LCD_Select activeLCD = LCD1;
//
//void lcd_select(LCD_Select lcd) {
//    activeLCD = lcd;
//}
//
//void RS_HIGH() {
//    HAL_GPIO_WritePin(
//        activeLCD == LCD1 ? LCD1_RS_PORT : LCD2_RS_PORT,
//        activeLCD == LCD1 ? LCD1_RS_PIN  : LCD2_RS_PIN,
//        GPIO_PIN_SET
//    );
//}
//
//void RS_LOW() {
//    HAL_GPIO_WritePin(
//        activeLCD == LCD1 ? LCD1_RS_PORT : LCD2_RS_PORT,
//        activeLCD == LCD1 ? LCD1_RS_PIN  : LCD2_RS_PIN,
//        GPIO_PIN_RESET
//    );
//}
//
//void EN_HIGH() {
//    HAL_GPIO_WritePin(
//        activeLCD == LCD1 ? LCD1_EN_PORT : LCD2_EN_PORT,
//        activeLCD == LCD1 ? LCD1_EN_PIN  : LCD2_EN_PIN,
//        GPIO_PIN_SET
//    );
//}
//
//void EN_LOW() {
//    HAL_GPIO_WritePin(
//        activeLCD == LCD1 ? LCD1_EN_PORT : LCD2_EN_PORT,
//        activeLCD == LCD1 ? LCD1_EN_PIN  : LCD2_EN_PIN,
//        GPIO_PIN_RESET
//    );
//}
//
//void lcd_send_nibble(uint8_t nibble) {
//    HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (nibble >> 0) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (nibble >> 1) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (nibble >> 2) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (nibble >> 3) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
//
//    EN_HIGH();
//    HAL_Delay(1);
//    EN_LOW();
//    HAL_Delay(1);
//}
//
//void lcd_send_cmd(uint8_t cmd) {
//    RS_LOW();
//    lcd_send_nibble(cmd >> 4);
//    lcd_send_nibble(cmd & 0x0F);
//    HAL_Delay(2);
//}
//
//void lcd_send_data(uint8_t data) {
//    RS_HIGH();
//    lcd_send_nibble(data >> 4);
//    lcd_send_nibble(data & 0x0F);
//    HAL_Delay(2);
//}
//
//void lcd_clear(void) {
//    lcd_send_cmd(0x01);
//    HAL_Delay(2);
//}
//
//void lcd_init(void) {
//    HAL_Delay(50);
//
//    lcd_send_nibble(0x03);
//    HAL_Delay(5);
//    lcd_send_nibble(0x03);
//    HAL_Delay(1);
//    lcd_send_nibble(0x03);
//    HAL_Delay(1);
//    lcd_send_nibble(0x02);
//    HAL_Delay(1);
//
//    lcd_send_cmd(0x28);  // Function Set
//    lcd_send_cmd(0x08);  // Display Off
//    lcd_send_cmd(0x01);  // Clear Display
//    HAL_Delay(2);
//    lcd_send_cmd(0x06);  // Entry Mode
//    lcd_send_cmd(0x0C);  // Display ON, Cursor OFF
//}
//
//void Set_cursor_position(char row, char col) {
//    switch (row) {
//        case 1: lcd_send_cmd(0x80 + col); break;
//        case 2: lcd_send_cmd(0xC0 + col); break;
//        case 3: lcd_send_cmd(0x94 + col); break;
//        case 4: lcd_send_cmd(0xD4 + col); break;
//    }
//}
//
//void lcd_display_float(float num, int precision) {
//    char buffer[16];
//    sprintf(buffer, "%.*f", precision, num);
//    lcd_send_string(buffer);
//}
//
//void lcd_display_int(int num) {
//    char buffer[16];
//    sprintf(buffer, "%02d", num);
//    lcd_send_string(buffer);
//}
//
//void lcd_send_string(char *str) {
//    while (*str) {
//        lcd_send_data(*str++);
//    }
//}
