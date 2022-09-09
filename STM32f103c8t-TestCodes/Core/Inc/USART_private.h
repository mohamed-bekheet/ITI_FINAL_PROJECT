/*
 * USART_private.h
 *
 *  Created on: Aug 21, 2022
 *      Author: mohamed moustafa aly
 */

#ifndef INCLUDE_USART_PRIVATE_H_
#define INCLUDE_USART_PRIVATE_H_


typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_t;

// USART1 base address: 0x40013800
#define USART1_ADDR							((volatile USART_t*) 0x40013800)
// USART2 base address: 0x40004400
#define USART2_ADDR							((volatile USART_t*) 0x40004400)
// USART3 base address: 0x40004800
#define USART3_ADDR							((volatile USART_t*) 0x40004800)




#endif /* INCLUDE_USART_PRIVATE_H_ */
