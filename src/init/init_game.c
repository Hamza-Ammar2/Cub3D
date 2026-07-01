#include "cub3d.h"

/* Boot mlx, create the window + frame image, load textures, place player. */
int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_exit("mlx init failed"));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
		return (error_exit("window creation failed"));
	game->frame.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.ptr)
		return (error_exit("image creation failed"));
	game->frame.addr = mlx_get_data_addr(game->frame.ptr, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (error_exit("image data init failed"));
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 1L << 17, handle_close, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	return (0);
}

int	init_player(t_game *game)
{
	(void)game;
	return (0);
}

int	load_textures(t_game *game)
{
	(void)game;
	return (0);
}
