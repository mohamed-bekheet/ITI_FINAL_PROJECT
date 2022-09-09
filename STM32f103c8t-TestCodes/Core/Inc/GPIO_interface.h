/*
 * GPIO_interface.h
 *
 *  Created on: Aug 4, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_
#include"STD_TYPES.h"

// Macro definitions
#define GPIO_PORTA		0
#define GPIO_PORTB		1
#define GPIO_PORTC		2

#define GPIO_HIGH		1
#define GPIO_LOW		0

typedef struct{
	u8 port;
	u8 pin_number;
}GPIO_PinConfig_t;

#define GPIO_PULLEDUP		1
#define GPIO_PULLEDDOWN		0

// Pin modes MACROs
#define GPIO_PIN_MODE_ANALOG_INPUT		0b0000
#define GPIO_PIN_MODE_FLOATING_INPUT	0b0100
#define GPIO_PIN_MODE_PULLING_INPUT		0b1000

#define GPIO_PIN_MODE_GP_PP_2MHZ_OUTPUT		0b0010 // General purpose output push-pull::Output mode, max speed 2 MHz
#define GPIO_PIN_MODE_GP_PP_10MHZ_OUTPUT		0b0001
#define GPIO_PIN_MODE_GP_PP_50MHZ_OUTPUT		0b0011

#define GPIO_PIN_MODE_GP_OD_2MHZ_OUTPUT		0b0110// General purpose output Open-drain::Output mode, max speed 2 MHz
#define GPIO_PIN_MODE_GP_OD_10MHZ_OUTPUT		0b0101
#define GPIO_PIN_MODE_GP_OD_50MHZ_OUTPUT		0b0111

#define GPIO_PIN_MODE_AF_PP_2MHZ_OUTPUT		0b1010 // Alternate function output Push-pull::Output mode, max speed 2 MHz
#define GPIO_PIN_MODE_AF_PP_10MHZ_OUTPUT	0b1001
#define GPIO_PIN_MODE_AF_PP_50MHZ_OUTPUT	0b1011

#define GPIO_PIN_MODE_AF_OD_2MHZ_OUTPUT		0b1110
#define GPIO_PIN_MODE_AF_OD_10MHZ_OUTPUT	0b1101
#define GPIO_PIN_MODE_AF_OD_50MHZ_OUTPUT	0b1111

// Public functions


/*
 * function to set mode of a certain pin
 */
void GPIO_voidSetPinMode(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8PinMode);


/*
 * function to get input value of a certain pin
 */
u8 GPIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);


/*
 * function to set output value of a certain pin
 */
void GPIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, bool Copy_u8PinValue);

void GPIO_SetPinArrayValue(GPIO_PinConfig_t *pinArray, u8 arraylenght,u32 value);

#endif /* GPIO_INTERFACE_H_ */
