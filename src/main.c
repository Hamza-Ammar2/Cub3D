#include "cub3d.h"

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
	/* register hooks + start the mlx loop here */
	render_frame(&game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
