#include "line_sensor.h"



void read_line_position()
{
    // u32 max_value = 0;
    // i32 max_i = 0;
    //
    // if (g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_LEFT_CENTER] > LINE_SENSOR_TRESHOLD)
    // {
    //     max_value = g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_LEFT_CENTER];
    //     max_i = -1;
    // }
    //
    // if (
    //         (g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT_CENTER] > LINE_SENSOR_TRESHOLD) &&
    //         (g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT_CENTER] > max_value)
    //     )
    // {
    //     max_value = g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT_CENTER];
    //     max_i = 1;
    // }
    //
    // if (
    //         (g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_LEFT] > LINE_SENSOR_TRESHOLD) &&
    //         (g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_LEFT] > max_value)
    //     )
    // {
    //     max_value = g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_LEFT];
    //     max_i = -2;
    // }
    //
    // if (
    //         (g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT] > LINE_SENSOR_TRESHOLD) &&
    //         (g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT] > max_value)
    //     )
    // {
    //     max_value = g_aeris_robot.surface_sensors.w[AERIS_RGB_SS_FRONT_RIGHT];
    //     max_i = 2;
    // }
    //
    // g_line_position.on_line = 0;
    //
    // if (max_value > LINE_SENSOR_TRESHOLD)
    //     g_line_position.on_line = 1;
    //
    // if (g_line_position.on_line != 0)
    //     g_line_position.line_position = max_i;
}
