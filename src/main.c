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
	// draw_rect(&game, (t_rect){.x = 100, .y = 100, .width = 20, .height = 150}, 0x00FF00);
	// draw_line(&game, (t_vect){.x = 50, .y = 50}, (t_vect){.x = 200, .y = 200}, 0xFF0000);
	get_map(argv[1], &game);
	game.player.x = 3 * SIZE + SIZE / 2; // Center of the cell (3, 1)
	game.player.y = 1 * SIZE + SIZE; // Center of the cell (3, 1)
	game.player.angle = 0; // Facing right
	draw_map2D(&game);
	draw_rays2D(&game.player, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
