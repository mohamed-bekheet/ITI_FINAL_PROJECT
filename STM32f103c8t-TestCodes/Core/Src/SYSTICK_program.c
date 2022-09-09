/*
 * SYS_TICK_program.c
 *
 *  Created on: Aug 10, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_config.h"
#include "SYSTICK_private.h"

#include "GPIO_interface.h"
/*
 *
 * SysTick timer (STK)
 * The processor has a 24-bit system timer, SysTick, that counts down from the reload value to
 * zero, reloads (wraps to) the value in the LOAD register on the next clock edge, then counts
 * down on subsequent clocks.
 * When the processor is halted for debugging the counter does not decrement.
 * */


void (*CallBack)(void) = (void *) 0;

u8 IntervalState = SYSTICK_PERIODIC_INTERVAL;
static u32 MAX_TIME_STK_us ; // in micro seconds

extern u32 STK_FREQ;
extern unsigned long long STK_COUNTS;
/*
 * STK_voidInit
 * description: Selects the clock source of the SysTick (AHB, AHB/8)
 */
void STK_voidInit(u32 Copy_u32SyClckFreq,u8 Copy_u8ClkSRC){

	switch(Copy_u8ClkSRC)
	{
	case SYSTICK_AHB_8:
		CLR_BIT(SYSTICK->CTRL,2);
		STK_FREQ = Copy_u32SyClckFreq/8;
		break;
	case SYSTICK_AHB:
		SET_BIT(SYSTICK->CTRL,2);
		STK_FREQ = Copy_u32SyClckFreq;
		break;
	}

	MAX_TIME_STK_us = (1677216/(STK_FREQ)*1000000);//=1677216
}




/*
 * STK_voidSetBusyWait
 * description: Starts a synchronous wait (normal delay based on frequency of the system clock)
 */
void STK_voidSetBusyWait(u32 Copy_u32TickCount){

	/* Disable the systick interrupt
	 * Set LOAD value
	 * start the timer
	 * empty loop until the flag is raised
	 * reset the flag
	 * Reset the LOAD register
	 * stop the timer
	 */
	CLR_BIT(SYSTICK->CTRL, 1);//Disable the systick interrupt
	SYSTICK->LOAD = (Copy_u32TickCount) & 0x00FFFFFF;//max is 24bit 0x00FFFFFF
	SET_BIT(SYSTICK->CTRL, 0);// Counter enable and start counting
	while(!(GET_BIT(SYSTICK->CTRL, 16)));//bit16::Returns 1 if timer counted to 0 since last time this was read.
	CLR_BIT(SYSTICK->CTRL, 0);// Counter disable and stop counting
	SYSTICK->VAL = 0;
}


/*
 * STK_voidSetBusyWait
 * description: Starts a synchronous wait (normal delay based on frequency of the system clock)
 */
void STK_voidDelayus(u32 Copy_u32TimeIn_us){

	u32 counts =  Copy_u32TimeIn_us*(STK_FREQ/1000000) ;

	float residual = (Copy_u32TimeIn_us/ MAX_TIME_STK_us);// MAX_TIME_STK_us=1677216
	//STK_voidSetBusyWait((u32) (Copy_u32TimeIn_us % MAX_TIME_STK_us) );
	for (; residual >= 0 ; residual --){
		STK_voidSetBusyWait((u32) counts );
	}
}
void STK_voidDelayms(u32 Copy_u32TimeIn_ms){

	u32 counts =  Copy_u32TimeIn_ms*(STK_FREQ/1000000) ;

	float residual = (Copy_u32TimeIn_ms/ (MAX_TIME_STK_us*1000));// MAX_TIME_STK_us=1677216
	//STK_voidSetBusyWait((u32) (Copy_u32TimeIn_us % MAX_TIME_STK_us) );
	for (; residual >= 0 ; residual --){
		STK_voidSetBusyWait((u32) counts*1000 );
	}
}

/*
 * STK_voidSetPeriodicInterval
 * description: Starts a periodic interval synchronous wait
 */
void STK_voidSetPeriodicInterval(u32 Copy_u32TickCount, void (*ptr)(void)){

	/* Set LOAD value
	 * assign the callback function to the handler
	 * Enable the interrupt
	 * start the timer
	 */
	CallBack = ptr;
	IntervalState = SYSTICK_PERIODIC_INTERVAL;

	SYSTICK->VAL=0;//A write of any value clears the field to 0, and also clears the COUNTFLAG bit in the STK_CTRL register to 0
	SYSTICK->LOAD = (Copy_u32TickCount - 1) & 0x00FFFFFF;//max is 16.77 second
	SET_BIT(SYSTICK->CTRL, 1);//SysTick exception request enable
	SET_BIT(SYSTICK->CTRL, 0);// Counter enable
}



/*
 * STK_voidSetSingleInterval
 * description: Starts a single interval asynchronous wait
 */
void STK_voidSetSingleInterval(u32 Copy_u32TickCount, void (*ptr)(void)){

	/* Set LOAD value
	 * assign the callback function to the handler
	 * Enable the interrupt
	 * start the timer
	 */

	IntervalState = SYSTICK_SINGLE_INTERVAL;
	SYSTICK->LOAD = (Copy_u32TickCount) & 0x00FFFFFF;
	CallBack = ptr;
	SET_BIT(SYSTICK->CTRL, 1);//SysTick exception request enable
	SET_BIT(SYSTICK->CTRL, 0);//Counter enable
}

/*
 * STK_voidStopTimer
 * description: Stops the Timer
 */
void STK_voidStopTimer(void){
	CLR_BIT(SYSTICK->CTRL, 0);// Counter disable
}

/*
 * STK_u32GetRemainingTicks
 * description: Gets the number of ticks remaining until we reach zero
 */
u32 STK_u32GetRemainingTicks(void){
	return SYSTICK->VAL ;
}
/*
 * STK_u32GetElapsedTicks
 * description: Gets the number of ticks elapsed since we started counting
 */
u32 STK_u32GetElapsedTicks(void){

	return 0;
}
//ISR
void SysTick_Handler(void){
	CallBack();
	STK_COUNTS ++;
	if(IntervalState == SYSTICK_PERIODIC_INTERVAL){

	}else{
		CLR_BIT(SYSTICK->CTRL, 0);//stop timer in case single interval
	}
	//no need to clear flag or interrupt flag
	//SYSTICK->VAL = 0; // Clearing the flag
	//CLR_BIT(SYSTICK->CTRL,1);
}
