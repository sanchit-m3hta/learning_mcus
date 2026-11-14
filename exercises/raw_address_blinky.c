#include "stm32f4xx.h"

int main(void)
{
	//RCC base address = 0x40023800
	//RCC_AHB1ENR offset = 0x30
	*(volatile uint32_t *)0x40023830 |= (1U << 0); //set bit 0 of RCC AHB1NR to 1, START THE CLOCK
	//GPIOA base address = 0X40020000
	//GPIO_MODER offset = 0x00
	*(volatile uint32_t *)0X40020000 |= (1U << 10); //set bit 10 of GPIO MODER A to 1 (GPIO A5)
	*(volatile uint32_t *)0X40020000 &= ~(1U << 11); // set bit 11 of GPIO MODER A to 0 (GPIO A5)

	//GPIOA base address = 0x40020000
	//GPIO_ODR offest = 0x14
	*(volatile uint32_t *)0x40020014 |= (1U << 5);//

	while(1){

		for (volatile uint32_t i = 0; i < 500000; i++){}
		*(volatile uint32_t *)0x40020014 ^= (1U << 5);

	}


}
