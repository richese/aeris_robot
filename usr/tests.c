#include "tests.h"

#include "os/suzuha_os.h"
#include "lib_usr/aeris_robot/aeris_robot.h"
#include "lib_usr/math.h"


thread_stack_t test_thread_stack[USER_THREAD_STACK_SIZE];

u32 g_stop_test = 0;


void
main_thread()
{
    printf_(OS_WELCOME_MESSAGE);
    aeris_init();

    u32 current_test = DEFAULT_TEST;
    u32 thread_id = 0;

    while (1) {
        g_stop_test = 0;

        switch (current_test) {
        case TEST_SURFACE_SENSOR:
            thread_id = create_thread(ss_test_thread, test_thread_stack,
                          sizeof(test_thread_stack), PRIORITY_MAX);
            break;

        case TEST_SURFACE_SENSOR_ERRORS:
            thread_id = create_thread(ss_error_test_thread, test_thread_stack,
                          sizeof(test_thread_stack), PRIORITY_MAX);
            break;

        case TEST_IMU:
            thread_id = create_thread(imu_test_thread, test_thread_stack,
                          sizeof(test_thread_stack), PRIORITY_MAX);
            break;

        case TEST_MOTORS:
            thread_id = create_thread(motor_test_thread, test_thread_stack,
                          sizeof(test_thread_stack), PRIORITY_MAX);
            break;

        default:
            aeris_error(2);
        }

        timer_delay_ms(250);
        while (aeris_key_state() != AERIS_KEY_PRESSED && g_stop_test == 0) {
            yield();
        }
        g_stop_test = 1;
        join(thread_id);
        current_test = (current_test + 1) % TEST_COUNT;
    }

    aeris_error(3);
}

void
ss_test_thread()
{
    struct sRgbcData raw[AERIS_SS_COUNT];

    printf_("Starting surface sensors test.\n");
    timer_delay_ms(1000);

    aeris_rgbw_set(AERIS_LED_W);

    event_timer_set_period(SS_PRINT_TIMER_ID, (SS_PRINT_TIMER_PERIOD>>2));

    while(!g_stop_test) {
        event_timer_wait(SS_PRINT_TIMER_ID);

        aeris_rgbw_set(AERIS_LED_G);
        for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
            aeris_surface_sensor_read_raw(i, &raw[i]);
        }

        printf_("\n\ntime = %u\n", (u32)timer_get_time());
        for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
            printf_("[%u %u %u %u]\n", raw[i].c, raw[i].r, raw[i].g, raw[i].b);
        }

        aeris_rgbw_reset(AERIS_LED_G);
    }

    aeris_rgbw_reset(AERIS_LED_G | AERIS_LED_W);
}

void
imu_test_thread()
{
    struct sAerisIMU imu;

    printf_("Starting imu test.\n");
    timer_delay_ms(1000);

    while(!g_stop_test) {

        aeris_rgbw_set(AERIS_LED_G);
        aeris_imu_read(&imu);
        aeris_rgbw_reset(AERIS_LED_G);

        printf_("a = [%i, %i, %i]\n", imu.ax, imu.ay, imu.az);
        printf_("m = [%i, %i, %i]\n", imu.mx, imu.my, imu.mz);
        printf_("g = [%i, %i, %i]\n", imu.gx, imu.gy, imu.gz);
        printf_("gh = %i mh = %i\n", (i32)(m_atan2(imu.ax, imu.az)*180.0/PI_),
                (i32)(m_atan2(imu.my, imu.mx)*180.0/PI_));
        printf_("\n\n");

        timer_delay_ms(100);
    }

    aeris_rgbw_reset(AERIS_LED_G);
}

void
ss_error_test_thread()
{
    struct sRgbcData raw;
    u32 total_tests = 0;
    u32 reset_cnt[AERIS_SS_COUNT];
    u32 error_cnt[AERIS_SS_COUNT][4]; // 128 bytes

    for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
        reset_cnt[i] = 0;
        for (u32 j = 0; j < 4; j++) error_cnt[i][j] = 0;
    }

    printf_("Starting surface sensors error rate test.\n");
    timer_delay_ms(1000);

    aeris_rgbw_set(AERIS_LED_W);

    event_timer_set_period(SS_SAMPLING_TIMER_ID, SS_SAMPLING_TIMER_PERIOD);
    event_timer_set_period(SS_PRINT_TIMER_ID, SS_PRINT_TIMER_PERIOD);

    while(!g_stop_test) {
        event_timer_wait(SS_SAMPLING_TIMER_ID);
        total_tests++;

        for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
            aeris_surface_sensor_read_raw(i, &raw);
            if (ss_has_high_error(raw.c) ||
                ss_has_high_error(raw.r) ||
                ss_has_high_error(raw.g) ||
                ss_has_high_error(raw.b)) {

                //aeris_surface_sensor_init(i);
                //aeris_surface_sensor_read_raw(i, &raw);
                reset_cnt[i] += 1;
            }

            error_cnt[i][0] += ss_has_high_error(raw.c);
            error_cnt[i][1] += ss_has_high_error(raw.r);
            error_cnt[i][2] += ss_has_high_error(raw.g);
            error_cnt[i][3] += ss_has_high_error(raw.b);
        }

        if (event_timer_get_flag(SS_PRINT_TIMER_ID)) {
            event_timer_clear_flag(SS_PRINT_TIMER_ID);

            printf_("time=%u test_count=%u\n", timer_get_time(), total_tests);
            for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
                printf_("[%u] [%u %u %u %u]\n", reset_cnt[i],
                        error_cnt[i][0], error_cnt[i][1],
                        error_cnt[i][2], error_cnt[i][3]);
            }
            printf_("\n\n");
        }
        timer_delay_ms(4);
    }

    aeris_rgbw_reset(AERIS_LED_W);
}

void
motor_test_thread()
{
    struct sAerisMotors speed[4] = {
        {40, 40},
        {0, 0},
        {-40, -40},
        {0, 0}
    };
    u32 i = 0;
    u32 speed_count = 4;

    aeris_rgbw_reset(AERIS_LED_B);
    printf_("Starting motor test.\n");
    timer_delay_ms(1000);

    while (!g_stop_test) {
        aeris_motors_set(speed[i]);
        aeris_rgbw_toggle(AERIS_LED_B);
        printf_("speed = [%i, %i]\n", speed[i].left, speed[i].right);
        i = (i + 1) % speed_count;
        timer_delay_ms(800);
    }

    aeris_rgbw_reset(AERIS_LED_B);
    aeris_motors_seti(0, 0);
}
