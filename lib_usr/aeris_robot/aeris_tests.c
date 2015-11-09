#include "aeris_tests.h"

#include "aeris_robot.h"

#include "line_sensor.h"
#include "../math.h"


void
aeris_imu_test()
{
    while (1)
    {
        g_aeris_robot.rgbw.g = 1;
        aeris_set_rgbw();

        aeris_read_imu();

        g_aeris_robot.rgbw.g = 0;
        aeris_set_rgbw();


        printf_("[ %i %i %i ] ", g_aeris_robot.imu.ax, g_aeris_robot.imu.ay, g_aeris_robot.imu.az);
        printf_("[ %i %i %i ] ", g_aeris_robot.imu.mx, g_aeris_robot.imu.my, g_aeris_robot.imu.mz);
        printf_("[ %i %i %i ] ", g_aeris_robot.imu.gx, g_aeris_robot.imu.gy, g_aeris_robot.imu.gz);
        printf_("> %i >>>>%i <", (i32)(m_atan2(g_aeris_robot.imu.ax, g_aeris_robot.imu.az)*180.0/PI_) , (i32)(m_atan2(g_aeris_robot.imu.my, g_aeris_robot.imu.mx)*180.0/PI_) );
        printf_("\n");

        timer_delay_ms(100);
    }
}


void aeris_surface_sensors_test()
{
    while (1)
    {
        g_aeris_robot.rgbw.g = 1;
        aeris_set_rgbw();

        aeris_read_surface_sensors();

        g_aeris_robot.rgbw.g = 0;
        aeris_set_rgbw();


      printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_FRONT_LEFT],
                                       g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_FRONT_LEFT],
                                       g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_FRONT_LEFT],
                                       g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_LEFT]);

       printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_FRONT_LEFT_CENTER],
                                      g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_FRONT_LEFT_CENTER],
                                      g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_FRONT_LEFT_CENTER],
                                      g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_LEFT_CENTER]);


       printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_FRONT_RIGHT_CENTER],
                                      g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_FRONT_RIGHT_CENTER],
                                      g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_FRONT_RIGHT_CENTER],
                                      g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT_CENTER]);

       printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_FRONT_RIGHT],
                                      g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_FRONT_RIGHT],
                                      g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_FRONT_RIGHT],
                                      g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT]);


       printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_REAR_LEFT],
                                                                      g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_REAR_LEFT],
                                                                      g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_REAR_LEFT],
                                                                      g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_REAR_LEFT]);

       printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_REAR_LEFT_CENTER],
                                                                     g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_REAR_LEFT_CENTER],
                                                                     g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_REAR_LEFT_CENTER],
                                                                     g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_REAR_LEFT_CENTER]);


       printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_REAR_RIGHT_CENTER],
                                                                     g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_REAR_RIGHT_CENTER],
                                                                     g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_REAR_RIGHT_CENTER],
                                                                     g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_REAR_RIGHT_CENTER]);

        printf_("[ %i %i %i %i] \n",   g_aeris_robot.surface_sensors.r[AERIS_RGB_SS_REAR_RIGHT],
                                                                     g_aeris_robot.surface_sensors.g[AERIS_RGB_SS_REAR_RIGHT],
                                                                     g_aeris_robot.surface_sensors.b[AERIS_RGB_SS_REAR_RIGHT],
                                                                     g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_REAR_RIGHT]);

        printf_("----------------------------------------------------\n\n" );
        timer_delay_ms(100);
    }
}


void aeris_motor_test()
{
    //while (1)
    {
        g_aeris_robot.motors.left = 40;
        g_aeris_robot.motors.right = 40;
        aeris_set_motors();
        timer_delay_ms(800);


        g_aeris_robot.motors.left = 0;
        g_aeris_robot.motors.right = 0;
        aeris_set_motors();
        timer_delay_ms(800);
    }
}


void aeris_line_folower_test()
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
