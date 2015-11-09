#ifndef _LINE_SENSOR_H_
#define _LINE_SENSOR_H_

#include "aeris_robot.h"


#define LINE_SENSOR_TRESHOLD (u32)500


struct sLinePosition
{
    i32 line_position;
    u8 on_line;
};

struct sLinePosition g_line_position;

void read_line_position();

#endif
