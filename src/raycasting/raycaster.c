#include "cub3d.h"

/*
** Core DDA raycasting loop. For each screen column, cast a ray, run DDA until
** it hits a wall, compute the perpendicular distance and wall side, then hand
** off to draw_column() for the textured vertical strip.
*/

static int	get_wall_side(t_game *game, t_vect end, double ray_angle)
{
	t_player	*player = &game->player;
	// int			map_x = get_index(end.x);
	// int			map_y = get_index(end.y);
	int			side;

	// if (map_x < 0 || map_x >= game->config.map_width
	// 	|| map_y < 0 || map_y >= game->config.map_height)
	// 	return (-1);
	// if (game->config.map[map_y][map_x] != '1')
	// 	return (-1);
	if (fabs(end.x - player->x) > fabs(end.y - player->y))
		side = (ray_angle > PI / 2 && ray_angle < 3 * PI / 2) ? WEST : EAST;
	else
		side = (ray_angle < PI) ? NORTH : SOUTH;
	return (side);
}

static t_rect	getuv_rect(t_game *game, t_vect end, double ray_angle)
{
	t_rect	uv;
	//int		side;
	// float d;
	// float n;

	// d = WIN_WIDTH / (float)NUM_RAYS;
	// n = SIZE / d;
	uv.width = game->textures[3].width;
	uv.height = game->textures[3].height;
	get_wall_side(game, end, ray_angle);
	// (side);

	uv.x = (int) (fmod(end.x, SIZE) * game->textures[3].width / SIZE);
	uv.y = 0;
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
	//int		side = get_wall_side(game, (t_vect){.x = game->player.x + cos(game->player.angle) * 1000, .y = game->player.y + sin(game->player.angle) * 1000}, game->player.angle);

	start_y = (WIN_HEIGHT - line_h) / 2;
	rect = (t_rect){x, start_y, WIN_WIDTH / NUM_RAYS, line_h};
	//draw_rect(game, rect, 0xFFFFFF);
	//uv.x = x % game->textures[3].width; // Keep src_x locked to the ray's sample point instead of stretching it
	draw_img(&game->frame, &game->textures[3], uv, rect);
}
