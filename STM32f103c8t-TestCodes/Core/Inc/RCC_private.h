/*
 * RCC_private.h
 *
 *  Created on: Aug 3, 2022
 *      Author: mohamed moustafa aly
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_


#define RCC_BASE_ADDRESS	0x40021000

#define RCC_CR				*((volatile u32*) (RCC_BASE_ADDRESS+0x00))
#define RCC_CFGR			*((volatile u32*) (RCC_BASE_ADDRESS+0x04))
#define RCC_CIR				*((volatile u32*) (RCC_BASE_ADDRESS+0x08))
#define RCC_APB2RSTR		*((volatile u32*) (RCC_BASE_ADDRESS+0x0C))
#define RCC_APB1RSTR		*((volatile u32*) (RCC_BASE_ADDRESS+0x10))
#define RCC_AHBENR			*((volatile u32*) (RCC_BASE_ADDRESS+0x14))
#define RCC_APB2ENR			*((volatile u32*) (RCC_BASE_ADDRESS+0x18))
#define RCC_APB1ENR			*((volatile u32*) (RCC_BASE_ADDRESS+0x1C))
#define RCC_BDCR			*((volatile u32*) (RCC_BASE_ADDRESS+0x20))
#define RCC_CSR				*((volatile u32*) (RCC_BASE_ADDRESS+0x24))



#endif /* RCC_PRIVATE_H_ */
