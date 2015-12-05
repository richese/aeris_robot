#ifndef _PCA9548_H_
#define _PCA9548_H_

/* I2C switch IC */

#include "device/device.h"


#define PCA9548_RESET_GPIO_BASE        GPIOB
#define PCA9548_RESET_GPIO_PIN         (1<<1)

#define PCA9548_ADDRESS                (0xE0)


void pca9548_init(void);
void pca9548_reset(void);
void pca9548_set_bus(u32 bus_id);
u32 pca9548_read_bus(void);


#endif /* _PCA9548_H_ */
