/*
 * DMA_interface.h
 *
 *  Created on: Sep 9, 2022
 *      Author: mohamed moustafa aly
 */

#ifndef INC_DMA_INTERFACE_H_
#define INC_DMA_INTERFACE_H_
#include"STD_TYPES.h"
#include "DMA_private.h"

#define DMA_1 DMA_REG


typedef enum{
    PRIO_LOW,
    PRIO_MEDIUM,
    PRIO_HIGH,
    PRIO_VERYHIGH,
}DMA_PRIORITY_e;

typedef enum{
    MEMS_8BIT,
    MEMS_16BIT,
    MEMS_32BIT,
}DMA_MEMORYSIZE_e;

typedef enum{
    PERS_8BIT,
    PERS_16BIT,
    PERS_32BIT,
}DMA_PERIPHERALSIZE_e;

typedef enum{
    DADIR_CIRCULAR,
    DADIR_MEM2MEM,
}DMA_DATADIR_MODE_e;

void DMA_RESRTREG(DMA_CHANNEL_t *channel);

void DMA_SetMemoryAddr(DMA_CHANNEL_t *channel,u32 *addr);

void DMA_SetPeripheralAddr(DMA_CHANNEL_t *channel,u32 *addr);



void DMA_ConfigTotalNumberData(DMA_CHANNEL_t *channel,u16 datanum);

void DMA_ConfigMemorySize(DMA_CHANNEL_t *channel,DMA_MEMORYSIZE_e memorysize);

void DMA_ConfigPeripheralSize(DMA_CHANNEL_t *channel,DMA_PERIPHERALSIZE_e peripheralsize);

void DMA_ConfigPriority(DMA_CHANNEL_t *channel,DMA_PRIORITY_e priority);

void DMA_EnableMEMInc(DMA_CHANNEL_t *channel);

void DMA_EnablePerphInc(DMA_CHANNEL_t *channel);


void DMA_ConfigDataTransDirection(DMA_CHANNEL_t *channel,DMA_DATADIR_MODE_e dataDirMode);

u8 DMA_GetFlag(DMA_CHANNEL_t *channel,u8 bit);

void DMA_CLRFlag(DMA_CHANNEL_t *channel,u8 bit);


void DMA_EnableHalfTxInterrupt(DMA_CHANNEL_t *channel);

void DMA_EnableEndTxInterrupt(DMA_CHANNEL_t *channel);

void DMA_Enablechannel(DMA_CHANNEL_t *channel);

void DMA_SetCallBackChannel5( void ( *Ptr ) ( void ) );

#endif /* INC_DMA_INTERFACE_H_ */
