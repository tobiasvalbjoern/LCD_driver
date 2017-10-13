#ifndef LCD_H
#define LCD_H

//Control pins and ports.
// RS pin 5
#define RS_PORT 1
#define RS_PIN 24

// R/W pin 19
#define RW_PORT 1
#define RW_PIN 30

// Enable Configure pin 20
#define ENABLE_PORT 1
#define ENABLE_PIN 31


//Data pins and ports

//Pin 23
#define DATA0_PORT 2
#define DATA0_PIN 10

//Pin 24
#define DATA1_PORT 1
#define DATA1_PIN 12

//Pin 25
#define DATA2_PORT 1
#define DATA2_PIN 11

//Pin 26
#define DATA3_PORT 1
#define DATA3_PIN 7

//Pin 27
#define DATA4_PORT 1
#define DATA4_PIN 6

//Pin 28
#define DATA5_PORT 1
#define DATA5_PIN 5

//Pin 29
#define DATA6_PORT 1
#define DATA6_PIN 3

//Pin 30
#define DATA7_PORT 1
#define DATA7_PIN 2

//0b00110000
#define FUNCTION_MODE 	0x30

//0b00001111
#define DISPLAY_MODE 	0xF

//0b00000001
#define CLEAR_MODE		0x1		


void LCD_init(void); //function to initialise the LCD
void char_to_LCD(char value); //function to display characters
void string_to_LCD(char* string); //function to display a string

#endif