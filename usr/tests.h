#ifndef _TESTS_H_
#define _TESTS_H_

#include "os/suzuha_os.h"


/* Application definitions required by os */

#define MAIN_THREAD_CALLBACK            main_thread
#define MAIN_THREAD_STACK               main_thread_stack
#define MAIN_THREAD_STACK_SIZE          sizeof(main_thread_stack)
#define MAIN_THREAD_PRIORITY            (PRIORITY_MAX + 2)

thread_stack_t main_thread_stack[128];
void main_thread();


/* Test configuration */

#define USER_THREAD_STACK_SIZE          (512)

#define TEST_SURFACE_SENSOR_ERRORS      (0)
#define TEST_SURFACE_SENSOR             (1)
#define TEST_IMU                        (2)
#define TEST_MOTORS                     (3)

#define TEST_COUNT                      (4)
#define DEFAULT_TEST                    TEST_SURFACE_SENSOR_ERRORS


#define SS_SAMPLING_TIMER_ID            (0)
#define SS_SAMPLING_TIMER_PERIOD        (100) /* 10 ms */
#define SS_PRINT_TIMER_ID               (1)
#define SS_PRINT_TIMER_PERIOD           (10000) /* 1 s */

#define SS_ERROR_TRESHOLD               (1025)
#define ss_has_high_error(v)            ((v >= SS_ERROR_TRESHOLD) ? 1 : 0)

void ss_test_thread();
void imu_test_thread();
void ss_error_test_thread();
void motor_test_thread();


#endif /* _TESTS_H_ */
