/*
 * OS_program.c
 *
 *  Created on: Aug 14, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "RCC_interface.h"

#include "OS_interface.h"
#include "OS_config.h"
#include "OS_private.h"

//array of tasks
Task OS_Tasks[OS_NUMBER_OF_TASKS];

u32 TickCount = 0;


void Scheduler(void){

	for(u8 i = 0; i < OS_NUMBER_OF_TASKS; i++){//loop for tasks

		if((OS_Tasks[i].State == OS_TASK_READY)){//Check task ready state
			if(OS_Tasks[i].InitialDelay == 0){
				OS_Tasks[i].InitialDelay = OS_Tasks[i].Periodicity-1;
				OS_Tasks[i].Fptr();
			}else{
				OS_Tasks[i].InitialDelay--;//start after time delay(number multiple of OS_TICK_TIME)
			}
		}

	}
	TickCount++;
}


/*
 * OS_voidCreateTask
 */
void OS_voidCreateTask(u8 Copy_u8ID, u8 Copy_u8Periodicity, u8 Copy_u8InitialDelay, void (*ptr)(void)){

	OS_Tasks[Copy_u8ID].Fptr = ptr;
	OS_Tasks[Copy_u8ID].InitialDelay = Copy_u8InitialDelay;
	OS_Tasks[Copy_u8ID].Periodicity = Copy_u8Periodicity;
	OS_Tasks[Copy_u8ID].State = OS_TASK_READY;
	OS_Tasks[Copy_u8ID].TaskID= Copy_u8ID;


}
/*
 * OS_voidDeleteTask
 */
void OS_voidDeleteTask(u8 Copy_u8ID){

	OS_Tasks[Copy_u8ID].State = OS_TASK_DELETED;

}

/*
 * OS_voidSuspendTask
 */
void OS_voidSuspendTask(u8 Copy_u8ID, u8 Copy_u8SuspendTime){

	OS_Tasks[Copy_u8ID].State = OS_TASK_SUSPENDED;
	OS_Tasks[Copy_u8ID].SuspendTime = Copy_u8SuspendTime + TickCount;//as an offset from current system time

}

/*
 * OS_voidStartScheduler
 */
void OS_voidStartScheduler(void){

	STK_voidInit( RCC_u32GetSYSCLK() ,SYSTICK_AHB_8);
	Scheduler();
	STK_voidSetPeriodicInterval(OS_TICK_TIME, Scheduler);

}

/*
 * OS_voidResumeTask
 */
void OS_voidResumeTask(u8 Copy_u8ID){
	OS_Tasks[Copy_u8ID].State = OS_TASK_READY;
}

/*
 * OS_u8GetTaskState
 */
u8 OS_u8GetTaskState(u8 Copy_u8ID){

	return OS_Tasks[Copy_u8ID].State;

}
