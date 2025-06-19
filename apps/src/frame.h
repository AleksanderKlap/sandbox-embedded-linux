#ifndef FRAME_H
#define FRAME_H

#include <time.h>
#include "config.h"

typedef struct
{
    int data[FRAME_WIDTH][FRAME_HEIGHT];
    time_t timestamp;
} Frame;

#endif