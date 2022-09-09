/*
 * OS_private.h
 *
 *  Created on: Aug 14, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */

#ifndef OS_PRIVATE_H_
#define OS_PRIVATE_H_

typedef struct{
	u8 Periodicity;
	u8 InitialDelay;//start after some counts
	u8 TaskID;
	u8 State;
	u8 SuspendTime;
	void (*Fptr)(void);//task function
}Task;

void Scheduler(void);//handle calling and switching tasks


#endif /* OS_PRIVATE_H_ */
