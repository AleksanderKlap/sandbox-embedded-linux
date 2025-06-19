#ifndef FRAMEANALYSIS_H
#define FRAMEANALYSIS_H

#include "frame.h"
#include <stdio.h>

static void analyze_frame(const Frame *frame, FILE *log_file);
static int frame_analysis_work();
int main();

#endif