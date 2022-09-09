/*
 * SPI_program.c
 *
 *  Created on: Sep 2, 2022
 *      Author: moham
 */


#include "SPI_interfce.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"





//WILL BE CALLED INSIDE SPI_INIT
//void SPI_GPIO_Init(SPI_interfce module);
 
void SPI_Init(SPI_interfce *module){
    RCC_voidPeripheralClockEnable(RCC_APB2,RCC_SPI1);
    RCC_voidPeripheralClockEnable(RCC_APB2,RCC_GPIOA);

    switch (module->operationMode)
    {
    case  OPER_MASTER :
        //GPIO PIN CONFIGURATIONS
        GPIO_voidSetPinMode(module->SCK_PORT ,module->SCK_PIN,GPIO_PIN_MODE_AF_PP_50MHZ_OUTPUT);//SCK
        GPIO_voidSetPinMode(module->MOSI_PORT,module->MOSI_PIN,GPIO_PIN_MODE_AF_PP_50MHZ_OUTPUT);//MOSI
        GPIO_voidSetPinMode(module->MISO_PORT,module->MISO_PIN,GPIO_PIN_MODE_FLOATING_INPUT);    //MISO
        GPIO_voidSetPinMode(module->NSS_PORT ,module->NSS_PIN,GPIO_PIN_MODE_AF_PP_50MHZ_OUTPUT);//NSS
        
        //FULLDUPLEX
        module->moduleReg->CR1 = 0;
        WRITE_BITS(module->moduleReg->CR1,module->phase,0);
        WRITE_BITS(module->moduleReg->CR1,module->polarity,1);
        WRITE_BITS(module->moduleReg->CR1,module->operationMode,2);//MASTER ENABLE
        WRITE_BITS(module->moduleReg->CR1,module->dataOrder,7);
        CLR_BIT(module->moduleReg->CR1,9);//SOFTWARE SLAVE MANAGMENT
        WRITE_BITS(module->moduleReg->CR1,module->frameFormate,11);
        module->moduleReg->CR2 = 0;
        module->moduleReg-> CR1 &= 0xFFC7 ;
        WRITE_BITS(module->moduleReg->CR1,module->baudrate,3);

        SET_BIT( module->moduleReg->CR1 , 6 );
        //SET_BIT(module->moduleReg->CR1,8);
        //SET_BIT(module->moduleReg->CR1,15);
        //CLR_BIT(module->moduleReg->CR1,10);//FULL DUPLEX


        //WRITE_BITS(module->moduleReg->CR2,module->nssMode,2);

        break;
    
    case  OPER_SLAVE :
        /* code */
        break;
    
    default:
        break;
    }
}

u8 SPI_handleDATAFrame(SPI_interfce *module,u8 *data,u8 lenght){
    //The transmit sequence begins when a byte is written in the Tx Buffer
    //CAN SEND 8BIT OR 16 BIT DATA BASED ON SPI_DATA_FRAME_FORMAT VALUE
	u8 RXdata =0;
    SET_BIT(module->moduleReg->CR1,6);//ENABLE SPI
    /*
    int i = 0;
    while(i<lenght){
    	//while (!GET_BIT(module->moduleReg->SR,1));
    	module->moduleReg->DR = (u16)data[i];
    	while (!GET_BIT(module->moduleReg->SR,1));
    	while (GET_BIT(module->moduleReg->SR,7));
        i++;
    }

    RXdata = (u8)(module->moduleReg->DR);
    //CLEAR OVERRUN
    u8 TEMP = module->moduleReg->DR;
    TEMP = module->moduleReg->SR;
    CLR_BIT(module->moduleReg->CR1,6);//DISABLE SPI AND NSS RETURN HIGH
    
   
*/
    module->moduleReg-> DR = data[0];

	while ( GET_BIT( module->moduleReg-> SR , 7) == 1 );

	return (u8) module->moduleReg-> DR ;
    return RXdata;
}
