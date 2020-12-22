 /*
 ============================================================================
 Name        : main.c
 Author      : kamel Ghalgaoui
 Version     : 1.0
 Email	     : kamelghalgaoui7@gmail.com
 Copyright   : Your copyright notice
 Description : Blink Leds for STM32 F3
 ============================================================================
 */

/*
 *  LED_4  = GPIO_E_PIN_8   (top left   - Blue)
 *  LED_3  = GPIO_E_PIN_9   (top        - Red)
 *  LED_5  = GPIO_E_PIN_10  (top right  - Orange)
 *  LED_7  = GPIO_E_PIN_11  (right      - Green)
 *  LED_9  = GPIO_E_PIN_12  (bottom right  - Blue)
 *  LED_10 = GPIO_E_PIN_13  (bottom  - Red)
 *  LED_8  = GPIO_E_PIN_14  (bottom left  - Orange)
 *  LED_6  = GPIO_E_PIN_15  (left  - Green)
 *
 *  USER BUTTON: GPIO PA0,
 */

#include <stdint.h>

#define RCC_AHBENR		*((volatile uint32_t*)0x40021014) /* Clock Register */

#define GPIOE_MODER		*((volatile uint32_t*)0x48001000) /* GPIO E DIR Register*/
#define GPIOE_OTYPER	*((volatile uint32_t*)0x48001004) /* GPIO E Output Type Register */
#define GPIOE_OSPEEDR	*((volatile uint32_t*)0x48001008) /* GPIO E Output Speed Register */
#define GPIOE_PUPDR		*((volatile uint32_t*)0x4800100C) /* GPIO E pull-up/pull-down register */
#define GPIOE_ODR		*((volatile uint32_t*)0x48001014) /* GPIO Output data register */

#define GPIOA_MODER		*((volatile uint32_t*)0x48000000) /* GPIO A DIR register */
#define GPIOA_PUPDR		*((volatile uint32_t*)0x4800000C) /* GPIO A pull-up/pull-down register */
#define GPIOA_IDR		*((volatile uint32_t*)0x48000010) /* GPIO A Input data register */

#define FREQUENCY		500000


void init_gpio(void)
{
	RCC_AHBENR 		|= 	0x00220000; /* Enable Clock Gating GPIO Port E and A*/

	GPIOE_MODER 	|= 	0x55550000; /* Make PE8,9,10,11,12,13,14 and 15 as output */
	GPIOE_OTYPER 	|=	0x00000000; /* Make PE8,9,10,11,12,13,14 and 15 output reset state*/
	GPIOE_OSPEEDR	|=	0x55550000; /* Set PE8,9,10,11,12,13,14 and 15 Output Speed as Medium speed */
	GPIOE_PUPDR		|= 	0x00000000; /* PE8,9,10,11,12,13,14 and 15 No Pull Up No Pull Down */

	GPIOA_MODER 	|= 	0x00000000; /* Make PA0 as input */
	GPIOA_PUPDR		|= 	0x00000001; /* PA0 Pull Down */

}

inline void sleep(uint32_t freq)
{
	volatile uint32_t counter = 0;
	while (counter < freq) {
		counter ++;
	}
}

void leds_off()
{
	GPIOE_ODR	&=	~0x00008000; /* Led 6 off */
	sleep(FREQUENCY);

	GPIOE_ODR	&=	~0x00004000; /* Led 8 off */
	sleep(FREQUENCY);

	GPIOE_ODR	&=	~0x00002000; /* Led 10 off */
	sleep(FREQUENCY);

	GPIOE_ODR	&=	~0x00001000; /* Led 9 off */
	sleep(FREQUENCY);

	GPIOE_ODR	&=	~0x00000800; /* Led 7 off */
	sleep(FREQUENCY);

	GPIOE_ODR	&=	~0x00000400; /* Led 5 off */
	sleep(FREQUENCY);

	GPIOE_ODR	&=	~0x00000200; /* Led 3 off */
	sleep(FREQUENCY);

	GPIOE_ODR	&=	~0x00000100; /* Led 4 off */
}

void leds_on()
{
	GPIOE_ODR	= 	0x00000100; /* Led 4 On*/
	sleep(FREQUENCY);

	GPIOE_ODR	|= 	0x00000200; /* Led 3 On */
	sleep(FREQUENCY);

	GPIOE_ODR	|= 	0x00000400; /* Led 5 On */
	sleep(FREQUENCY);

	GPIOE_ODR	|=	0x00000800;	/* Led 7 On */
	sleep(FREQUENCY);

	GPIOE_ODR	|=	0x00001000; /* Led 9 On */
	sleep(FREQUENCY);

	GPIOE_ODR	|= 	0x00002000; /* Led 10 On */
	sleep(FREQUENCY);

	GPIOE_ODR	|= 	0x00004000; /* Led 8 On */
	sleep(FREQUENCY);

	GPIOE_ODR	|=	0x00008000;	/* Led 6 On */
}

int main(void)
{
	init_gpio();

	while (1) {
		if (GPIOA_IDR != 0x00) {
			leds_on();
			sleep(10 * FREQUENCY);
			leds_off();
			sleep(10 * FREQUENCY);
		}
	}
	return 0;
}
