#include "cub3d.h"

/*
** Core DDA raycasting loop. For each screen column, cast a ray, run DDA until
** it hits a wall, compute the perpendicular distance and wall side, then hand
** off to draw_column() for the textured vertical strip.
*/
void	cast_rays(t_game *game)
{
	(void)game;
}

void	draw_column(t_game *game, int x)
{
	(void)game;
	(void)x;
}
