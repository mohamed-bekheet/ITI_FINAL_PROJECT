/*
 * USART_interface.h
 *
 *  Created on: Aug 21, 2022
 *      Author: mohamed modustafa
 */

#ifndef INCLUDE_USART_INTERFACE_H_
#define INCLUDE_USART_INTERFACE_H_

#include "USART_private.h"

#define USART_1					USART1_ADDR
#define USART_2					USART2_ADDR
#define USART_3					USART3_ADDR

#define _8_DATA_BITS			0
#define _9_DATA_BITS			1

#define _1_STOP_BIT				0b00
#define _0_5_STOP_BITS			0b01
#define _2_STOP_BITS			0b10
#define _1_5_STOP_BITS			0b11

#define USART1_DR_ADDR_DMA    (USART1_ADDR->DR)
// Public functions

/*
 * function to Initialize the USARTs
 */
void USART_voidInit(USART_t *UsartREG,u32 Copy_u16BaudRate);
/*
 * function to send a byte
 */
void USART_voidSendByte(USART_t *UsartREG, u16 Copy_u8Value);

/*
 * function to receive a byte
 */
//void USART_voidResByte(USART_t *UsartREG, u16 Copy_u8Value);

void USART_voidSendArray(USART_t *UsartREG,u16 Copy_u8NumElements,u16 ptr_u8Array[]);


void USART_voidSendString(USART_t *UsartREG,char ptr_u8Array[]);


void USART_voidEnableInteruptReceiver(USART_t *UsartREG);

char USART_u8RecieveByte(USART_t *UsartREG);
/*

u8 MUSART1_u8RecCharSynch ( void ){

	u8  LOC_u8Data  = 0 ;
	u32 LOC_TimeOut = 0 ;

	CLR_BIT ( MUSART1 -> SR, 5);

	while( ( GET_BIT ( MUSART1 -> SR, 5) == 0 ) && ( LOC_TimeOut < THRESHOLD_VALUE ) )
	{
		LOC_TimeOut++;
	}

	if( LOC_TimeOut == THRESHOLD_VALUE )
	{
		LOC_u8Data = 255;
	}
	else
	{

		LOC_u8Data = MUSART1 -> DR;
	}

	return LOC_u8Data;

}*/
#endif /* INCLUDE_USART_INTERFACE_H_ */
