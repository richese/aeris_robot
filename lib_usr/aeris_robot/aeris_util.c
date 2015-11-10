#include "aeris_util.h"

#include "aeris_robot.h"
#include "line_sensor.h"
#include "../math.h"


// TODO move to its own target
void
aeris_line_folower_test()
{
    float e0 = 0.0;
    float e1 = 0.0;

    float kp = 16.0;
    float kd = 40.0;

    i32 b_speed = 20;
    i32 dif_speed = 0;

    while (1)
    {
        g_aeris_robot.rgbw.g = 1;
        aeris_set_rgbw();

        aeris_read_surface_sensors();

        g_aeris_robot.rgbw.g = 0;
        aeris_set_rgbw();

        read_line_position();
        e1 = e0;
        e0 = 0 - g_line_position.line_position;

        dif_speed = kp*e0 + kd*(e0 - e1);

        i32 left_speed = b_speed + dif_speed;
        i32 right_speed = b_speed - dif_speed;

        g_aeris_robot.motors.left = left_speed;
        g_aeris_robot.motors.right = right_speed;
        aeris_set_motors();
    }
}

void
aeris_print_ss_data()
{
    for (u32 i = 0; i < AERIS_SS_COUNT; i++) {
        printf_("[%d, %d, %d, %d]\n",
                g_aeris_robot.surface_sensors.r[i],
                g_aeris_robot.surface_sensors.g[i],
                g_aeris_robot.surface_sensors.b[i],
                g_aeris_robot.surface_sensors.w[i]);
    }
}

void
aeris_print_imu_data()
{
    printf_("a = [%i, %i, %i]\n", g_aeris_robot.imu.ax, g_aeris_robot.imu.ay, g_aeris_robot.imu.az);
    printf_("m = [%i, %i, %i]\n", g_aeris_robot.imu.mx, g_aeris_robot.imu.my, g_aeris_robot.imu.mz);
    printf_("g = [%i, %i, %i]\n ", g_aeris_robot.imu.gx, g_aeris_robot.imu.gy, g_aeris_robot.imu.gz);
    printf_("gh = %i mh = %i\n",
            (i32)(m_atan2(g_aeris_robot.imu.ax, g_aeris_robot.imu.az)*180.0/PI_),
            (i32)(m_atan2(g_aeris_robot.imu.my, g_aeris_robot.imu.mx)*180.0/PI_));
}
