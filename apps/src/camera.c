#include "camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "config.h"
#include "test_camera.h"

void generate_frame(Frame *frame)
{
    frame->timestamp = time(NULL);
    for (int i = 0; i < FRAME_WIDTH; i++)
    {
        for (int j = 0; j < FRAME_HEIGHT; j++)
        {
            int r = rand() % 10;
            if (r == 1)
                frame->data[i][j] = 1;
            else if (r == 2)
                frame->data[i][j] = 2;
            else
                frame->data[i][j] = 0;
        }
    }
}
void log_frame(Frame *frame, FILE *file)
{
    fprintf(file, "Frame at timestamp: %ld\n", frame->timestamp);
    for (int i = 0; i < FRAME_WIDTH; i++)
    {
        for (int j = 0; j < FRAME_HEIGHT; j++)
        {
            fprintf(file, "%d", frame->data[i][j]);
        }
        fprintf(file, "\n");
    }
    fflush(file);
}

int camera_work()
{
    sem_t *sem = sem_open("/camera_buffer", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED)
    {
        perror("Failed to open semaphore");
        return;
    }

    FILE *logfile = fopen(CAMERA_LOG_FILE, "a");
    if (!logfile)
    {
        perror("Failed to open file");
        sem_close(sem);
    }

    FILE *buffer = fopen(CAMERA_BUFFER_FILE, "wb");
    if (!buffer)
    {
        perror("Failed to open camera buffer");
        fclose(logfile);
        sem_close(sem);
    }

    Frame frame;
    while (1)
    {

        if (sem_wait(sem) == -1)
        {
            perror("Semaphore wait failed");
            break;
        }

        generate_frame(&frame);
        log_frame(&frame, logfile);
        if (fwrite(&frame, sizeof(Frame), 1, buffer) != 1)
        {
            fprintf(logfile, "Error writing to buffer\n");
            fflush(logfile);
            sem_post(sem);
            break;
        }
        fflush(buffer);
        sem_post(sem);
        sleep(1);
    }

    fclose(buffer);
    fclose(logfile);
    sem_close(sem);
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [ --run | --test ]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--test") == 0)
    {
        run_camera_test();
        return 0;
    }
    else if (strcmp(argv[1], "--run") == 0)
    {
        srand(time(NULL));
        return camera_work();
    }
    else
    {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        return 1;
    }
}