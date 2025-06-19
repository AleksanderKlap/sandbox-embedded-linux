#ifndef CAMERA_H
#define CAMERA_H

#include "config.h"
#include "frame.h"
#include <stdio.h>

void generate_frame(Frame *frame);
static void log_frame(Frame *frame, FILE *file);
int main();

#endif