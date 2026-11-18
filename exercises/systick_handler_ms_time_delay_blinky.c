#include "stm32f4xx.h"
#define DELAY_500_ms 500 //ms

volatile uint32_t ms_ticks = 0;

void SysTick_Handler(void){
	ms_ticks = ms_ticks + 1;
}


void delay_ms(uint32_t ms){
	volatile uint32_t start = ms_ticks;

	while((ms_ticks - start) < ms){

	}
}


int main(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER5_1;

	GPIOA->ODR &= ~GPIO_ODR_OD5;

	//System Tick Setup
	SysTick->LOAD = 15999U;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	while(1){
			GPIOA->ODR |= GPIO_ODR_OD5;
			delay_ms(DELAY_500_ms+1500);
			GPIOA->ODR &= ~GPIO_ODR_OD5;
			delay_ms(DELAY_500_ms - 250);
		}

	return 0;
}
