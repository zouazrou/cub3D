#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;

void put_pixel_in_image(void *image, int x, int y, int col)
{
    int     offset;
    char    *data_img;

    data_img = mlx_get_data_addr(image, &bpp, &line_bytes, &endian);
    offset = (y * line_bytes) + (x * (bpp / 8));
    *(int *)(data_img + offset) = col;
}