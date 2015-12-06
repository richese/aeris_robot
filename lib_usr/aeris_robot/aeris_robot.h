#ifndef _AERIS_ROBOT_H_
#define _AERIS_ROBOT_H_

#include "device/device.h"
#include "os/suzuha_os.h"

#include "aeris_error.h"
#include "lib_usr/apds9950.h"
#include "lib_usr/lsm9ds0.h"
#include "lib_usr/pca9548.h"


///-----------------------------------------------------------------------------
///
/// Aeris robot low level library
///
///-----------------------------------------------------------------------------


///-----------------------------------------------------------------------------
///
/// Main Board pin definitions
///
///-----------------------------------------------------------------------------


/* Motor pin definitions */
#define AERIS_MOTORS_M1_GPIO_BASE       GPIOC
#define AERIS_MOTORS_M1                 (0x0002)

#define AERIS_MOTORS_APHASE_GPIO_BASE   GPIOC
#define AERIS_MOTORS_APHASE             (0x0004)

#define AERIS_MOTORS_BPHASE_GPIO_BASE   GPIOC
#define AERIS_MOTORS_BPHASE             (0x0008)

#define AERIS_MOTORS_A_PWM_GPIO_BASE    GPIOA
#define AERIS_MOTORS_A_PWM              (0x0001)

#define AERIS_MOTORS_B_PWM_GPIO_BASE    GPIOA
#define AERIS_MOTORS_B_PWM              (0x0002)

/* RGB led pin definitions */
#define AERIS_RGB_GPIO_BASE             GPIOB

#define AERIS_RGB_LED_1                 (0x0010)
#define AERIS_RGB_LED_2                 (0x0020)
#define AERIS_RGB_LED_3                 (0x0040)
#define AERIS_RGB_LED_MASK              (0x0070)

/* Push button pin definitions */
#define AERIS_KEY_GPIO_BASE             GPIOB

#define AERIS_KEY_1                     (0x0400)

/// Connected sensor board pin definitions

/* White surface led pin definitions */
#define AERIS_WHITE_LED_GPIO_BASE       GPIOC

#define AERIS_WHITE_LED                 (0x0020)

/* PCA9548 reset pin */
#define AERIS_PCA9548_RESET_GPIO_BASE   PCA9548_RESET_GPIO_BASE

#define AERIS_PCA9548_RESET             PCA9548_RESET_GPIO_PIN


///-----------------------------------------------------------------------------
///
/// Aeris robot API
///
///-----------------------------------------------------------------------------


u32 aeris_init(void);


/* Motor API */
#define AERIS_MOTORS_PWM_BASE_CLOCK     SystemCoreClock /* defined by device */
#define AERIS_MOTORS_PWM_FREQUENCY      (10000)
#define AERIS_MOTORS_PWM_PERIOD         ((SystemCoreClock/AERIS_MOTORS_PWM_FREQUENCY) - 1)

#define AERIS_MOTORS_MAX_SPEED          ((i32)100)

struct sAerisMotors
{
    i32 left;
    i32 right;
};

void aeris_motors_set(struct sAerisMotors speed);
void aeris_motors_seti(i32 left, i32 right);
struct sAerisMotors aeris_motors_state(void);


/* Leds API */
#define AERIS_LED_R                     AERIS_RGB_LED_1
#define AERIS_LED_G                     AERIS_RGB_LED_2
#define AERIS_LED_B                     AERIS_RGB_LED_3
#define AERIS_LED_W                     (AERIS_WHITE_LED>>4)
#define AERIS_LED_ALL                   (0x72)

void aeris_rgbw_set(u16 leds);
void aeris_rgbw_reset(u16 leds);
void aeris_rgbw_toggle(u16 leds);
u16 aeris_rgbw_state(void);


/* Button API */
#define AERIS_KEY_PRESSED               (0x01)

u8 aeris_key_state(void);


/* IMU API */

struct sAerisIMU
{
    i16 roll, pitch, yaw;

    i16 ax, ay, az;
    i16 mx, my, mz;
    i16 gx, gy, gz;

    i16 temp;
};

// TODO:
void aeris_imu_read(struct sAerisIMU *data);

/* Surface sensors API */

#define AERIS_SS_COUNT                  ((u32)8)

#define AERIS_SS_FRONT_LEFT             ((u32)0)
#define AERIS_SS_FRONT_LEFT_CENTER      ((u32)1)
#define AERIS_SS_FRONT_RIGHT_CENTER     ((u32)2)
#define AERIS_SS_FRONT_RIGHT            ((u32)3)
#define AERIS_SS_REAR_LEFT              ((u32)4)
#define AERIS_SS_REAR_LEFT_CENTER       ((u32)5)
#define AERIS_SS_REAR_RIGHT_CENTER      ((u32)6)
#define AERIS_SS_REAR_RIGHT             ((u32)7)

// defines which sensors are actually soldered on PCB
// disabled sensors always read zeros
#define AERIS_SS_ENABLE                 ((u32)0x0000009f)

u32 aeris_surface_sensor_init(u32 id);
void aeris_surface_sensor_read_raw(u32 id, struct sRgbcData *raw);


#endif /* _AERIS_ROBOT_H_ */
