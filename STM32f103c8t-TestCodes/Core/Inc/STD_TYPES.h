/*
 * STD_TYPES.h
 *
 *  Created on: Aug 3, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


typedef    unsigned char         u8   ;
typedef    unsigned short int    u16  ;
typedef    unsigned int          u32  ;

typedef    signed char           s8   ;
typedef    signed short int      s16  ;
typedef    signed int            s32  ;

typedef    volatile unsigned char         vu8   ;
typedef    volatile unsigned short int    vu16  ;
typedef    volatile unsigned int          vu32  ;

typedef    volatile signed char           vs8   ;
typedef    volatile signed short int      vs16  ;
typedef    volatile signed int            vs32  ;

typedef enum{
	 FALSE,
	 TRUE,
}bool;

// STD_TYPES  convention
// u: unsigned - s:signed  -  f: float
// 8,16,32 number of bits can be stored in this variable before an overflow

// ex: uint8_t   unsigned int of 8 bits
#endif /* STD_TYPES_H_ */
