#include "pca9548.h"

void
pca9548_init(void)
{
    GPIO_InitTypeDef reset_init;

    reset_init.GPIO_Pin = PCA9548_RESET_GPIO_PIN;
    reset_init.GPIO_Mode = GPIO_Mode_OUT;
    reset_init.GPIO_OType = GPIO_OType_PP;
    reset_init.GPIO_Speed = GPIO_Speed_100MHz;
    reset_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(PCA9548_RESET_GPIO_BASE, &reset_init);
    pca9548_reset();
}

void
pca9548_reset(void)
{
    GPIO_ResetBits(PCA9548_RESET_GPIO_BASE, PCA9548_RESET_GPIO_PIN);
    timer_delay_loops(10000);
    GPIO_SetBits(PCA9548_RESET_GPIO_BASE, PCA9548_RESET_GPIO_PIN);
    timer_delay_loops(10000);
}

void
pca9548_set_bus(u32 bus_id)
{
    pca9548_reset();

    i2cStart();
    i2cWrite(PCA9548_ADDRESS);
    i2cWrite((1<<bus_id));
    i2cStop();

    timer_delay_loops(1000);
}

u32
pca9548_read_bus(void)
{
    u32 tmp;

    i2cStart();
    i2cWrite(PCA9548_ADDRESS | 0x01);
    tmp = i2cRead(1);
    i2cStop();

    return tmp;
}
