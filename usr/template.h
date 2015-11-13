#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "os/suzuha_os.h"


/* Application definitions required by os */

#define MAIN_THREAD_CALLBACK        main_thread
#define MAIN_THREAD_STACK           main_thread_stack
#define MAIN_THREAD_STACK_SIZE      sizeof(main_thread_stack)
#define MAIN_THREAD_PRIORITY        (PRIORITY_MAX + 2)

thread_stack_t main_thread_stack[128];
void main_thread();


/* Other */

#define USER_THREAD_STACK_SIZE	     (128)


void led_blink_thread();


#endif /* _TEMPLATE_H_ */
