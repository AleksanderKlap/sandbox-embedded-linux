#include "camera.h"

void test_empty_frame()
{
    Frame f = {0};
    int cars, pedestrians;
    count_objects(&f, &cars, &pedestrians);
    assert(cars == 0);
    assert(pedestrians == 0);
}

void test_frame_with_objects()
{
    Frame f = {0};
    f.data[0][0] = 1;
    f.data[1][1] = 1;
    f.data[2][2] = 2;
    int cars, pedestrians;
    count_objects(&f, &cars, &pedestrians);
    assert(cars == 2);
    assert(pedestrians == 1);
}

int main()
{
    test_empty_frame();
    test_frame_with_objects();
    printf("All tests passed\n");
    return 0;
}