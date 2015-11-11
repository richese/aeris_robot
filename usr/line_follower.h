#ifndef _LINE_FOLLOWER_H_
#define _LINE_FOLLOWER_H_

#include "os/suzuha_os.h"


#define THREAD_STACK_SIZE	128


thread_stack_t main_thread_stack[THREAD_STACK_SIZE];


void main_thread();


#endif /* _LINE_FOLLOWER_H_ */
