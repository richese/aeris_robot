#ifndef _AERIS_ERROR_H_
#define _AERIS_ERROR_H_

#include "aeris_robot.h"


#define aeris_error(error_code) \
    if (error_code != 0) \
    { \
        printf_("robot error %s:%u\n", __FILE__, __LINE__); \
        sched_off(); \
        GPIO_SetBits(AERIS_RGB_GPIO_BASE, AERIS_RGB_LED_1); \
        GPIO_SetBits(AERIS_RGB_GPIO_BASE, AERIS_RGB_LED_2); \
        GPIO_SetBits(AERIS_RGB_GPIO_BASE, AERIS_RGB_LED_3); \
        while(1) \
        { \
        u32 _aeris_error_ii_; \
        for (_aeris_error_ii_ = 0; _aeris_error_ii_ < error_code; _aeris_error_ii_++) \
        { \
            GPIO_ResetBits(AERIS_RGB_GPIO_BASE, AERIS_RGB_LED_1); \
            timer_delay_loops(10000); \
            GPIO_SetBits(AERIS_RGB_GPIO_BASE, AERIS_RGB_LED_1); \
            timer_delay_loops(2000000); \
        } \
        timer_delay_loops(10000000); \
        printf_("robot error %s:%u\n", __FILE__, __LINE__); \
        }; \
    } \


#endif /* _AERIS_ERROR_H_ */
