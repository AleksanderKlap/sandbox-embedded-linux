#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "camera.h"

static void analyze_frame(const Frame *frame, FILE *log_file)
{
    int cars = 0, pedestrians = 0;
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

    fprintf(log_file, "Timestamp: %ld, Cars: %d, Pedestrians: %d\n", frame->timestamp, cars, pedestrians);
    fflush(log_file);
}

static int frame_analysis_work()
{
    sem_t *sem = sem_open("/camera_buffer", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED)
    {
        perror("Failed to open semaphore");
        return 1;
    }

    FILE *log_file = fopen("/tmp/frame_analysis.log", "a");
    if (!log_file)
    {
        perror("Failed to open log file");
        sem_close(sem);
        return 1;
    }

    FILE *buffer = fopen("/tmp/camera_buffer", "rb");
    if (!buffer)
    {
        perror("Failed to open camera buffer");
        fclose(log_file);
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
            fprintf(log_file, "Error reading buffer\n");
            fflush(log_file);
            sem_post(sem);
            sleep(1);
            continue;
        }

        analyze_frame(&frame, log_file);
        sem_post(sem);
        sleep(1);
    }

    fclose(buffer);
    fclose(log_file);
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