/*
 * RCC_interface.h
 *
 *  Created on: Aug 2, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_ /// same exact name


/*
 * This driver responsible for Clocks for peripherals and reset system
 *
 * */
//for MCO
#define RCC_NOCLK_MCO 0b010
#define RCC_SYSCLK_MCO 0b100
#define RCC_HSI_MCO 0b101
#define RCC_HSE_MCO 0b110
#define RCC_PLL_MCO 0b111

/*
typedef enum{
	HSI,
	HSE,
	PLL,
	LSI,//40khz
	LSE,//32.768khz
}RCC_ClockSources;
*/

/*
typedef struct{
	vu32 HSION:1;//>
	vu32 HSIRDY:1;
	vu32 :1;
	vu32 HSITRIM:4;
	vu32 HSICAL:7;
	vu32 HSEON:1;//>
	vu32 HSERDY:1;
	vu32 HSEBYP:1;//>
	vu32 CSSON:1;//>
	vu32 :4;
	vu32 PLLON:1;//>
	vu32 PLLRDY:1;
}RCC_CR_t;//clock control register
*/

//volatile RCC_CR_t* RCC_CR_ptr;

//RCC_CR_ptr = ((volatile RCC_CR_t*)(0x40021000+0x00));


void RCC_voidClockSecuritySys(bool enable);

typedef enum{
	RCC_AHB,
	RCC_APB1,
	RCC_APB2,
}RCC_bus_e;

//Do not change any thing from here
//peripheral
#define RCC_AHB			0
#define RCC_APB1		1
#define RCC_APB2		2

#define RCC_MCO_NO		(-2)
#define RCC_SYS_CLK		(-1)

#define RCC_HSI			0b00
#define RCC_HSE			0b01 //8MHZ crystal
#define RCC_PLL			0b10


#define RCC_AHB_PRE_NO	0
#define RCC_AHB_PRE_2	8
#define RCC_AHB_PRE_4	9
#define RCC_AHB_PRE_8	10
#define RCC_AHB_PRE_16	11


//for MCO
#define RCC_NOCLK_MCO 0b010
#define RCC_SYSCLK_MCO 0b100
#define RCC_HSI_MCO 0b101
#define RCC_HSE_MCO 0b110
#define RCC_PLL_MCO 0b111

/*
typedef enum{
	NO,
	PRE2 = 8,
	PRE4,
	PRE8,
	PRE16,
}RCC_AHB_PRE;
*/
// we can't use enum in macros because it needs compiling and macros are preprocessor

typedef enum{  //new data type label int "peripheral name"
	   //AHB peripheral clock enable
	    RCC_DMA1,
	    RCC_DMA2,
	    RCC_SRAM,
	    RCC_RES1,
	    RCC_FLITF,
	    RCC_RES2,
	    RCC_CRCE,
	    RCC_RES3,
	    RCC_FSMC,
		//APB1 peripheral clock enable
	    RCC_RES4,
	    RCC_SDIO,
	    RCC_RES5,
	    RCC_RES6,
	    RCC_RES7,
	    RCC_RES8,
	    RCC_RES9,
	    RCC_RES10,
	    RCC_RES11,
	    RCC_RES12,
	    RCC_RES13,
	    RCC_RES14,
	    RCC_RES15,
	    RCC_RES16,
	    RCC_RES17,
	    RCC_RES18,
	    RCC_RES19,
	    RCC_RES20,
	    RCC_RES21,
	    RCC_RES22,
	    RCC_RES23,
	    RCC_RES24,
	    RCC_RES25,
	    RCC_TIM2,
	    RCC_TIM3,
	    RCC_TIM4,
	    RCC_TIM5,
	    RCC_TIM6,
	    RCC_TIM7,
	    RCC_TIM12,
	    RCC_TIM13,
	    RCC_TIM14,
	    RCC_RES26,
	    RCC_RES27,
	    RCC_WWDG,
	    RCC_RES28,
	    RCC_RES29,
	    RCC_SPI2,
	    RCC_SPI3,
	    RCC_RES30,
	    RCC_USART2,
	    RCC_USART3,
	    RCC_UART4,
	    RCC_UART5,
	    RCC_I2C1,
	    RCC_I2C2,
	    RCC_USB,
	    RCC_CAN,
	    RCC_BKP,
	    RCC_PWR,
	    RCC_DAC,
	    RCC_RES46,
	    RCC_RES31,
		//APB2 peripheral clock enable
	    RCC_AFIO,
	    RCC_RES32,
	    RCC_GPIOA,
	    RCC_GPIOB,
	    RCC_GPIOC,
	    RCC_GPIOD,
	    RCC_GPIOE,
	    RCC_GPIOF,
	    RCC_GPIOG,
	    RCC_ADC1,
	    RCC_ADC2,
	    RCC_TIM1,
	    RCC_SPI1,
	    RCC_TIM8,
	    RCC_USART1,
	    RCC_ADC3,
	    RCC_RES33,
	    RCC_RES34,
	    RCC_RES35,
	    RCC_TIM9,
	    RCC_TIM10,
	    RCC_TIM11,
	    RCC_RES36,
	    RES37,
	    RES38,
	    RES39,
	    RES40,
	    RES41,
	    RES42,
	    RES43,
	    RES44,
	    RES45
}Peripherals_e;


// PUPLIVC FUNCTION DECLARATION

//write it based on RCC configuration file
void RCC_voidInit (void);

/*
 * NAME:RCC_voidPeripheralClockEnable
 * RETURN TYPE: VOID
 * ARGUMENTS: Copy_u8BusName:U8 , (AHB,APB1,ABP2)
 * 			  Copy_u8PerphiralName : Peripherals_t , (ENUM VALUES)
 * DESCRIPTION: ENABLES PREPHIRAL CLK FOR CERTAIN PREPHIRAL
 */
void RCC_voidPeripheralClockEnable(u8 Copy_u8BusName, Peripherals_e Copy_u8PerphiralName);

void RCC_voidPeripheralClockDisable(u8 Copy_u8BusName, Peripherals_e Copy_u8PerphiralName);


u32 RCC_u32GetSYSCLK(void);

#endif /* RCC_INTERFACE_H_ */
