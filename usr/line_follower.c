#include "line_follower.h"

#include "os/suzuha_os.h"
#include "lib_usr/aeris_robot/aeris_robot.h"
#include "lib_usr/aeris_robot/line_sensor.h"


void
main_thread()
{
    printf_(OS_WELCOME_MESSAGE);
    aeris_init();

    // event_timer_set_period(DEBUG_MSG_TIMER_ID, DEBUG_MSG_TIMER_PERIOD);
    //
    // float e0 = 0.0;
    // float e1 = 0.0;
    //
    // float kp = 16.0;
    // float kd = 40.0;
    //
    // i32 b_speed = 20;
    // i32 dif_speed = 0;

    while (1)
    {
        // g_aeris_robot.rgbw.g = 1;
        // aeris_set_rgbw();
        //
        // // aeris_read_surface_sensors();
        //
        // g_aeris_robot.rgbw.g = 0;
        // aeris_set_rgbw();
        //
        // //read_line_position();
        // e1 = e0;
        // e0 = 0 - g_line_position.line_position;
        //
        // dif_speed = kp*e0 + kd*(e0 - e1);
        //
        // //i32 left_speed = b_speed + dif_speed;
        // //i32 right_speed = b_speed - dif_speed;
        //
        // //g_aeris_robot.motors.left = left_speed;
        // //g_aeris_robot.motors.right = right_speed;
        // //aeris_set_motors();
        //
        // if (event_timer_get_flag(DEBUG_MSG_TIMER_ID)) {
        //     event_timer_clear_flag(DEBUG_MSG_TIMER_ID);
        //     //aeris_print_ss_data();
        // }
    }
}
