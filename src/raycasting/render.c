#include "cub3d.h"

/*
** Compose one frame: run the raycaster and push the image to the window.
** update_player() is called from game_loop() before this runs.
*/
int	render_frame(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	return (0);
}
