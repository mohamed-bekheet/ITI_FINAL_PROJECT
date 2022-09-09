/*
 * SPI_private.h
 *
 *  Created on: Sep 2, 2022
 *      Author: moham
 */

#ifndef INC_SPI_PRIVATE_H_
#define INC_SPI_PRIVATE_H_

#include "STD_TYPES.h"

 typedef struct  {
    vu32 CR1;
    vu32 CR2;
    vu32 SR;
    vu32 DR;
    vu32 CRCPR;
    vu32 RXCRCR;
    vu32 TXCRCCR;
    vu32 I2SCFGR;
    vu32 I2SPR;
}SPI_REG;

#define SPI_1_ADDR   (((volatile SPI_REG*)(0x40013000)))
#define SPI_2_ADDR   (((volatile SPI_REG*)(0x40003800)))

#endif /* INC_SPI_PRIVATE_H_ */
