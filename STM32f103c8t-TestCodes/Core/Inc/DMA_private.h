/*
 * DMA_private.h
 *
 *  Created on: Sep 9, 2022
 *      Author: moham
 */

#ifndef INC_DMA_PRIVATE_H_
#define INC_DMA_PRIVATE_H_

#include"STD_TYPES.h"

typedef struct 
{
    vu32 CCR;
    vu32 CNDTR;
    vu32 CPAR;
    vu32 CMAR;
    vu32 reserved;
}DMA_CHANNEL_t;

typedef struct 
{
    vu32 ISR;
    vu32 IFCR;
    DMA_CHANNEL_t CH1;
    DMA_CHANNEL_t CH2;
    DMA_CHANNEL_t CH3;
    DMA_CHANNEL_t CH4;
    DMA_CHANNEL_t CH5;
    DMA_CHANNEL_t CH6;
    DMA_CHANNEL_t CH7;
}DMA_MODULE_t;

//0X40020000
#define DMA_REG  ((DMA_MODULE_t*)(0X40020000))
#endif /* INC_DMA_PRIVATE_H_ */
