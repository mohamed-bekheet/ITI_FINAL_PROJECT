/*
 * SPI_interfce.h
 *
 *  Created on: Sep 2, 2022
 *      Author: moham
 */

#ifndef INC_SPI_INTERFCE_H_
#define INC_SPI_INTERFCE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_private.h"

#define SPI_1  SPI_1_ADDR
#define SPI_2  SPI_2_ADDR

#define SPI1_DATA_ADDR_DMA  (SPI_1->DR)

//*SPI1.CR2 :::::: *(0X4001300+04)
typedef enum{
    BR_2,
    BR_4,
    BR_8,
    BR_16,
    BR_32,
    BR_64,
    BR_128,
    BR_256,
}SPI_BAUDRATE;

typedef enum
{
    FRAM_8BIT,
    FRAM_16BIT,
} SPI_DATA_FRAME_FORMAT;
typedef enum
{
    DAOR_MSB_FIRST,
    DAOR_LSB_FIRST,
} SPI_DATA_ORDER;

typedef enum
{   
    OPER_SLAVE,
    OPER_MASTER,
} SPI_OPERATION;

typedef enum{
    COMM_FULLDUPLEX,
    COMM_HALFDUPLEX,
    //COM_CONTI,
    COMM_DMA,
}SPI_COMMUNICATION;

/*
The idle state of SCK must correspond to the polarity selected in the SPI_CR1 register (by 
pulling up SCK if CPOL=1 or pulling down SCK if CPOL=0)
*/

/*
If 
CPOL is reset, the SCK pin has a low-level idle state. If CPOL is set, the SCK pin has a 
high-level idle state.
*/
typedef enum
{
    POL_SCK_LOW_LEVEL,//The first clock transition is the first data capture edge
    POL_SCK_HIGH_LEVEL,//The second clock transition is the first data capture edge
} SPI_POLARITY;
/*
If the CPHA (clock phase) bit is set, the second edge on the SCK pin (falling edge if the 
CPOL bit is reset, rising edge if the CPOL bit is set) is the MSBit capture strobe
*/
typedef enum
{  
    PHA_RISING_TRIG,//TRAILING
    PHA_FALLING_TRIG,//LEADING

} SPI_PHASE;

typedef enum
{  
    NSS_INPUT_SW_MODE_DISABLE,
    NSS_OUTPUT_MODE_ENABLE,

} SPI_NSS_MODE;//SLAVE SELECT ENABLE USING IR BBY SW



typedef struct
{

    SPI_REG* moduleReg;
    SPI_OPERATION operationMode;
    SPI_COMMUNICATION commUMode;
    SPI_BAUDRATE baudrate;
    SPI_POLARITY polarity;
    SPI_PHASE phase;
    SPI_DATA_FRAME_FORMAT frameFormate;
    SPI_DATA_ORDER dataOrder;
    SPI_NSS_MODE nssMode;
    u8 MISO_PORT;
    u8 MISO_PIN;
    u8 MOSI_PORT;
    u8 MOSI_PIN;
    u8 SCK_PORT;
    u8 SCK_PIN;
    u8 NSS_PORT;
    u8 NSS_PIN;

}SPI_interfce;

//WILL BE CALLED INSIDE SPI_INIT
//void SPI_GPIO_Init(SPI_interfce module);
 
void SPI_Init(SPI_interfce *module);

u8 SPI_handleDATAFrame(SPI_interfce *module,u8 *data,u8 lenght);



#endif /* INC_SPI_INTERFCE_H_ */
