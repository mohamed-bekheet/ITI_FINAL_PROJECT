/*
 * DMA_program.c
 *
 *  Created on: Sep 9, 2022
 *      Author: moham
 */
#include "DMA_interface.h"
#include "DMA_private.h"
#include "BIT_MATH.h"

void ( *DMA_CallBackChannel3 )( void );
void ( *DMA_CallBackChannel5 )( void );

void DMA_RESRTREG(DMA_CHANNEL_t *channel){
    channel->CCR = 0;
}
//PARAMETR EXAMPLE DMA_REG->CH1
void DMA_SetMemoryAddr(DMA_CHANNEL_t *channel,u32 *addr){
    channel->CMAR = addr;
}

void DMA_SetPeripheralAddr(DMA_CHANNEL_t *channel,u32 *addr){
     channel->CPAR = addr;
}




void DMA_ConfigTotalNumberData(DMA_CHANNEL_t *channel,u16 datanum){
     channel->CNDTR = datanum;
}
void DMA_ConfigMemorySize(DMA_CHANNEL_t *channel,DMA_MEMORYSIZE_e memorysize){
     WRITE_BITS( channel->CCR , memorysize,10);
}
void DMA_ConfigPeripheralSize(DMA_CHANNEL_t *channel,DMA_PERIPHERALSIZE_e peripheralsize){
     WRITE_BITS( channel->CCR , peripheralsize,8);
}
void DMA_ConfigPriority(DMA_CHANNEL_t *channel, DMA_PRIORITY_e priority){
    WRITE_BITS( channel->CCR , priority,12 );
}

void DMA_EnableMEMInc(DMA_CHANNEL_t *channel){
        SET_BIT ( channel->CCR , 7);
}

void DMA_EnablePerphInc(DMA_CHANNEL_t *channel){
        SET_BIT ( channel->CCR , 6);
}

void DMA_ConfigDataTransDirection(DMA_CHANNEL_t *channel, DMA_DATADIR_MODE_e dataDirMode){

    if (dataDirMode == DADIR_CIRCULAR )
    {
        CLR_BIT ( channel->CCR , 14);//MEMORY MODE DISABLE
        SET_BIT ( channel->CCR , 5);//CIRCULAR MODE ENABLE
        CLR_BIT ( channel->CCR , 4);//READ FROM PERIPHERAL
        
    }
    else{//MEMORY TO MEMORY 
        CLR_BIT ( channel->CCR , 5);
        SET_BIT ( channel->CCR , 14);
        SET_BIT ( channel->CCR , 4);
    }
    
}

void DMA_EnableHalfTxInterrupt(DMA_CHANNEL_t *channel){
    SET_BIT ( channel->CCR , 2);
}

void DMA_EnableEndTxInterrupt(DMA_CHANNEL_t *channel){
    SET_BIT ( channel->CCR , 1);
    SET_BIT ( channel->CCR , 3);
}

void DMA_Enablechannel(DMA_CHANNEL_t *channel){
        SET_BIT ( channel->CCR , 0);
}
void DMA_Disablechannel(DMA_CHANNEL_t *channel){
        CLR_BIT ( channel->CCR , 0);
}

u8 DMA_GetFlag(DMA_CHANNEL_t *channel,u8 bit){
       return GET_BIT ( channel->CCR , bit);
}
void DMA_CLRFlag(DMA_CHANNEL_t *channel,u8 bit){
        CLR_BIT ( channel->CCR , bit);
}

/*----------------------------------------------------------------------------------------------------------*/
void DMA_SetCallBackChannel5( void ( *Ptr ) ( void ) ){

	DMA_CallBackChannel5 = Ptr ;

}

void DMA1_Channel5_IRQHandler(void){

	DMA_CallBackChannel5();

}
