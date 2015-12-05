#include "apds9950.h"

u32
apds9950_rgbc_init(void)
{
    u8 tmp;

    /* dummy read to recover from bus failure */
    //tmp = i2c_read_reg(APDS9950_ADDRESS, APDS9950_ID);
    /* check device id */
    //tmp = i2c_read_reg(APDS9950_ADDRESS, APDS9950_ID);
    //if (tmp != APDS9950_ID_VALUE) return 1;

    i2c_write_reg(APDS9950_ADDRESS, APDS9950_COMMAND | APDS9950_ATIME, 0xff);
    i2c_write_reg(APDS9950_ADDRESS, APDS9950_COMMAND | APDS9950_WTIME, 0xff);
    i2c_write_reg(APDS9950_ADDRESS, APDS9950_COMMAND | APDS9950_CONFIG, 0);

    tmp = APDS9950_ENABLE_PON | APDS9950_ENABLE_AEN;
    i2c_write_reg(APDS9950_ADDRESS, APDS9950_COMMAND | APDS9950_ENABLE, tmp);

    tmp = APDS9950_CONTROL_AGAIN3;
    i2c_write_reg(APDS9950_ADDRESS, APDS9950_COMMAND | APDS9950_CONTROL, tmp);

    return 0;
}

void
apds9950_rgbc_read(struct sRgbcData *data)
{
    u16 tmp;

    i2cStart();
    i2cWrite(APDS9950_ADDRESS);
    i2cWrite(APDS9950_COMMAND | APDS9950_COMMAND_TYPE1 | APDS9950_CDATAL);

    i2cStart();
    i2cWrite(APDS9950_ADDRESS | 1);

    tmp = i2cRead(1);
    tmp |= (((u16)i2cRead(1)) << 8);
    data->c = tmp;

    tmp = i2cRead(1);
    tmp |= (((u16)i2cRead(1)) << 8);
    data->r = tmp;

    tmp = i2cRead(1);
    tmp |= (((u16)i2cRead(1)) << 8);
    data->g = tmp;

    tmp = i2cRead(1);
    tmp |= (((u16)i2cRead(0)) << 8);
    data->b = tmp;

    i2cStop();
}
