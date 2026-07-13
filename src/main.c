/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:09:12 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:09:12 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	run_game(t_game *game)
{
	game->timing.target_fps = 30.0;
	game->timing.last_frame = get_time_ms();
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

static int	fail(t_game *game)
{
	free_game(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_exit("usage: ./cub3D <scene.cub>"));
	ft_bzero(&game, sizeof(t_game));
	if (parse_scene(&game, argv[1]))
		return (fail(&game));
	if (init_game(&game))
		return (fail(&game));
	if (init_player(&game))
		return (fail(&game));
	if (load_textures(&game))
		return (fail(&game));
	run_game(&game);
	free_game(&game);
	return (0);
}
