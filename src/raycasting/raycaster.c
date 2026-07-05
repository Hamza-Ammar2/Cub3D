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

void	draw_column(t_game *game, int x, int lineH)
{
	int startY = (WIN_HEIGHT - lineH) / 2;
	//int endY = startY + lineH;
	t_rect rect = {x, startY, WIN_WIDTH / NUM_RAYS, lineH};
	int y;

	y = 0;
	draw_rect(game, rect, 0xFFFFFF); // Placeholder for wall color
	// while (y < WIN_HEIGHT)
	// {
	// 	if (y < startY)
	// 		put_pixel(&game->frame, x, y, game->config.ceiling_color);
	// 	else if (y >= startY && y < endY)
	// 		put_pixel(&game->frame, x, y, 0xFFFFFF); // Placeholder for wall color
	// 	else
	// 		put_pixel(&game->frame, x, y, game->config.floor_color);
	// 	y++;
	// }
}