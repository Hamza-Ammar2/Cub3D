
#include "cub3d.h"

void	draw_map2D(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->config.map_height)
    {
        j = 0;
        while (j < game->config.map_width)
        {
            if (game->config.map[i][j] == '1')
                draw_rect(game, (t_rect){.x = j * SIZE, .y = i * SIZE, .width = SIZE, .height = SIZE}, 0xFFFFFF);
            else
                draw_rect(game, (t_rect){.x = j * SIZE, .y = i * SIZE, .width = SIZE, .height = SIZE}, 0x000000);
            j++;
        }
        i++;
    }
}

void	draw_rect(t_game *game, t_rect rect, int color)
{
    int i;
    int j;

    i = 0;
    while (i < rect.height)
    {
        j = 0;
        while (j < rect.width)
        {
            put_pixel(&game->frame, rect.x + j, rect.y + i, color);
            j++;
        }
        i++;
    }
}

void	draw_line(t_game *game, t_vect p0, t_vect p1, int color)
{
    int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(p1.x - p0.x);
	dy = abs(p1.y - p0.y);
	if (p0.x < p1.x)
		sx = 1;
	else
		sx = -1;
	if (p0.y < p1.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		put_pixel(&game->frame, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err = err - dy;
			p0.x = p0.x + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			p0.y = p0.y + sy;
		}
	}
}
