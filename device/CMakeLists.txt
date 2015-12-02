cmake_minimum_required(VERSION 2.8.8)
project(LIB_LOW_LEVEL_STM32F4)


set(LIB_LOW_LEVEL_STM32F4_SOURCES
    stm32f4/lib_low_level/adc/adc.c
    stm32f4/lib_low_level/adc/stm32f4xx_adc.c
    stm32f4/lib_low_level/core/cortex_cpu.c
    stm32f4/lib_low_level/core/system_stm32f4xx.c
    stm32f4/lib_low_level/gpio/gpio.c
    stm32f4/lib_low_level/gpio/stm32f4xx_gpio.c
    stm32f4/lib_low_level/i2c/stm32f4xx_i2c.c
    stm32f4/lib_low_level/i2c/i2c.c
    stm32f4/lib_low_level/lib_low_level.c
    stm32f4/lib_low_level/misc.c
    stm32f4/lib_low_level/pwm/pwm.c
    stm32f4/lib_low_level/spi/spi.c
    stm32f4/lib_low_level/spi/stm32f4xx_spi.c
    stm32f4/lib_low_level/startup.c
    stm32f4/lib_low_level/stm32f4xx_rcc.c
    stm32f4/lib_low_level/timer/stm32f4xx_tim.c
    stm32f4/lib_low_level/timer/timer.c
    stm32f4/lib_low_level/uart/stm32f4xx_usart.c
    stm32f4/lib_low_level/uart/uart.c
)

add_library(lib_low_level OBJECT "${LIB_LOW_LEVEL_STM32F4_SOURCES}")
set_target_properties(lib_low_level PROPERTIES OUTPUT_NAME _low_level)
