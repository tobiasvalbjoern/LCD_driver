/*
 * LCD.c
 *
 *  Created on: 11. okt. 2017
 *      Author: Test Bruger
 */
#include <time.h>
#include "LCD.h"
#include "board.h"


//MAKE DEFINES FOR ALL THE PINS AND PORTS HERE.

void delay_s(int number_of_seconds) {
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Stroing start time
	clock_t start_time = clock();

	// looping till required time is not acheived
	while (clock() < start_time + milli_seconds)
		;
}

void controlpin_output(void) {
	//Control PINS. All as output


	Chip_GPIO_SetPinDIROutput(LPC_GPIO, RS_PORT, RS_PIN);


	Chip_GPIO_SetPinDIROutput(LPC_GPIO, RW_PORT, RW_PIN);


	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ENABLE_PORT, ENABLE_PIN);

}

void datapin_output(void) {
	//Data PINS. p23-p30. All as output.

	//Configure pin 23
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA0_PORT, DATA0_PIN);

	//Configure pin 24
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA1_PORT, DATA1_PIN);

	//Configure pin 25
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA2_PORT, DATA2_PIN);

	//Configure pin 26
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA3_PORT, DATA3_PIN);

	//Configure pin 27
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA4_PORT, DATA4_PIN);

	//Configure pin 28
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA5_PORT, DATA5_PIN);

	//Configure pin 29
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA6_PORT, DATA6_PIN);

	//Configure pin 30
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA7_PORT, DATA7_PIN);

}

void command_mode(void) {
	//Set RS to 0. To send commands.
	Chip_GPIO_SetPinState(LPC_GPIO, RS_PORT, RS_PIN, false);

	//Set RW to 0. To write data.
	Chip_GPIO_SetPinState(LPC_GPIO, RW_PORT, RW_PIN, false);

	//Set enable to 0.
	Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, false);

}

void data_mode(void)
{
	//Set RS to 1. To write character data.
	Chip_GPIO_SetPinState(LPC_GPIO, RS_PORT, RS_PIN, true);
}

void setbus(char c) {
	/* set bits 0-7 according to char which can be passed as: "0bxxxxxxxx" or char*/
	Chip_GPIO_SetPinState(LPC_GPIO, DATA0_PORT, DATA0_PIN, c & 0b00000001);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA1_PORT, DATA1_PIN, c & 0b00000010);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA2_PORT, DATA2_PIN, c & 0b00000100);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA3_PORT, DATA3_PIN, c & 0b00001000);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA4_PORT, DATA4_PIN, c & 0b00010000);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA5_PORT, DATA5_PIN, c & 0b00100000);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA6_PORT, DATA6_PIN, c & 0b01000000);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA7_PORT, DATA7_PIN, c & 0b10000000);
}

void toggle_enable(void) {
	//Set enable high
	Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, true);
	delay_s(0.001);

	//Set enable low.
	Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, false);
	delay_s(0.001);
}


void lcd_write(char c) {
	setbus(c);
	//delay for 10 microseconds
	toggle_enable();
}

void function_mode(void) {
	//set the data pins to function mode

	lcd_write(FUNCTION_MODE);
	toggle_enable();
}

void display_mode(void) {

	//display mode
	//set the data pins to display mode
	lcd_write(DISPLAY_MODE);
	toggle_enable();
}

void clear_mode(void) {

	//clear display
	//set the data pins to clear mode
	lcd_write(CLEAR_MODE);
	toggle_enable();
}

//initialise LCD function
void LCD_init(void) {
	delay_s(0.02); // pause for 20 ms
	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	controlpin_output();
	datapin_output();

	command_mode();

	function_mode();
	display_mode();
	clear_mode();
}

void char_to_LCD(char value) {

	data_mode();
	lcd_write(value);
}


void string_to_LCD(char *string) {
	while (*string) {
		char_to_LCD(*string++);
	}
}
