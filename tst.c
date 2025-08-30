#include "cub3d.h"

/*
    mlx_xpm_file_to_image();

*/
int main(int argc, char const *argv[])
{
    int w, h;
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "wall");
    if (!mlx || !win)
        exit(42);
    void *wall_img;

    wall_img= mlx_xpm_file_to_image(mlx, "image/wall.xpm", &w, &h);
    if (!wall_img)
        exit( 22);
    mlx_put_image_to_window(mlx, win, wall_img, WIDTH/2-1, HEIGHT/2-1);

    if (!mlx_loop(mlx))
        printf("waaaa3\n");
    
    return 0;
}
 