#include "stm32f4xx.h"

int main(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;		//(1U << 0); // ENABLE GPIO A CLOCK

	GPIOA->MODER |= GPIO_MODER_MODER5_0;		//(1U << 10);

	GPIOA->MODER &= ~GPIO_MODER_MODER5_1;		//~(1U << 11);

	GPIOA->ODR |= GPIO_ODR_OD5; 				//(1U << 5);

	while(1){
		for (volatile uint32_t i = 0; i < 500000; i++){}
		GPIOA->ODR ^= GPIO_ODR_OD5;
	}

	return 0;
}
