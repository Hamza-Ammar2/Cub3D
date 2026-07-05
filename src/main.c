#include "cub3d.h"

static int key_down(int key, void *param)
{
	t_game *game = (t_game *)param;

	if (key == KEY_W)
		game->player.move_forward = 1;
	else if (key == KEY_S)
		game->player.move_backward = 1;
	else if (key == KEY_A)
		game->player.move_left = 1;
	else if (key == KEY_D)
		game->player.move_right = 1;
	else if (key == KEY_LEFT)
		game->player.rotate_left = 1;
	else if (key == KEY_RIGHT)
		game->player.rotate_right = 1;
	return (0);
}

static int key_up(int key, void *param)
{
	t_game *game = (t_game *)param;

	if (key == KEY_W)
		game->player.move_forward = 0;
	else if (key == KEY_S)
		game->player.move_backward = 0;
	else if (key == KEY_A)
		game->player.move_left = 0;
	else if (key == KEY_D)
		game->player.move_right = 0;
	else if (key == KEY_LEFT)
		game->player.rotate_left = 0;
	else if (key == KEY_RIGHT)
		game->player.rotate_right = 0;
	return (0);
}

// static int	handle_key(mlx_key_data_t keydata, void *param)
// {
// 	// if (key == KEY_ESC)
// 	// 	clean(game);
// 	t_game *game = (t_game *)param;

// 	if (keydata.key == KEY_W)
// 	{
// 		if (keydata.action == KEY_PRESS)
// 			game->player.move_forward = 1;
// 		else if (keydata.action == KEY_RELEASE)
// 			game->player.move_forward = 0;
// 	}
// 	if (keydata.key == KEY_S)
// 	{
// 		if (keydata.action == KEY_PRESS)
// 			game->player.move_backward = 1;
// 		else if (keydata.action == KEY_RELEASE)
// 			game->player.move_backward = 0;
// 	}
// 	if (keydata.key == KEY_A)
// 	{
// 		if (keydata.action == KEY_PRESS)
// 			game->player.move_left = 1;
// 		else if (keydata.action == KEY_RELEASE)
// 			game->player.move_left = 0;
// 	}
// 	if (keydata.key == KEY_D)
// 	{
// 		if (keydata.action == KEY_PRESS)
// 			game->player.move_right = 1;
// 		else if (keydata.action == KEY_RELEASE)
// 			game->player.move_right = 0;
// 	}
// 	if (keydata.key == KEY_LEFT)
// 	{
// 		if (keydata.action == KEY_PRESS)
// 			game->player.rotate_left = 1;
// 		else if (keydata.action == KEY_RELEASE)
// 			game->player.rotate_left = 0;
// 	}
// 	if (keydata.key == KEY_RIGHT)
// 	{
// 		if (keydata.action == KEY_PRESS)
// 			game->player.rotate_right = 1;
// 		else if (keydata.action == KEY_RELEASE)
// 			game->player.rotate_right = 0;
// 	}
// 	return (0);
// 	// if (!key_it(key, game) && !handle_rotation(key, game))
// 	// 	return (0);
// 	// clear_image(&game->frame);
// 	// draw_map2D(game);
// 	// draw_rays2D(&game->player, game);
// 	// mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
// 	// return (0);
// }

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_exit("usage: ./cub3D <scene.cub>"));
	ft_bzero(&game, sizeof(t_game));
	if (parse_scene(&game, argv[1]))
		return (1);
	if (init_game(&game))
		return (1);
	get_map(argv[1], &game);
	game.player.x = 3 * SIZE + SIZE / 2; // Center of the cell (3, 1)
	game.player.y = 1 * SIZE + SIZE; // Center of the cell (3, 1)
	game.player.angle = 0; // Facing right
	// draw_map2D(&game);
	// draw_rays2D(&game.player, &game);
	game.timing.target_fps = 30.0;
	game.timing.last_frame = get_time_ms();
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, 2, 1, key_down, &game);   // KeyPress, KeyPressMask
	mlx_hook(game.win, 3, 2, key_up, &game);
	//mlx_key_hook(game.win, handle_key, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
