/*
 * NVIC_interface.h
 * Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */
/***/


#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_


typedef enum{
	NVIC_RESET=1,
	NMI,
	HARDFAULT,
	MMFAULT,//MEMORY MANAGMENT FAULT
	BUSFAULT,//BUS FAULT
	USAGEFAULT,
	SVCALL =1,
	PENDSV,
	_SYSTICK,

	NVIC_DMA1_Channel3 = 13,
	NVIC_DMA1_Channel5 = 15,
	//CONTINUED......
}NVIC_EXCEPTIONS_E;

#define		NVIC_GROUP_4_BITS		0x05FA0300
#define		NVIC_GROUP_3_BITS		0x05FA0400
#define		NVIC_GROUP_2_BITS		0x05FA0500
#define		NVIC_GROUP_1_BITS		0x05FA0600
#define		NVIC_GROUP_0_BITS		0x05FA0700

//#define		NVIC_GROUP_4_BITS		0
//#define		NVIC_GROUP_3_BITS		1
//#define		NVIC_GROUP_2_BITS		2
//#define		NVIC_GROUP_1_BITS		3
//#define		NVIC_GROUP_0_BITS		4


/*
 * NVIC_voidInit
 * Parameters: void
 * description: Sets the Priority Model for group & sub-priorities
 */
void NVIC_voidInit(void);


/*
 * NVIC_voidEnableInterrupt
 * parameters:
 * description: Sets the NVIC enable pin for a specific interrupt
 */
void NVIC_voidEnableInterrupt(NVIC_EXCEPTIONS_E ExceptionPosition);


/*
 * NVIC_voidDisableInterrupt
 * parameters:
 * description: Sets the NVIC disable pin for a specific interrupt
 */
void NVIC_voidDisableInterrupt(NVIC_EXCEPTIONS_E ExceptionPosition);


void NVIC_SetPriority (NVIC_EXCEPTIONS_E ExceptionPosition, u32 priority);
void NVIC_voidSystemReset (void);


#endif /* NVIC_INTERFACE_H_ */
