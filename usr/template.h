#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "os/suzuha_os.h"


#define THREAD_STACK_SIZE	128

/* Required */
thread_stack_t main_thread_stack[THREAD_STACK_SIZE];

thread_stack_t led_blink_thread_stack[THREAD_STACK_SIZE];

/* Required */
void main_thread();

void led_blink_thread();


#endif /* _TEMPLATE_H_ */
