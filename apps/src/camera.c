#include "camera.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

static void generate_frame(Frame *frame)
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

static void log_frame(Frame *frame, FILE *file)
{
    fprintf(file, "Frame at timestamp: %ld\n", frame->timestamp);
    for (int i = 0; i < FRAME_WIDTH; i++)
    {
        for (int j = 0; j < FRAME_HEIGHT; j++)
        {
            fprintf(file, "%d", frame->data[i][j]);
        }
        fprintf(file, "\n");
        fflush(file);
    }
}

void camera_work()
{
    sem_t *sem = sem_open("/camera_buffer", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED)
    {
        perror("Failed to open semaphore");
        return;
    }

    FILE *file = fopen("/tmp/camera_mock.log", "a");
    if (!file)
    {
        perror("Failed to open file");
        sem_close(sem);
        return 1;
    }

    FILE *buffer = fopen("/tmp/camera_buffer", "wb");
    if (!buffer)
    {
        perror("Failed to open camera buffer");
        fclose(file);
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

        generate_frame(&frame);
        log_frame(&frame, file);
        if (fwrite(&frame, sizeof(Frame), 1, buffer) != 1)
        {
            fprintf(file, "Error writing to buffer\n");
            fflush(file);
            sem_post(sem);
            break;
        }
        fflush(buffer);
        sem_post(sem);
        sleep(1);
    }

    fclose(buffer);
    fclose(file);
    sem_close(sem);
    sem_unlink("/camera_buffer");
}

int main()
{
    srand(time(NULL));
    camera_work();
    return 0;
}