/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	start_angle(char dir)
{
	if (dir == 'E')
		return (0.0);
	if (dir == 'S')
		return (PI / 2.0);
	if (dir == 'W')
		return (PI);
	if (dir == 'N')
		return (3.0 * PI / 2.0);
	return (0.0);
}

static void	bind_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 1L << 17, handle_close, game);
}

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
	bind_hooks(game);
	return (0);
}

int	init_player(t_game *game)
{
	game->player.x = game->config.start_x * SIZE;
	game->player.y = game->config.start_y * SIZE;
	game->player.angle = start_angle(game->config.start_dir);
	return (0);
}

int	load_textures(t_game *game)
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
