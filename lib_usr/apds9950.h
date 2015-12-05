#ifndef _APDS9950_H_
#define _APDS9950_H_

#include "device/device.h"

/* APDS-9950  Digital Proximity, RGB and Ambient Light Sensor */


#define APDS9950_ADDRESS                (0x72)

/* APDS9950 I2C registers */
#define APDS9950_COMMAND                (0x80) /* Select command register */
#define APDS9950_ENABLE                 (0x00) /* Enable of states amd interrupts */
#define APDS9950_ATIME                  (0x01) /* RGBC time */
#define APDS9950_WTIME                  (0x03) /* Wait time */
#define APDS9950_AILTL                  (0x04) /* Clear interrupt low treshold low byte */
#define APDS9950_AILTH                  (0x05) /* Clear interrupt low treshold high byte */
#define APDS9950_AIHTL                  (0x06) /* Clear interrupt high treshold low byte */
#define APDS9950_AIHTH                  (0x07) /* Clear interrupt high treshold high byte */
#define APDS9950_PILTL                  (0x08) /* Proximity interrupt low treshold low byte */
#define APDS9950_PILTH                  (0x09) /* Proximity interrupt low treshold high byte */
#define APDS9950_PIHTL                  (0x0a) /* Proximity interrupt high treshold low byte */
#define APDS9950_PIHTH                  (0x0b) /* Proximity interrupt high treshold high byte */
#define APDS9950_PERS                   (0x0c) /* Interrupt persistence filters */
#define APDS9950_CONFIG                 (0x0d) /* Configuration */
#define APDS9950_PPULSE                 (0x0e) /* Proximity pulse count */
#define APDS9950_CONTROL                (0x0f) /* Gain control register */
#define APDS9950_ID                     (0x12) /* Device ID */
#define APDS9950_STATUS                 (0x13) /* Device status */
#define APDS9950_CDATAL                 (0x14) /* Clear ADC low data register */
#define APDS9950_CDATAH                 (0x15) /* Clear ADC high data register */
#define APDS9950_RDATAL                 (0x16) /* Red ADC low data register */
#define APDS9950_RDATAH                 (0x17) /* Red ADC high data register */
#define APDS9950_GDATAL                 (0x18) /* Green ADC low data register */
#define APDS9950_GDATAH                 (0x19) /* Green ADC high data register */
#define APDS9950_BDATAL                 (0x1a) /* Blue ADC low data register */
#define APDS9950_BDATAH                 (0x1b) /* Blue ADC high data register */
#define APDS9950_PDATAL                 (0x1c) /* Proximity ADC low data register */
#define APDS9950_PDATAH                 (0x1d) /* Proximity ADC high data register */


/* Command register bit definitions */
#define APDS9950_COMMAND_ADD0           (0x00)
#define APDS9950_COMMAND_ADD1           (0x05)
#define APDS9950_COMMAND_ADD2           (0x06)
#define APDS9950_COMMAND_ADD3           (0x07)
#define APDS9950_COMMAND_TYPE0          (0x00)
#define APDS9950_COMMAND_TYPE1          (0x20)
#define APDS9950_COMMAND_TYPE2          (0x40)
#define APDS9950_COMMAND_TYPE3          (0x60)

/* Enable register bit definitions */
#define APDS9950_ENABLE_PON             (0x01)
#define APDS9950_ENABLE_AEN             (0x02)
#define APDS9950_ENABLE_PEN             (0x04)
#define APDS9950_ENABLE_WEN             (0x08)
#define APDS9950_ENABLE_AIEN            (0x10)
#define APDS9950_ENABLE_PIEN            (0x20)

/* Configuration register bit definitions */
#define APDS9950_CONFIG_WLONG           (0x01)

/* Control register bit definitions */
#define APDS9950_CONTROL_AGAIN0         (0x00) /* 1x RGBC Gain value */
#define APDS9950_CONTROL_AGAIN1         (0x01) /* 4x RGBC Gain value */
#define APDS9950_CONTROL_AGAIN2         (0x02) /* 16x RGBC Gain value */
#define APDS9950_CONTROL_AGAIN3         (0x03) /* 60x RGBC Gain value */
#define APDS9950_CONTROL_PGAIN0         (0x00) /* 1x Proximity gain (only) */
#define APDS9950_CONTROL_PDIODE         (0x20) /* Proximity uses the IR diode */
#define APDS9950_CONTROL_PDRIVE0        (0x00) /* 100 mA Proximity led drive strength */
#define APDS9950_CONTROL_PDRIVE1        (0x40) /* 50 mA Proximity led drive strength */
#define APDS9950_CONTROL_PDRIVE2        (0x80) /* 25mA Proximity led drive strength */
#define APDS9950_CONTROL_PDRIVE3        (0xc0) /* 12.5 mA Proximity led drive strength */

/* ID register value */
#define APDS9950_ID_VALUE               (0x69) /* Part number identification */

/* Status register bit definitions */
#define APDS9950_STATUS_AVALID          (0x01)
#define APDS9950_STATUS_PVALID          (0x02)
#define APDS9950_STATUS_AINT            (0x10)
#define APDS9950_STATUS_PINT            (0x20)


struct sRgbcData
{
    u16 c;
    u16 r;
    u16 g;
    u16 b;
};


u32 apds9950_rgbc_init(void);
void apds9950_rgbc_read(struct sRgbcData *data);


#endif /* _APDS9950_H_ */
