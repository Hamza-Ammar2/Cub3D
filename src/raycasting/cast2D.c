

#include "cub3d.h"

t_vect	get_ray_end_horizontal(t_game *game, double ray_angle)
{
	t_player *player = &game->player;
	double	m;
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		i;
	int		j;

	m = tan(ray_angle);
	if (sin(ray_angle) > 0)
	{
		dy = SIZE;
		y = get_index(player->y) * SIZE + SIZE;
	}
	else
	{
		dy = -SIZE;
		y = get_index(player->y) * SIZE;
	}
	dx = dy / m;
	x = player->x + (y - player->y) / m;
	while (1)
	{
		i = get_index(y);
		j = get_index(x);
		if (dy < 0)
			i -= 1;
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

t_vect	get_ray_end(t_game *game, double ray_angle)
{
	t_player *player = &game->player;
	double	m;
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		i;
	int		j;

	m = tan(ray_angle);
	if (cos(ray_angle) > 0)
	{
		dx = SIZE;
		x = get_index(player->x) * SIZE + SIZE;
	}
	else
	{
		dx = -SIZE;
		x = get_index(player->x) * SIZE;
	}
	dy = m * dx;
	y = player->y + m * (x - player->x);
	while (1)
	{
		i = get_index(y);
		j = get_index(x);
		if (dx < 0)
			j -= 1;
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

t_vect get_end(t_game *game, double ray_angle)
{
	t_player *player = &game->player;
	t_vect a = get_ray_end_horizontal(game, ray_angle);
	t_vect b = get_ray_end(game, ray_angle);
	double dist_a = (pow(a.x - player->x, 2) + pow(a.y - player->y, 2));
	double dist_b = (pow(b.x - player->x, 2) + pow(b.y - player->y, 2));
	return (dist_a < dist_b) ? a : b;
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
		ray_end = get_end(game, ray_angle);
		draw_line(game, (t_vect){.x = player->x, .y = player->y}, ray_end, 0xFF0000);
		ray_angle += FOV_SCALE / NUM_RAYS;
		i++;
	}
}
