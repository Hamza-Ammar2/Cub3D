#include "cub3d.h"

/*
** Apply held-key state each frame: WASD translate the position vector (with
** wall collision checks), left/right arrows rotate dir + camera plane.
*/

t_vect	get_ray_end(t_game *game, double ray_angle)
{
	t_player *player = &game->player;
	double x = player->x;
	double y = player->y;

	double m = tan(ray_angle);
	double dx = SIZE;
	double dy = m * dx;

	x = get_index(player->x) * SIZE + SIZE;
	y = player->y + m * (x - player->x);
	if (cos(ray_angle) < 0)
	{
		dx = -SIZE;
		dy = m * dx;
		x = get_index(player->x) * SIZE;
	}
	while (1)
	{
		int i = get_index(y);
		int j = get_index(x);

		if (i < 0 || i >= game->config.map_height)
			break;
		if (j < 0 || j >= game->config.map_width)
			break;

		if (game->config.map[i][j] == '1')
			break;
		x += dx;
		y += dy;
	}
	return (t_vect){.x = (int)x, .y = (int)y};
}

void	draw_rays2D(t_player *player, t_game *game)
{
	double ray_angle;
	t_vect ray_end;
	int i;

	ray_angle = player->angle - (FOV_SCALE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_end = get_ray_end(game, ray_angle);
		draw_line(game, (t_vect){.x = player->x, .y = player->y}, ray_end, 0xFF0000);
		ray_angle += FOV_SCALE / NUM_RAYS;
		i++;
	}
}



int	update_player(t_game *game)
{
	(void)game;
	return (0);
}
