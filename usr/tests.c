#include "tests.h"

#include "os/suzuha_os.h"
#include "lib_usr/aeris_robot/aeris_robot.h"


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
        while (aeris_read_key() == 0) yield();
        g_stop_test = 1;
        join(thread_id);
        current_test = (current_test + 1) % TEST_COUNT;
    }

    aeris_error(3);
}

void
ss_test_thread()
{
    printf_("Starting surface sensors test.\n");
    timer_delay_ms(1000);

    g_aeris_robot.rgbw.w = 1;
    aeris_set_rgbw();

    while(!g_stop_test) {
        g_aeris_robot.rgbw.g = 1;
        aeris_set_rgbw();

        aeris_read_surface_sensors();

        g_aeris_robot.rgbw.g = 0;
        aeris_set_rgbw();

        aeris_print_ss_data();
        printf_("\n");

        timer_delay_ms(10);
    }

    g_aeris_robot.rgbw.w = 0;
    aeris_set_rgbw();
}

void
imu_test_thread()
{
    printf_("Starting imu test.\n");
    timer_delay_ms(1000);

    while(!g_stop_test) {
        g_aeris_robot.rgbw.g = 1;
        aeris_set_rgbw();

        aeris_read_imu();

        g_aeris_robot.rgbw.g = 0;
        aeris_set_rgbw();

        aeris_print_imu_data();
        printf_("\n\n");

        timer_delay_ms(100);
    }
}

static void
ss_error_print(u32 low_error[AERIS_SS_COUNT][4],
               u32 high_error[AERIS_SS_COUNT][4], u32 total_tests)
{
    printf_("test_count=%u\n", total_tests);
    for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
        printf_("[%u %u %u %u] ",
                low_error[i][0], low_error[i][1],
                low_error[i][2], low_error[i][3]);
        printf_("[%u %u %u %u]\n",
                high_error[i][0], high_error[i][1],
                high_error[i][2], high_error[i][3]);
    }
    printf_("\n\n");
}

void
ss_error_test_thread()
{
    printf_("Starting surface sensors error rate test.\n");

    struct sAerisSurfaceSensors *sensor = &g_aeris_robot.surface_sensors;
    u32 total_tests = 0;
    u32 high_error[AERIS_SS_COUNT][4];
    u32 low_error[AERIS_SS_COUNT][4];

    timer_delay_ms(1000);

    for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
        for (u32 j = 0; j < 4; j++) high_error[i][j] = 0;
    }
    for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
        for (u32 j = 0; j < 4; j++) low_error[i][j] = 0;
    }

    g_aeris_robot.rgbw.w = 1;
    aeris_set_rgbw();

    event_timer_set_period(SS_ERROR_TIMER_ID, SS_ERROR_TIMER_PERIOD);

    while(!g_stop_test) {
        aeris_read_surface_sensors();
        total_tests++;

        for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
            high_error[i][0] += ss_has_high_error(sensor->r[i], SS_ERROR_TRESHOLD_HIGH);
            high_error[i][1] += ss_has_high_error(sensor->g[i], SS_ERROR_TRESHOLD_HIGH);
            high_error[i][2] += ss_has_high_error(sensor->b[i], SS_ERROR_TRESHOLD_HIGH);
            high_error[i][3] += ss_has_high_error(sensor->w[i], SS_ERROR_TRESHOLD_HIGH);
            low_error[i][0] += ss_has_low_error(sensor->r[i], SS_ERROR_TRESHOLD_LOW);
            low_error[i][1] += ss_has_low_error(sensor->g[i], SS_ERROR_TRESHOLD_LOW);
            low_error[i][2] += ss_has_low_error(sensor->b[i], SS_ERROR_TRESHOLD_LOW);
            low_error[i][3] += ss_has_low_error(sensor->w[i], SS_ERROR_TRESHOLD_LOW);
        }

        if (event_timer_get_flag(SS_ERROR_TIMER_ID)) {
            event_timer_clear_flag(SS_ERROR_TIMER_ID);
            ss_error_print(low_error, high_error, total_tests);
        }
        timer_delay_ms(1);
    }

    g_aeris_robot.rgbw.w = 0;
    aeris_set_rgbw();
}

void
motor_test_thread()
{
    printf_("Starting motor test.\n");
    timer_delay_ms(1000);

    while (!g_stop_test) {
        g_aeris_robot.rgbw.b = 1;
        aeris_set_rgbw();

        g_aeris_robot.motors.left = 40;
        g_aeris_robot.motors.right = 40;
        aeris_set_motors();
        printf_("speed = [%i, %i]\n", g_aeris_robot.motors.left,
                g_aeris_robot.motors.right);
        timer_delay_ms(800);

        g_aeris_robot.rgbw.b = 0;
        aeris_set_rgbw();

        g_aeris_robot.motors.left = 0;
        g_aeris_robot.motors.right = 0;
        printf_("speed = [%i, %i]\n", g_aeris_robot.motors.left,
                g_aeris_robot.motors.right);
        aeris_set_motors();
        timer_delay_ms(800);
    }
}
