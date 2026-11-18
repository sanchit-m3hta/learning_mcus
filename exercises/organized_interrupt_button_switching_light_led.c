#include "stm32f4xx.h"


void clock_setup(void){
	//Enable Peripheral Clocks: Turn on clock signal
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;			//GPIO A and GPIO C
	(void)RCC->AHB1ENR;			// Dummy read: stalls CPU until the peripheral clock signal finishes propagating across the bus

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;			//System Configuration Controller - used to route GPIO pins to external interrupts
	(void)RCC->APB2ENR;
}


void io_setup(void){
	//CONFIGURE P5A to be output (built-in LED)
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER5_1;

	//CONFIGURE PC13 to be input (user button)
	GPIOC->MODER &= ~(GPIO_MODER_MODER13_0 | GPIO_MODER_MODER13_1);
}


void startup_state(void){
	GPIOA->ODR &= ~GPIO_ODR_OD5;		//Built-in LED starts is turned off initially
}


void interrupt_setup(void){
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;		//inside the 4th External interrupt configuration register, connect interrupt line to PC13
	EXTI->IMR |= EXTI_IMR_IM13;		//UNMASK INTERRUPT LINE 13
	EXTI->FTSR |= EXTI_FTSR_TR13;	//TRIGGER INTERRUPT ON FALLING EDGE ON THE INPUT LINE i.e falling edge recieved on PC13

}

void EXTI15_10_IRQHandler(void){
	if ((EXTI->PR & EXTI_PR_PR13) != 0){
		GPIOA->ODR ^= GPIO_ODR_OD5;		//Flip the state of the Built-in LED
		EXTI->PR = EXTI_PR_PR13;		//Clear the pending bit, bit 13, so its can be triggerd again
	}
}


int main(void){

	clock_setup();
	io_setup();
	startup_state();
	interrupt_setup();
	NVIC_EnableIRQ(EXTI15_10_IRQn);		//interrupt handler for interrupt lines 10 to 15

	while(1){
		//nothing
	}

	return 0;
}
