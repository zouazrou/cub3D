#include "cub3d.h"

int main(int argc, char const *argv[])
{

    double radian = -(PI);
    radian = fmod(radian, (PI*2));
    if (radian < 0)
        radian += PI*2;
    printf("rad {%.2f}\n", radian);

    return 0;
}
