#include "aeris_robot.h"
#include "aeris_error.h"

#include "lib_usr/apds9950.h"
#include "lib_usr/lsm9ds0.h"
#include "lib_usr/pca9548.h"


struct sAerisRobot
{
    struct sAerisMotors motors;
};

static struct sAerisRobot g_aeris;


u32
aeris_init(void)
{
    u32 tmp;
    GPIO_InitTypeDef pin_init;
    TIM_TimeBaseInitTypeDef timer_init;

    /* Initialize g_aeris structure */
    g_aeris.motors.left = 0;
    g_aeris.motors.right = 0;


    /* Motor init */

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    // init M1 pin
    pin_init.GPIO_Pin = AERIS_MOTORS_M1;
    pin_init.GPIO_Mode = GPIO_Mode_OUT;
    pin_init.GPIO_Speed = GPIO_Speed_100MHz;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(AERIS_MOTORS_M1_GPIO_BASE, &pin_init);
    GPIO_SetBits(AERIS_MOTORS_M1_GPIO_BASE, AERIS_MOTORS_M1);

    // init A_PHASE pin
    pin_init.GPIO_Pin = AERIS_MOTORS_APHASE;
    pin_init.GPIO_Mode = GPIO_Mode_OUT;
    pin_init.GPIO_Speed = GPIO_Speed_100MHz;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(AERIS_MOTORS_APHASE_GPIO_BASE, &pin_init);
    GPIO_ResetBits(AERIS_MOTORS_APHASE_GPIO_BASE, AERIS_MOTORS_APHASE);

    // init B_PHASE pin
    pin_init.GPIO_Pin = AERIS_MOTORS_BPHASE;
    pin_init.GPIO_Mode = GPIO_Mode_OUT;
    pin_init.GPIO_Speed = GPIO_Speed_100MHz;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(AERIS_MOTORS_BPHASE_GPIO_BASE, &pin_init);
    GPIO_ResetBits(AERIS_MOTORS_BPHASE_GPIO_BASE, AERIS_MOTORS_BPHASE);

    // init A_PWM pin
    pin_init.GPIO_Pin = AERIS_MOTORS_A_PWM;
    pin_init.GPIO_Mode = GPIO_Mode_AF;
    pin_init.GPIO_Speed = GPIO_Speed_50MHz;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(AERIS_MOTORS_A_PWM_GPIO_BASE, &pin_init);
    GPIO_PinAFConfig(AERIS_MOTORS_A_PWM_GPIO_BASE, GPIO_PinSource0, GPIO_AF_TIM5);

    // init B_PWM pin
    pin_init.GPIO_Pin = AERIS_MOTORS_B_PWM;
    pin_init.GPIO_Mode = GPIO_Mode_AF;
    pin_init.GPIO_Speed = GPIO_Speed_50MHz;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(AERIS_MOTORS_B_PWM_GPIO_BASE, &pin_init);
    GPIO_PinAFConfig(AERIS_MOTORS_B_PWM_GPIO_BASE, GPIO_PinSource1, GPIO_AF_TIM5);

    // init Timer 5
    timer_init.TIM_Prescaler = 0;
    timer_init.TIM_CounterMode = TIM_CounterMode_Up;
    timer_init.TIM_Period = AERIS_MOTORS_PWM_PERIOD;
    timer_init.TIM_ClockDivision = 0;
    timer_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM5, &timer_init);

    aeris_motors_seti(0, 0);

    TIM_Cmd(TIM5, ENABLE);
    TIM_CtrlPWMOutputs(TIM5, ENABLE);


    /* Led init */

    // RGB led pins
    pin_init.GPIO_Pin = AERIS_RGB_LED_MASK;
    pin_init.GPIO_Mode = GPIO_Mode_OUT;
    pin_init.GPIO_Speed = GPIO_Speed_100MHz;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(AERIS_RGB_GPIO_BASE, &pin_init);

    // White led pin
    pin_init.GPIO_Pin = AERIS_WHITE_LED;
    pin_init.GPIO_Mode = GPIO_Mode_OUT;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_Speed = GPIO_Speed_100MHz;
    pin_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(AERIS_WHITE_LED_GPIO_BASE, &pin_init);

    aeris_rgbw_reset(AERIS_LED_ALL);

    /* Button init */

    // Button pin
    pin_init.GPIO_Pin = AERIS_KEY_1;
    pin_init.GPIO_Mode = GPIO_Mode_IN;
    pin_init.GPIO_Speed = GPIO_Speed_50MHz;
    pin_init.GPIO_OType = GPIO_OType_PP;
    pin_init.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(AERIS_KEY_GPIO_BASE, &pin_init);

    /* I2C peripherals init */

    // IMU init
    tmp = lsm9ds0_init();
    if (tmp != 0)
        aeris_error(tmp);

    // I2C switch init
    pca9548_init();

    // RGB sensors init
    for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
        // 2x init to get out of possible bus fault condition after stm32f4 reset
        aeris_surface_sensor_init(i);
        if (aeris_surface_sensor_init(i) != 0) {
            aeris_error(i);
        }
    }

    // TODO: sensor board magnetometers

    return 0;
}

void
aeris_motors_set(struct sAerisMotors speed)
{
    i32 ch1 = 0;
    i32 ch2 = 0;

    if (speed.left < -AERIS_MOTORS_MAX_SPEED)
        speed.left = -AERIS_MOTORS_MAX_SPEED;

    if (speed.left > AERIS_MOTORS_MAX_SPEED)
        speed.left =  AERIS_MOTORS_MAX_SPEED;

    if (speed.right < -AERIS_MOTORS_MAX_SPEED)
        speed.right = -AERIS_MOTORS_MAX_SPEED;

    if (speed.right > AERIS_MOTORS_MAX_SPEED)
        speed.right = AERIS_MOTORS_MAX_SPEED;

    ch2 = speed.left;
    ch1 = speed.right;

    if (ch1 < 0) ch1 = -ch1;
    if (ch2 < 0) ch2 = -ch2;

    if (speed.left < 0)
        GPIO_SetBits(AERIS_MOTORS_APHASE_GPIO_BASE, AERIS_MOTORS_APHASE);
    else
        GPIO_ResetBits(AERIS_MOTORS_APHASE_GPIO_BASE, AERIS_MOTORS_APHASE);

    if (speed.right < 0)
        GPIO_SetBits(AERIS_MOTORS_BPHASE_GPIO_BASE, AERIS_MOTORS_BPHASE);
    else
        GPIO_ResetBits(AERIS_MOTORS_BPHASE_GPIO_BASE, AERIS_MOTORS_BPHASE);



    TIM_OCInitTypeDef  TIM_OCInitStructure;


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;


    TIM_OCInitStructure.TIM_Pulse = (ch1*(AERIS_MOTORS_PWM_PERIOD-1))/100;
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = (ch2*(AERIS_MOTORS_PWM_PERIOD-1))/100;
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);

    g_aeris.motors.left = speed.left;
    g_aeris.motors.right = speed.right;
}

void
aeris_motors_seti(i32 left, i32 right)
{
    struct sAerisMotors speed;
    speed.left = left;
    speed.right = right;
    aeris_motors_set(speed);
}

struct sAerisMotors
aeris_motors_state(void)
{
    return g_aeris.motors;
}

void
aeris_rgbw_set(u16 leds)
{
    u16 mask;

    mask = leds & AERIS_RGB_LED_MASK;
    if (mask != 0) {
        GPIO_ResetBits(AERIS_RGB_GPIO_BASE, mask);
    }

    mask = (leds<<4) & AERIS_WHITE_LED;
    if (mask != 0) {
        GPIO_SetBits(AERIS_WHITE_LED_GPIO_BASE,AERIS_WHITE_LED);
    }
}

void
aeris_rgbw_reset(u16 leds)
{
    u16 mask;

    mask = leds & AERIS_RGB_LED_MASK;
    if (mask != 0) {
        GPIO_SetBits(AERIS_RGB_GPIO_BASE, mask);
    }

    mask = (leds<<4) & AERIS_WHITE_LED;
    if (mask != 0) {
        GPIO_ResetBits(AERIS_WHITE_LED_GPIO_BASE,AERIS_WHITE_LED);
    }
}

void
aeris_rgbw_toggle(u16 leds)
{
    u16 mask;

    mask = leds & AERIS_RGB_LED_MASK;
    if (mask != 0) {
        GPIO_ToggleBits(AERIS_RGB_GPIO_BASE, mask);
    }

    mask = (leds<<4) & AERIS_WHITE_LED;
    if (mask != 0) {
        GPIO_ToggleBits(AERIS_WHITE_LED_GPIO_BASE,AERIS_WHITE_LED);
    }
}

u16
aeris_rgbw_state(void)
{
    u16 res = 0;
    res |= GPIO_ReadOutputData(AERIS_RGB_GPIO_BASE) & AERIS_RGB_LED_MASK;
    res |= ((GPIO_ReadOutputData(AERIS_WHITE_LED_GPIO_BASE) & AERIS_WHITE_LED)>>4);
    return res;
}

u8
aeris_key_state(void)
{
    if (GPIO_ReadInputDataBit(AERIS_KEY_GPIO_BASE, AERIS_KEY_1) == 0) {
        return AERIS_KEY_PRESSED;
    } else {
        return 0x00;
    }
}

void
aeris_imu_read(struct sAerisIMU *data)
{
    lsm9ds0_read();

    data->ax = g_lsm9ds0_imu.ax;
    data->ay = g_lsm9ds0_imu.ay;
    data->az = g_lsm9ds0_imu.az;

    data->mx = g_lsm9ds0_imu.mx;
    data->my = g_lsm9ds0_imu.my;
    data->mz = g_lsm9ds0_imu.mz;

    data->gx = g_lsm9ds0_imu.gx;
    data->gy = g_lsm9ds0_imu.gy;
    data->gz = g_lsm9ds0_imu.gz;

    data->temp = g_lsm9ds0_imu.temp;

    data->roll = 0;
    data->pitch = 0;
    data->yaw = 0;
}

u32
aeris_surface_sensor_init(u32 id)
{
    u32 res = 0;

    if ((1<<id) & AERIS_SS_ENABLE) {
        pca9548_set_bus(id);
        res = apds9950_rgbc_init(APDS9950_ATIME_FASTEST,
                                 APDS9950_WTIME_FASTEST,
                                 APDS9950_RGBC_GAIN_60X);
    }

    return res;
}

void
aeris_surface_sensor_read_raw(u32 id, struct sRgbcData *raw)
{
    if ((1<<id) & AERIS_SS_ENABLE) {
        pca9548_set_bus(id);
        apds9950_rgbc_read(raw);
    } else {
        raw->c = 0;
        raw->r = 0;
        raw->g = 0;
        raw->b = 0;
    }
}
