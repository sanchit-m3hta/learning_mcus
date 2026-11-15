#include "stm32f4xx.h"

int main(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER5_1;

	GPIOC->MODER &= ~GPIO_MODER_MODER13_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER13_1;

	GPIOA->ODR &= ~GPIO_ODR_OD5;	//make led LO

	while(1){
		if((GPIOC->IDR & GPIO_IDR_ID13) == 0){
			GPIOA->ODR |= GPIO_ODR_OD5;		//make led HI
		}else{
			GPIOA->ODR &= ~GPIO_ODR_OD5;	//make led LO
		}
	}

	return 0;
}
