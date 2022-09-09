/*
 * USART_program.c
 *
 *  Created on: Aug 21, 2022
 *      Author: mohamed moustafa aly
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"



/*
 * function to Initialize the USARTs
 */
void USART_voidInit(USART_t *UsartREG,u32 Copy_u16BaudRate){

	float UARTDIV = 8000000/(16*(float)Copy_u16BaudRate);

		UsartREG->CR1 |= (DATA_BITS << 12);//define the word length
		UsartREG->CR2 |= (STOP_BITS << 12);//program stop bits
		if(UART_DMA_TRANSMMIT_ENABLE) SET_BIT(UsartREG->CR3,7) ;
		if(UART_DMA_RECIEVE_ENABLE) SET_BIT(UsartREG->CR3,6);
		//USARTDIV = DIV_Mantissa + (DIV_Fraction / 16)
		UsartREG->BRR = ( ((int)UARTDIV << 4) | (int)((UARTDIV - (int)UARTDIV)*16) );
		UsartREG->CR1 |= (1 << 13);    //enable the USART
		UsartREG->CR1 |= (1 << 3);     //SET TE to send idle frame
		UsartREG->CR1 |= (1 << 7);	 //SET the TXEIE
		UsartREG->CR1 |= (1 << 2);	 //SET the RE(Receiver enable) bit USART_CR1. This enables the
		UsartREG->CR1 |= (1 << 5);	 //SET the RXNEIE



}



void USART_voidSendByte(USART_t *UsartREG, u16 Copy_u8Value){

			//UsartREG->CR1 |= (1 << 3);    //SET TE to send idle frame
			while (!GET_BIT(UsartREG->SR,6));         //TC != 0     wait for the last transmission to complete
			while (!GET_BIT(UsartREG->SR,7));    //TXE != 1
			UsartREG->DR = (Copy_u8Value & 0b111111111);



}


void USART_voidSendString(USART_t *UsartREG,char ptr_u8Array[]){



				while (!GET_BIT(UsartREG->SR,6));         //TC != 0     wait for the last transmission to complete
				//UsartREG->CR1 |= (1 << 3);    //SET TE to send idle frame
				u8 i = 0;
				while(ptr_u8Array[i]!='\0'){
					while (!GET_BIT(UsartREG->SR,7));			//TXE != 1
					UsartREG->DR = (ptr_u8Array[i] & 0b111111111);
					i++;
				}

	}





/*

void USART_voidEnableInteruptReceiver(USART_t *UsartREG){
	switch(Copy_u8UsartNum){
		case(USART_1):
			//UsartREG->CR1 |= (1 << 13);    //enable the USART
			UsartREG->CR1 |= (1 << 2);    //SET RE
			UsartREG->CR1 |= (1 << 5);    //SET RXNE to enable recieve interrupt
			break;

		case(USART_2):
			//REG_USART2->CR1 |= (1 << 13);    //enable the USART
			REG_USART2->CR1 |= (1 << 2);    //SET RE
			REG_USART2->CR1 |= (1 << 5);    //SET RXNE to enable recieve interrupt
			break;

		case(USART_3):
			//REG_USART3->CR1 |= (1 << 13);    //enable the USART
			REG_USART3->CR1 |= (1 << 2);    //SET RE
			REG_USART3->CR1 |= (1 << 5);    //SET RXNE to enable recieve interrupt
			break;
		}

}

*/

char USART_u8RecieveByte(USART_t *UsartREG){
	long unsigned int ccc;
	ccc = 0;
    while(!GET_BIT(UsartREG->SR,5) && (ccc <= 9900000) )  //RXNE
    	ccc++;
    if(ccc >= 9900000)
    	return '\0';
    else
    	return UsartREG->DR;
}



/*
void USART1_Handler(void){
	static u8 flag=0;
	u8 byteRecieved = UsartREG->DR;
	//USART_voidSendByte(USART_2,byteRecieved);


	GPIO_voidSetPinValue(GPIO_PORTA, 0,flag);
	flag = !flag;
}


*/
