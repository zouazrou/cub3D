#include "cub3d.h"
#include <float.h>
int main(int argc, char const *argv[])
{
    double nb = 4.999999999999999999999;
    printf("before = %lf\n", DBL_MIN);
    printf("after  = %lf\n", floor(DBL_MIN));

    return 0;
}
