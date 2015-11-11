#include "template.h"

#include "os/suzuha_os.h"
#include "lib_usr/aeris_robot/aeris_robot.h"


void
main_thread()
{
	printf_(OS_WELCOME_MESSAGE);

	aeris_init();

	create_thread(led_blink_thread, led_blink_thread_stack,
		          sizeof(led_blink_thread_stack), PRIORITY_MIN);

	while (1) {
		g_aeris_robot.rgbw.r = 1;
		aeris_set_rgbw();
		timer_delay_ms(5000);

		g_aeris_robot.rgbw.r = 0;
		aeris_set_rgbw();
		timer_delay_ms(2500);
	}
}

void
led_blink_thread()
{
	while (1) {
		g_aeris_robot.rgbw.g = 1;
		aeris_set_rgbw();
		timer_delay_ms(1000);

		g_aeris_robot.rgbw.g = 0;
		aeris_set_rgbw();
		timer_delay_ms(1000);
	}
}
