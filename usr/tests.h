#ifndef _TESTS_H_
#define _TESTS_H_

#include "os/suzuha_os.h"


#define THREAD_STACK_SIZE           (128)

thread_stack_t main_thread_stack[THREAD_STACK_SIZE];
thread_stack_t test_thread_stack[THREAD_STACK_SIZE];

#define TEST_COUNT                  (4)


void main_thread();

void ss_test_thread();
void imu_test_thread();
void ss_error_test_thread();
void motor_test_thread();


#endif /* _TESTS_H_ */
