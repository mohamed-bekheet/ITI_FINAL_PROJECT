/*
 * SYSTICK_interface.h
 *
 *  Created on: Aug 10, 2022
 *      Author: mohamed moustafa aly
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

//Macros
//AHB has main system clock
#define SYSTICK_AHB_8 		0
#define SYSTICK_AHB 		1



/*
 * The processor has a 24-bit system timer, SysTick, that counts down from the reload value to
 * zero, reloads (wraps to) the value in the LOAD register on the next clock edge, then counts
 * down on subsequent clocks.
 * When the processor is halted for debugging the counter does not decrement.
 *
 */

/*
 * STK_voidInit
 * description: Selects the clock source of the SysTick (AHB, AHB/8)
 */
void STK_voidInit(u32 Copy_u32SyClckFreq,u8 Copy_u8ClkSRC);


/*
 * STK_voidSetBusyWait
 * description: Starts a synchronous wait (delay)
 */
void STK_voidSetBusyWait(u32 Copy_u32TickCount);

void STK_voidDelayus(u32 Copy_u32TimeIn_us);

/*
 * STK_voidSetPeriodicInterval
 * description: Starts a periodic interval asynchronous wait
 */
void STK_voidSetPeriodicInterval(u32 Copy_u32TickCount, void (*ptr)(void));


/*
 * STK_voidSetSingleInterval
 * description: Starts a single interval asynchronous wait
 */
void STK_voidSetSingleInterval(u32 Copy_u32TickCount, void (*ptr)(void));

/*
 * STK_voidStopTimer
 * description: Stops the Timer
 */
void STK_voidStopTimer(void);

/*
 * STK_u32GetRemainingTicks
 * description: Gets the number of ticks remaining until we reach zero
 */
u32 STK_u32GetRemainingTicks(void);

/*
 * STK_u32GetElapsedTicks
 * description: Gets the number of ticks elapsed since we started counting
 */
u32 STK_u32GetElapsedTicks(void);



#endif /* SYSTICK_INTERFACE_H_ */
