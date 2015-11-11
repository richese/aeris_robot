#ifndef _TESTS_H_
#define _TESTS_H_

#include "os/suzuha_os.h"


#define THREAD_STACK_SIZE           (128)
#define TEST_COUNT                  (4)

enum {
    TEST_SURFACE_SENSOR = 0,
    TEST_IMU_DATA,
    TEST_SURFACE_SENSOR_ERRORS,
    TEST_MOTORS,
};


thread_stack_t main_thread_stack[THREAD_STACK_SIZE];
thread_stack_t test_thread_stack[THREAD_STACK_SIZE];


void main_thread();
void ss_test_thread();
void imu_test_thread();
void ss_error_test_thread();
void motor_test_thread();


#endif /* _TESTS_H_ */
