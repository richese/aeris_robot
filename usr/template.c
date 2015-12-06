#include "template.h"

#include "os/suzuha_os.h"
#include "lib_usr/aeris_robot/aeris_robot.h"


thread_stack_t led_blink_thread_stack[USER_THREAD_STACK_SIZE];


void
main_thread()
{
    printf_(OS_WELCOME_MESSAGE);
    aeris_init();

    create_thread(led_blink_thread, led_blink_thread_stack,
                  sizeof(led_blink_thread_stack), PRIORITY_MIN);

    while (1) {
        aeris_rgbw_set(AERIS_LED_R);
        printf_("Red: On\n");
        timer_delay_ms(5000);

        aeris_rgbw_reset(AERIS_LED_R);
        printf_("Red: Off\n");
        timer_delay_ms(2500);
    }
}

void
led_blink_thread()
{
    while (1) {
        aeris_rgbw_set(AERIS_LED_G);
        printf_("Green: On\n");
        timer_delay_ms(1000);

        aeris_rgbw_reset(AERIS_LED_G);
        printf_("Green: Off\n");
        timer_delay_ms(1000);
    }
}
