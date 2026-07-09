#include "cub3d.h"

/*
** Core DDA raycasting loop. For each screen column, cast a ray, run DDA until
** it hits a wall, compute the perpendicular distance and wall side, then hand
** off to draw_column() for the textured vertical strip.
*/


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
		draw_column(game, i * (WIN_WIDTH / NUM_RAYS), lineH);
		ray_angle += FOV_SCALE / NUM_RAYS;
		i++;
	}
}

void	draw_column(t_game *game, int x, int line_h)
{
	int		start_y;
	t_rect	rect;

	start_y = (WIN_HEIGHT - line_h) / 2;
	rect = (t_rect){x, start_y, WIN_WIDTH / NUM_RAYS, line_h};
	draw_rect(game, rect, 0xFFFFFF);
}