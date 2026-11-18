#include "stm32f4xx.h"

void EXTI15_10_IRQHandler(void){
	if((EXTI->PR & EXTI_PR_PR13) != 0){
		GPIOA->ODR ^= GPIO_ODR_OD5;
		EXTI->PR = EXTI_PR_PR13; //EVENT OCCURED
	}
}

int main(void){

	//Enabling Peripheral clocks
	//GPIOA and GPIOC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
	//System Configuration Controller
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;


	//Configure pins as input/output
	//LED as out
	GPIOA->MODER |= GPIO_MODER_MODER5_0;	//MODER5[1:0] = 01
	GPIOA->MODER &= ~GPIO_MODER_MODER5_1;	//MODER5[1:0] = 01
	GPIOA->ODR &= ~GPIO_ODR_OD5;	//Set the led to off
	//Button 1 as input
	GPIOC->MODER &= ~(GPIO_MODER_MODER13_0 | GPIO_MODER_MODER13_1); 	//MODER13[1:0] = 00

	//Sysconfig external interrupt configuration register 4: EXTI 12 TO EXTI 15
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	//EXTI external mask register
	EXTI->IMR |= EXTI_IMR_IM13;
	//External interrupt falling trigger selection: FALLING EDGE
	EXTI->FTSR |= EXTI_FTSR_TR13;

	NVIC_EnableIRQ(EXTI15_10_IRQn);

	while(1){

	}

	return 0;
}
