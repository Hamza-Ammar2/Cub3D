#include "cub3d.h"

static int	load_tex(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (load_image(game, &game->textures[i], game->config.tex_path[i]))
			return (1);
		i++;
	}
	return (0);
}

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
	if (init_player(&game))
		return (1);
	if (load_tex(&game))
		return (1);
	game.timing.target_fps = 30.0;
	game.timing.last_frame = get_time_ms();
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
