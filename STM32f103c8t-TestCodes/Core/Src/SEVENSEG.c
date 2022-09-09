#include "SEVENSEG_interface.h"


//7seg pins ABCDEFG + enable
//SS::SEVEN SEGMENT
void SS_voidWriteDigit(SevenSeg_pins_t *sevenSegment_pins, SEVENSEG_DIGIT_e digit) {

	if(sevenSegment_pins->activeHigh){
		GPIO_SetPinArrayValue(sevenSegment_pins->SevenSegArr, 7,(u32)digit);
	}
	else{//active Low
		GPIO_SetPinArrayValue(sevenSegment_pins->SevenSegArr, 7,(u32)~digit);
	}
}

void SS_voidEnable(SevenSeg_pins_t* sevenSegment_pins, bool enable){
	GPIO_voidSetPinValue(sevenSegment_pins->enablePin.port,sevenSegment_pins->enablePin.pin_number, enable);
}
