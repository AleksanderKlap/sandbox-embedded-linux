#include <stdio.h>
#include <assert.h>
#include "config.h"
#include "frame.h"
#include "test_camera.h"

int count_values(Frame *frame, int value)
{
    int count = 0;
    for (int i = 0; i < FRAME_WIDTH; i++)
    {
        for (int j = 0; j < FRAME_HEIGHT; j++)
        {
            if (frame->data[i][j] == value)
                count++;
        }
    }
    return count;
}

int test_generate_frame()
{
    Frame test_frame;

    generate_frame(&test_frame);

    assert(test_frame.timestamp > 0);

    int count_0 = count_values(&test_frame, 0);
    int count_1 = count_values(&test_frame, 1);
    int count_2 = count_values(&test_frame, 2);

    printf("Value counts: 0=%d, 1=%d, 2=%d\n", count_0, count_1, count_2);

    assert(count_0 + count_1 + count_2 == FRAME_WIDTH * FRAME_HEIGHT);
    assert(count_0 >= 0);
    assert(count_1 >= 0);
    assert(count_2 >= 0);

    printf("All tests passed.\n");
}

int run_camera_test()
{
    test_generate_frame();
    return 0;
}
