#ifndef FRAMEANALYSIS_H
#define FRAMEANALYSIS_H

#include "frame.h"
#include <stdio.h>

void count_traffic(Frame *frame, int *cars, int *pedestrians);
void analyze_frame(const Frame *frame, FILE *log_file);
int frame_analysis_work();
int main();

#endif