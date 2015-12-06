#include "apds9950.h"


u32
apds9950_rgbc_init(u8 atime, u8 wtime, u8 rgbc_gain)
{
    u8 val;

    apds9950_read_reg(APDS9950_ID);

    val = apds9950_read_reg(APDS9950_ID);
    if (val != APDS9950_ID_VALUE) return 1;

    val = atime;
    apds9950_write_reg(APDS9950_ATIME, val);
    if (apds9950_read_reg(APDS9950_ATIME) != val) return 2;

    val = wtime;
    apds9950_write_reg(APDS9950_WTIME, val);
    if (apds9950_read_reg(APDS9950_WTIME) != val) return 3;

    val = 0x00;
    apds9950_write_reg(APDS9950_CONFIG, 0);
    if (apds9950_read_reg(APDS9950_CONFIG) != val) return 4;

    val = rgbc_gain;
    apds9950_write_reg(APDS9950_CONTROL, val);
    if (apds9950_read_reg(APDS9950_CONTROL) != val) return 5;

    val = APDS9950_ENABLE_PON | APDS9950_ENABLE_AEN;
    apds9950_write_reg(APDS9950_ENABLE, val);
    if (apds9950_read_reg(APDS9950_ENABLE) != val) return 6;

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

u8
apds9950_read_reg(u8 reg)
{
    u8 val;

    i2cStart();
    i2cWrite(APDS9950_ADDRESS);
    i2cWrite(APDS9950_COMMAND | reg);
    i2cStart();
    i2cWrite(APDS9950_ADDRESS | 1);
    val = i2cRead(0);
    i2cStop();

    return val;
}

void
apds9950_write_reg(u8 reg, u8 val)
{
    i2c_write_reg(APDS9950_ADDRESS, (APDS9950_COMMAND | reg), val);
}
