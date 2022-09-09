/*
 * NVIC_program.c
 *
 *  Created on: Aug 8, 2022
 *        Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
*/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"


/*
 * NVIC_voidInit
 * Parameters: void
 * description: Sets the Priority Model for group & sub-priorities
 */
void NVIC_voidInit(void){

	SCB_AIRCR = NVIC_PRIORITY_DISTRIBUTION;

//	switch(NVIC_PRIORITY_DISTRIBUTION){
//
//	case NVIC_GROUP_4_BITS:
//		SCB_AIRCR = 0x05FA0300;
//		break;
//	case NVIC_GROUP_3_BITS:
//		SCB_AIRCR = 0x05FA0400;
//		break;
//	case NVIC_GROUP_2_BITS:
//		SCB_AIRCR = 0x05FA0500;
//		break;
//	case NVIC_GROUP_1_BITS:
//		SCB_AIRCR = 0x05FA0600;
//		break;
//	case NVIC_GROUP_0_BITS:
//		SCB_AIRCR = 0x05FA0700;
//		break;
//
//	}


}


/*
 * NVIC_voidSetPriority
 * parameters:Copy_u8GroupPriority(0-7),Copy_u8SubPriority(0-7)
 * return value:
 * description: Sets the priority for a specific interrupt
 */
void NVIC_voidSetPriority(NVIC_EXCEPTIONS_E ExceptionPosition, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority){

	//NVIC_IPR[Copy_u8InterruptPosition] = (Copy_u8GroupPriority<<(4+NVIC_PRIORITY_DISTRIBUTION)) | (Copy_u8SubPriority<<4);
	NVIC_IPR[ExceptionPosition] = (Copy_u8GroupPriority<<(4+((NVIC_PRIORITY_DISTRIBUTION-0x05FA0300)/0x100))) | (Copy_u8SubPriority<<4);

}

/*
 * NVIC_voidEnableInterrupt
 * parameters:
 * description: Sets the NVIC enable pin for a specific interrupt
 */
void NVIC_voidEnableInterrupt(NVIC_EXCEPTIONS_E ExceptionPosition){

	if(ExceptionPosition <= 31){
		//SET_BIT(NVIC_ISER0, ExceptionPosition);//enable only one
		NVIC_ISER0 = 1 << (ExceptionPosition);
	}else if(ExceptionPosition <= 63){
		NVIC_ISER1 = 1 << (ExceptionPosition - 32);
	}
}


/*
 * NVIC_voidDisableInterrupt
 * parameters:
 * description: Sets the NVIC disable pin for a specific interrupt
 */
void  NVIC_voidDisableInterrupt(NVIC_EXCEPTIONS_E ExceptionPosition){
	if(( ExceptionPosition < 32 )){
		NVIC_ICER0 = 1 << ExceptionPosition;
	}
	else if (ExceptionPosition < 63 ){
		NVIC_ICER1 =  1 << (ExceptionPosition - 32);
	}

}



void NVIC_SetPriority (NVIC_EXCEPTIONS_E ExceptionPosition, u32 priority);
void NVIC_voidSystemReset (void);




