/*
 * main.c
 *
 *  Created on: Aug 8, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */
#define STM_BLUEBILL


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"

#include "OS_interface.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"
#include "testVoiceData.h"
#include "SEVENSEG_interface.h"

#include "USART_interface.h"
#include "SPI_interfce.h"

#include "DMA_interface.h"
#include "DMA_private.h"
u32 SYSFREQ ;//from rcc

u32 STK_FREQ=0;//from systick handler
unsigned long long STK_COUNTS=0;//from systick handler



#define LED_PORT GPIO_PORTA
#define LED_PIN 0

 u32 OnTime = 100;//in ms
 u32 OffTime = 100;//in ms

 void LED_PWM_RUN(void){
	u32 currT_ms=STK_COUNTS;//*1000/SYSFREQ;
 	if(currT_ms <= OnTime)GPIO_voidSetPinValue(LED_PORT, LED_PIN, GPIO_HIGH);
 	else if (currT_ms < OnTime+OffTime)GPIO_voidSetPinValue(LED_PORT, LED_PIN, GPIO_LOW);
 	else if (currT_ms >= OnTime+OffTime) STK_COUNTS = 0;

 }
 //min 2 milli second
void LED_PWM_INIT(u32 OnTime_ms, u32 OffTime_ms){

	STK_voidSetPeriodicInterval( (SYSFREQ/8)/1000 ,LED_PWM_RUN) ;//1000 >>1ms every count is 1microsecond
	OnTime = OnTime_ms ;
	OffTime = OffTime_ms ;
}

void LED_TOG0(void) {

	static u8 x = 0;
	GPIO_voidSetPinValue(GPIO_PORTA, 0, x);
	x = 1 - x;
}

SevenSeg_pins_t SevenSeg1 = {
		////a,b,c,d,e,f,g
		{ { GPIO_PORTA, 0 }, { GPIO_PORTA, 1 }, {GPIO_PORTA, 2 }, { GPIO_PORTA, 3 }, { GPIO_PORTA, 4 }, { GPIO_PORTA,5 }, { GPIO_PORTA, 6 } },
		{ GPIO_PORTA, 9},//enable pin
	    .activeHigh= 0,//active High
};
SevenSeg_pins_t SevenSeg2 = {
		////a,b,c,d,e,f,g
		{ { GPIO_PORTA, 0 }, { GPIO_PORTA, 1 }, {GPIO_PORTA, 2 }, { GPIO_PORTA, 3 }, { GPIO_PORTA, 4 }, { GPIO_PORTA,5 }, { GPIO_PORTA, 6 } },
		{ GPIO_PORTA, 10},//enable pin
	    .activeHigh= 0,//active High
};

/*
void SendAudio(u8 *sound_header, unsigned int header_lenght) {
	GPIO_SetPinValue(GPIOA, 8, GPIO_HIGH);
	static u16 x = 0;

	GPIO_SetChannelGroupValue(GPIOA, 0, 8, sound_header[x++]);

	if (x == header_lenght)
		x = 0;

	GPIO_SetPinValue(GPIOA, 8, GPIO_LOW);

}
*/
SPI_interfce SPI1APP={
		.moduleReg =SPI_1,
		.baudrate = BR_8,
		.commUMode = COMM_FULLDUPLEX,

		.operationMode = OPER_MASTER,
		.polarity = POL_SCK_LOW_LEVEL,
		.phase = PHA_RISING_TRIG,//LEADING  ,RISING_TRIG TRAILING

		.frameFormate =FRAM_8BIT,
		.dataOrder = DAOR_MSB_FIRST,

		.nssMode = NSS_OUTPUT_MODE_ENABLE,
		
		.SCK_PORT = GPIO_PORTA,
		.SCK_PIN = 5,
		.MOSI_PORT = GPIO_PORTA,
		.MOSI_PIN = 7,
		.MISO_PORT = GPIO_PORTA,
		.MISO_PIN = 6,
		.NSS_PORT = GPIO_PORTA,
		.NSS_PIN = 4,
	};

u16 BUFFERSIZE = 10;
u8 UartDmaBuffer[10];

void DMA_CB(void){
	GPIO_voidSetPinValue(LED_PORT, 0, GPIO_LOW);
	if (DMA_GetFlag(&(DMA_REG->CH5),1))
	{
	
	if (UartDmaBuffer == 'M')
	{
		LED_PWM_INIT(2, 2); //min 2ms
	}
	else if (UartDmaBuffer == 'B')
	{
		LED_PWM_INIT(50, 50); //min 2ms
	}
		DMA_CLRFlag(&(DMA_REG->CH5),1);
	}
	
}

void DMA_UART2SPI_APP(void){
	RCC_voidPeripheralClockEnable(RCC_AHB, RCC_DMA1);
	
	DMA_RESRTREG(&(DMA_REG->CH5));
	
	DMA_SetPeripheralAddr( &(DMA_REG->CH5) ,&USART1_DR_ADDR_DMA);//source
	//DMA_SetMemoryAddr( &(DMA_REG->CH5) ,&UartDmaBuffer);//destination
	DMA_SetMemoryAddr( &(DMA_REG->CH5) ,&SPI1_DATA_ADDR_DMA);
	DMA_ConfigTotalNumberData(&(DMA_REG->CH5),BUFFERSIZE);
	DMA_ConfigMemorySize(&(DMA_REG->CH5),MEMS_8BIT);
	DMA_ConfigPeripheralSize(&(DMA_REG->CH5),PERS_8BIT);
	DMA_ConfigPriority(&(DMA_REG->CH5),PRIO_VERYHIGH);
	DMA_EnableMEMInc(&(DMA_REG->CH5));
	DMA_ConfigDataTransDirection(&(DMA_REG->CH5),DADIR_CIRCULAR);
	//DMA_EnableEndTxInterrupt(&(DMA_REG->CH5));
	//DMA_SetCallBackChannel5(DMA_CB);
	DMA_Enablechannel(&(DMA_REG->CH5));

}

void DMA_UART2BUFFER_APP(void){
	RCC_voidPeripheralClockEnable(RCC_AHB, RCC_DMA1);

	DMA_RESRTREG(&(DMA_REG->CH5));

	DMA_SetPeripheralAddr( &(DMA_REG->CH5) ,&USART1_DR_ADDR_DMA);//source
	DMA_SetMemoryAddr( &(DMA_REG->CH5) ,&UartDmaBuffer);//destination
	DMA_ConfigTotalNumberData(&(DMA_REG->CH5),BUFFERSIZE);
	DMA_ConfigMemorySize(&(DMA_REG->CH5),MEMS_8BIT);
	DMA_ConfigPeripheralSize(&(DMA_REG->CH5),PERS_8BIT);
	DMA_ConfigPriority(&(DMA_REG->CH5),PRIO_VERYHIGH);
	DMA_EnableMEMInc(&(DMA_REG->CH5));
	DMA_ConfigDataTransDirection(&(DMA_REG->CH5),DADIR_CIRCULAR);
	//DMA_EnableEndTxInterrupt(&(DMA_REG->CH5));
	//DMA_SetCallBackChannel5(DMA_CB);
	DMA_Enablechannel(&(DMA_REG->CH5));

}

int main(void) {
//////////////////////////////////////////INITIALIZATION/////////////////////////////////////
	RCC_voidInit();
	RCC_voidPeripheralClockEnable(RCC_APB2, RCC_GPIOA);
	SYSFREQ = RCC_u32GetSYSCLK();
	STK_voidInit(SYSFREQ, SYSTICK_AHB_8);

	//USART1 PINS
	GPIO_voidSetPinMode(GPIO_PORTA, 9, GPIO_PIN_MODE_AF_PP_2MHZ_OUTPUT);  	  //TX
	GPIO_voidSetPinMode(GPIO_PORTA, 10, GPIO_PIN_MODE_FLOATING_INPUT);    //RX
	//RCC_voidPeripheralClockEnable(RCC_APB2, RCC_USART1);
	//USART_voidInit(USART_1,115200);
	//DMA_UART2BUFFER_APP();


	//output configuration
	//take about 10 micro second
	GPIO_voidSetPinMode(LED_PORT, LED_PIN, GPIO_PIN_MODE_GP_PP_10MHZ_OUTPUT);
	GPIO_voidSetPinValue(LED_PORT, LED_PIN, GPIO_HIGH);
	

	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TEST NORMAL UART
	//USART_voidSendString(USART_1,"start\n");

////////////////////////////////////APPLICATION//////////////////////////////////////////////

	LED_PWM_INIT(2, 2); //min 2ms


	SPI_Init(&SPI1APP);	
	SPI_handleDATAFrame(&SPI1APP,'m',15);	//TEST NORMAL SPI

	while (1) {
		//USART_voidSendString(USART_1,UartDmaBuffer);
		SPI_handleDATAFrame(&SPI1APP,'m',15);
	}

	return 0;
}









//********************************************************************************//
	//OS_voidCreateTask(0, 1, 5, LED_TOG0);
	//OS_voidCreateTask(1, 2, 1, LED_TOG1);
	//OS_voidCreateTask(2, 4, 3, LED_TOG2);

	//GPIO_voidSetPinValue(GPIO_PORTA, 8, GPIO_HIGH);
	//OS_voidStartScheduler();
/************************************************************************************/

	//SS_voidWriteDigit(&SevenSeg1, seven);
