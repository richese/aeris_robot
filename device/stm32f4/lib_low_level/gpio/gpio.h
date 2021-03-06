#ifndef _GPIO_H_
#define _GPIO_H_

#include "../lib_low_level.h"
#include "stm32f4xx_gpio.h"

/*
#define GPIO_BASE	GPIOF

#define LED_1	(1<<13)
#define LED_2	(1<<14)
#define LED_3	(1<<15)
*/


#define GPIO_BASE	GPIOB

#define LED_1	(1<<4)
#define LED_2	(1<<5)
#define LED_3	(1<<6)

#define LED_W_GPIO_BASE	    GPIOC
#define LED_W	          (1<<5)


#define LED_R	(LED_1)
#define LED_G	(LED_2)
#define LED_B	(LED_3)

#define KEY_GPIO    GPIOA
#define KEY_1       (1<<0)

void gpio_init();
void led_on(u32 led);
void led_off(u32 led);
u32 get_key();

#endif
