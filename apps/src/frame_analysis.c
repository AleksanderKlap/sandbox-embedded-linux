#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "camera.h"

void count_traffic(Frame *frame, int *cars, int *pedestrians)
{
    *cars = 0, *pedestrians = 0;
    for (int i = 0; i < FRAME_WIDTH; i++)
    {
        for (int j = 0; j < FRAME_HEIGHT; j++)
        {
            if (frame->data[i][j] == 1)
            {
                cars++;
            }
            else if (frame->data[i][j] == 2)
            {
                pedestrians++;
            }
        }
    }
}

void analyze_frame(const Frame *frame, FILE *analysis_output)
{
    int cars = 0, pedestrians = 0;
    count_traffic(frame, &cars, &pedestrians);

    fprintf(analysis_output, "Timestamp: %ld, Cars: %d, Pedestrians: %d\n", frame->timestamp, cars, pedestrians);
    fflush(analysis_output);
}

int frame_analysis_work()
{
    sem_t *sem = sem_open("/camera_buffer", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED)
    {
        perror("Failed to open semaphore");
        return 1;
    }

    FILE *analysis_output = fopen(ANALYSIS_OUTPUT_FILE, "a");
    if (!analysis_output)
    {
        perror("Failed to open log file");
        sem_close(sem);
        return 1;
    }

    FILE *buffer = fopen("/tmp/camera_buffer", "rb");
    if (!buffer)
    {
        perror("Failed to open camera buffer");
        fclose(analysis_output);
        sem_close(sem);
        return 1;
    }

    Frame frame;
    while (1)
    {
        if (sem_wait(sem) == -1)
        {
            perror("Semaphore wait failed");
            break;
        }

        if (fread(&frame, sizeof(Frame), 1, buffer) != 1)
        {
            if (feof(buffer))
            {
                fprintf(analysis_output, "End of buffer reached, analyser stopped.\n");
                fflush(analysis_output);
                sem_post(sem);
                break;
            }
            else
            {
                fprintf(analysis_output, "Error reading buffer\n");
                fflush(analysis_output);
                sem_post(sem);
                sleep(1);
                continue;
            }
        }

        analyze_frame(&frame, analysis_output);
        sem_post(sem);
        sleep(1);
    }

    fclose(buffer);
    fclose(analysis_output);
    sem_close(sem);
    sem_unlink("/camera_buffer");
    return 0;
}

int main()
{
    srand(time(NULL));
    frame_analysis_work();
    return 0;
}