#ifndef FRAMEANALYSIS_H
#define FRAMEANALYSIS_H

#include "frame.h"
#include <stdio.h>

void count_traffic(Frame *frame, int *cars, int *pedestrians);
void analyze_frame(Frame *frame, FILE *analysis_output);
int frame_analysis_work();

#endif