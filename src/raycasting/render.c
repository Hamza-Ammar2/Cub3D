#include "cub3d.h"

/*
** Compose one frame: paint ceiling + floor, run the raycaster, push the image
** to the window. Registered as the mlx_loop_hook.
*/
int	render_frame(t_game *game)
{
	update_player(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	return (0);
}
