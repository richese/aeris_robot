#include "tests.h"

#include "os/suzuha_os.h"
#include "lib_usr/aeris_robot/aeris_robot.h"


u32 g_stop_test = 0;


void
main_thread()
{
	printf_(OS_WELCOME_MESSAGE);

	aeris_init();

	u32 current_test = 0;
	u32 thread_id = 0;

	while (1) {
		g_stop_test = 0;

		switch (current_test) {
		case 0:
			create_thread(ss_test_thread, test_thread_stack,
				          sizeof(test_thread_stack), PRIORITY_MAX);
			break;

		case 1:
			create_thread(imu_test_thread, test_thread_stack,
				          sizeof(test_thread_stack), PRIORITY_MAX);
			break;

		case 2:
			create_thread(ss_error_test_thread, test_thread_stack,
				          sizeof(test_thread_stack), PRIORITY_MAX);
			break;
		case 3:
			create_thread(motor_test_thread, test_thread_stack,
				          sizeof(test_thread_stack), PRIORITY_MAX);
			break;

		default:
			aeris_error(2);
		}

		while (aeris_read_key()) yield();
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

	while(!g_stop_test) {
		g_aeris_robot.rgbw.g = 1;
		aeris_set_rgbw();

		aeris_read_surface_sensors();

		g_aeris_robot.rgbw.g = 0;
		aeris_set_rgbw();

		aeris_print_ss_data();
		printf_("\n\n" );

		timer_delay_ms(100);
	}
}

void
imu_test_thread()
{
	printf_("Starting imu test.\n");

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

void
ss_error_test_thread()
{
	printf_("Starting surface sensors error rate test.\n");

	while(!g_stop_test) {
		printf_("Not implemented yet.\n");
		timer_delay_ms(1000);
	}
}

void
motor_test_thread()
{
	printf_("Starting motor test.\n");

	while (!g_stop_test) {
		g_aeris_robot.rgbw.b = 1;
		aeris_set_rgbw();

		g_aeris_robot.motors.left = 40;
		g_aeris_robot.motors.right = 40;
		aeris_set_motors();
		printf_("speed = [%d, %d]\n", g_aeris_robot.motors.left,
		        g_aeris_robot.motors.right);
		timer_delay_ms(800);

		g_aeris_robot.rgbw.b = 0;
		aeris_set_rgbw();

		g_aeris_robot.motors.left = 0;
		g_aeris_robot.motors.right = 0;
		printf_("speed = [%d, %d]\n", g_aeris_robot.motors.left,
		        g_aeris_robot.motors.right);
		aeris_set_motors();
		timer_delay_ms(800);
	}
}
