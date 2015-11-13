#ifndef _LINE_FOLLOWER_H_
#define _LINE_FOLLOWER_H_

#include "os/suzuha_os.h"


/* Application definitions required by os */

#define MAIN_THREAD_CALLBACK        main_thread
#define MAIN_THREAD_STACK           main_thread_stack
#define MAIN_THREAD_STACK_SIZE      sizeof(main_thread_stack)
#define MAIN_THREAD_PRIORITY        PRIORITY_MAX

thread_stack_t main_thread_stack[128];
void main_thread();


/* Other */

#define DEBUG_MSG_TIMER_ID      EVENT_TIMER_0_ID
#define DEBUG_MSG_TIMER_PERIOD  (4096)


#endif /* _LINE_FOLLOWER_H_ */
