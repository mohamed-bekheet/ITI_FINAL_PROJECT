/*
 * BIT_MATH.h
 *
 *  Created on: Aug 3, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

// 4 NORMAL MACROS [NORMAL REPLACEMENT]
#define SET_BIT(VAR,BIT)    (VAR |=(0x01<<BIT))//BRACKETS BEC I CAN USE IT INSIDE STH. (OPERATION ARRANGEMENTS) // TEXT PLACEMENT TIS IS MICRO
#define CLR_BIT(VAR,BIT)    (VAR &= (~(0x01<<BIT)))
#define GET_BIT(VAR,BIT)    ((VAR) & 0X01<<BIT)
#define TOG_BIT(VAR,BIT)    (VAR ^=(0x01<<BIT))
#define WRITE_BITS(REG,VAR,STARTBIT) (REG |=(VAR<<STARTBIT))

#define BitGetBits(VAR, Bits_Offest, Bits_Width) ((VAR) >> (Bits_Offest)) & (((1U << (Bits_Width)) - 1U))

#define BitSetBits(VAR, Bits_Offest, Bits_Width, Value) (((VAR) & ~(((1U << (Bits_Width)) - 1U) << (Bits_Offest))) | (((Value) & ((1U << (Bits_Width)) - 1U)) << (Bits_Offest)))

/*
 * MACRO LIKE FUNCTION ?? Can't get it search
 * #define FUNC(ARG1,ARG2)  (ARG1+ARG2)
 * 0b00001111
 * SetPinVal(7,GET_BIT(0b00001111,7))
*/

#endif /* BIT_MATH_H_ */
