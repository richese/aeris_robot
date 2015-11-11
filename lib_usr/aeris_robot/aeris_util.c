#include "aeris_util.h"

#include "aeris_robot.h"
#include "line_sensor.h"
#include "../math.h"


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
