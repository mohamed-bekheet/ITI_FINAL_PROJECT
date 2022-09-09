/*
 * RCC_program.c
 *
 *  Created on: Aug 3, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_config.h"
#include "RCC_private.h"


void RCC_voidInit(void)
{
	//Clock control register (RCC_CR)
	RCC_CR = 0;
	RCC_CFGR = 0;


	RCC_CR |= (RCC_HSI_ON<<0);
	if(RCC_TRIMMING_VAL<32)
		RCC_CR |= (RCC_TRIMMING_VAL<<3);
	RCC_CR |= (RCC_HSE_ON<<16);
	RCC_CR |= (RCC_HSE_BYPASS<<18);
	RCC_CR |= (RCC_CSS_ON<<19);

	if(RCC_MCO_SRC > RCC_NOCLK_MCO)
	RCC_CFGR |=(RCC_MCO_SRC<<24);

	RCC_CFGR |= (RCC_AHB_PRESCALER <<4);
	RCC_CFGR |= (RCC_APB2_PRESCALER <<11);
	RCC_CFGR |= (RCC_APB1_PRESCALER <<8);
	RCC_CFGR |= (RCC_ADC_PRESCALER <<14);
	RCC_CFGR |= (RCC_PLL_SRC <<16);
	RCC_CFGR |= (RCC_PLL_HSE_DIV <<17);
	if(RCC_PLL_MUL > 1 && RCC_PLL_MUL < 17)
		RCC_CFGR |= ((RCC_PLL_MUL-2) << 18);

	RCC_CR |= (RCC_PLL_ON<<24);
	if(RCC_SYSTEM_CLOCK_SWITCH < 4)
		RCC_CFGR|=(RCC_SYSTEM_CLOCK_SWITCH << 0);//System clock switch

}


void RCC_voidPeripheralClockEnable(u8 Copy_u8BusName, Peripherals_e Copy_u8PerphiralName)
{
	switch(Copy_u8BusName)
	{
		case RCC_AHB:	SET_BIT(RCC_AHBENR, Copy_u8PerphiralName);				break;
		case RCC_APB2:	SET_BIT(RCC_APB2ENR, (Copy_u8PerphiralName - 62));		break;
		case RCC_APB1:	SET_BIT(RCC_APB1ENR, (Copy_u8PerphiralName - 32));	   	break;
	}
}

void RCC_voidPeripheralClockDisable(u8 Copy_u8BusName, Peripherals_e Copy_u8PerphiralName)
{
	switch(Copy_u8BusName)
	{
		case RCC_AHB:	CLR_BIT(RCC_AHBENR, Copy_u8PerphiralName);				break;
		case RCC_APB2:	CLR_BIT(RCC_APB2ENR, (Copy_u8PerphiralName - 62));		break;
		case RCC_APB1:	CLR_BIT(RCC_APB1ENR, (Copy_u8PerphiralName - 32));		break;
	}
}


u32 RCC_u32GetSYSCLK(void){
	return RCC_SYSCLK_FREQ;
}

