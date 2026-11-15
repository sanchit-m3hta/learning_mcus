#include "stm32f4xx.h"
#define DELAY 1000 //ms

void delay_ms(uint32_t ms){

	SysTick->LOAD = 15999U;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	for (volatile uint32_t i = ms; i > 0; i--){
		while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0){
					//WAIT
			}
	}

}

int main(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER5_1;

	GPIOA->ODR &= ~GPIO_ODR_OD5;

	while(1){
		GPIOA->ODR |= GPIO_ODR_OD5;
		delay_ms(DELAY);
		GPIOA->ODR &= ~GPIO_ODR_OD5;
		delay_ms(DELAY);

	}

	return 0;
}
