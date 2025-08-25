#include "cub3d.h"

bool    FACING_DOWN(double angle)
{
    if (angle > 0 && angle < PI)
        return (true);
    return (false);
}

bool    FACING_UP(double angle)
{
    // if (angle > PI && angle < 2 * PI)
    //     return (true);
    // return (false);
    return (!FACING_DOWN(angle));
}

bool    FACING_RIGHT(double angle)
{
    if (angle < PI / 2 || angle > PI * 3 / 2)
        return (true);
    return (false);
}

bool    FACING_LEFT(double angle)
{
    // if (angle > PI / 2 && angle < PI * 3 / 2)
    //     return (true);
    // return (false);
    return (!FACING_RIGHT(angle)); 
}
