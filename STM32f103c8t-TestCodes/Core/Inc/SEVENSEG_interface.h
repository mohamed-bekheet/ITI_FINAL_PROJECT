#ifndef _SEVENSEGMENT_H_
#define _SEVENSEGMENT_H_


#include "GPIO_interface.h"
#include "STD_TYPES.h"
//7 segment Pins:- A0:A6
//Enable pins:- A8, A9
typedef struct {
	GPIO_PinConfig_t SevenSegArr[7]; //array of struct
	GPIO_PinConfig_t enablePin;
	bool activeHigh ;//default active high
} SevenSeg_pins_t;
/*
 * {,,,,,,};
 * */
typedef enum{
	//default active high
	//G,F,E,D,C,B,A
	zero=0b00111111,
	one=0b00000110,
	two=0b01011011,
	three=0b01001111,
	four=0b01100110,
	five=0b01101101,
	six=0b01111101,
	seven=0b00000111,
	eight=0b01111111,
	nine=0b01101111,
}SEVENSEG_DIGIT_e;

//7seg pins ABCDEFG + enable
//SS::SEVEN SEGMENT
void SS_voidWriteDigit(SevenSeg_pins_t *sevenSegment_pins, SEVENSEG_DIGIT_e digit);

void SS_voidEnable(SevenSeg_pins_t* sevenSegment_pins, bool enable);

//void SS_voidPOV();
#endif
