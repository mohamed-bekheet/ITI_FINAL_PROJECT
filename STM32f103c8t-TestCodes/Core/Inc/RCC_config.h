/*
 * RCC_config.h
 *
 *  Created on: Aug 2, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

//choose clock source
//enable all for other modules

#define RCC_SYSCLK_FREQ  8000000//HZ

//used for calibration let it 16
#define RCC_TRIMMING_VAL            16

// HSE clock
//enable state of HSE 1: on , 0: off
#define RCC_HSE_ON                  1  //high speed external clock signal (HSE) 4 to 16 MHz
#define RCC_HSE_BYPASS              0  //external clock source bypass up to 25MHz
#define RCC_CSS_ON                  1  //Clock security system enable

//HSI clock : internal 8 MHz RC Oscillator
// can be used as  a PLL input
#define RCC_HSI_ON                  1  //high speed internal clock signal (HSI)

//PLL
#define RCC_PLL_ON                  0//1:enable 0:disable

//The internal PLL can be used to multiply the HSI RC output or HSE crystal output clock frequency
#define RCC_PLL_SRC               RCC_HSE     // PLL entry clock source
#define RCC_PLL_HSE_DIV              0        //0or1Set and cleared by software to divide HSE before PLL entry. This bit can be written only
#define RCC_PLL_MUL                  4        //2 means will be multiplied by 2 same for 3 and 4 up to 17:::::PLL multiplication factor

//in case of want to active MCO write this in main func after RCC_init,::
//GPIO_voidSetPinMode(GPIO_PORTA, 8, GPIO_PIN_MODE_AF_PP_50MHZ_OUTPUT);
#define RCC_MCO_SRC             RCC_HSE_MCO//ex:RCC_SYSCLK_MCO selet MCO source from interface desction for mco


//7.2.6 System clock (SYSCLK) selection
#define RCC_SYSTEM_CLOCK_SWITCH   RCC_HSE //RCC_HSE //choose from:RCC_HSI,RCC_HSE,RCC_PLL




#define RCC_AHB_PRESCALER            1
#define RCC_APB1_PRESCALER           1
#define RCC_APB2_PRESCALER           1//1::not divided
#define RCC_ADC_PRESCALER            1





#endif /* RCC_CONFIG_H_ */
