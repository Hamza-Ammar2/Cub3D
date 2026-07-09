#include "cub3d.h"

/*
** Core DDA raycasting loop. For each screen column, cast a ray, run DDA until
** it hits a wall, compute the perpendicular distance and wall side, then hand
** off to draw_column() for the textured vertical strip.
*/

static int	get_wall_side(t_game *game, t_vect end, double ray_angle)
{
	double	eps;

	eps = 0.0001;
	(game->config.cur_side) = -1;
	if (fmod(end.x, SIZE) < eps)
	{
		printf("fmod(end.y, SIZE) = %f\n", fmod(end.y, SIZE));
		if (cos(ray_angle) > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (sin(ray_angle) > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

static t_rect	getuv_rect(t_game *game, t_vect end, double ray_angle)
{
	t_rect	uv;
	int		side;

	side = get_wall_side(game, end, ray_angle);
	uv.width = 1;
	uv.height = game->textures[side].height;
	uv.x = (int) (fmod(end.x, SIZE) * game->textures[side].width / SIZE);
	if (side == SOUTH)
		uv.x = game->textures[side].width - uv.x - 1;
	else if (side == EAST || side == WEST)
		uv.x = (int) (fmod(end.y, SIZE) * game->textures[side].width / SIZE);
	if (side == WEST)
		uv.x = game->textures[side].width - uv.x - 1;
	uv.y = 0;
	game->config.cur_side = side;
	return (uv);
}


void	cast_rays(t_game *game)
{
	double ray_angle;
	t_player *player = &game->player;
	t_vect ray_end;
	int i;
	double dist;
	int lineH;

	ray_angle = player->angle - (FOV_SCALE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_end = get_end(game, ray_angle);
		dist = get_distance((t_vect){.x = player->x, .y = player->y}, ray_end);
		dist *= cos(ray_angle - player->angle);
		lineH = (int)(WIN_HEIGHT * SIZE / dist);
		draw_column(game, getuv_rect(game, ray_end, ray_angle), i * (WIN_WIDTH / NUM_RAYS), lineH);
		ray_angle += FOV_SCALE / NUM_RAYS;
		i++;
	}
}

void	draw_column(t_game *game, t_rect uv, int x, int line_h)
{
	int		start_y;
	t_rect	rect;

	start_y = (WIN_HEIGHT - line_h) / 2;
	rect = (t_rect){x, start_y, WIN_WIDTH / NUM_RAYS, line_h};
	draw_img(&game->frame, &game->textures[game->config.cur_side], uv, rect);
	if (start_y > 0)
		draw_rect(game, (t_rect){x, 0, WIN_WIDTH / NUM_RAYS, start_y}, game->config.ceiling_color);
	if (start_y + line_h < WIN_HEIGHT)
		draw_rect(game, (t_rect){x, start_y + line_h, WIN_WIDTH / NUM_RAYS, WIN_HEIGHT - (start_y + line_h)}, game->config.floor_color);
}
