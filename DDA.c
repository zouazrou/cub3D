#include "cub3d.h"


#define SIZE 20

char **board;

void    print_board()
{
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if (board[y][x] == 0)
                write(1, ".", 1);
            else
                write(1, board[y] + x, 1);
            write(1, " ", 1);
        }
        write(1, "\n", 1);
    }
}

void put_pixel(int x, int y)
{
    board[y][x] = 'x';
}

void    DDA(t_vec p0, t_vec p1)
{
	int		dx;
    int		dy;
	float	Xinc, Yinc;
	float	x, y;
    int		steps;

    printf("Xp0 = %d | Yp0 = %d\nXp1 = %d | Yp1 = %d\n", p0.x, p0.y, p1.x, p1.y);
    //
    dx = p1.x - p0.x;
    dy = p1.y - p0.y;
    printf("Xd = %d | Yd = %d\n", dx, dy);

    // steps
    steps = dx;
    if (dx < dy)
        steps = dy;
    // calculate increment in x & y for each steps
    Xinc = (float)(dx / (float)steps);
    Yinc = (float)(dy / (float)steps);
    printf("Xinc = %f | Yinc = %f\n", Xinc, Yinc);

    // draw line in the window
    x = p0.x;
	y = p0.y;
    for (int i = 0; i <= steps; i++)
    {
        // put pixel in this position ...
        put_pixel(x, y);
        x += Xinc;
        y += Yinc;
    }
}

int main(int argc, char const *argv[])
{
	t_game	game;

    board = calloc(SIZE, sizeof(char *));
    for (int i = 0; i < SIZE; i++)
        board[i] = calloc(SIZE, 1);




    DDA((t_vec){0, 0}, (t_vec){9, 13});    

    print_board();
    return 0;
}
