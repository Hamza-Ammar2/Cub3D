/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_rotation(int key, t_game *game)
{
	if (key == KEY_LEFT)
		game->player.angle -= ROT_SPEED;
	else if (key == KEY_RIGHT)
		game->player.angle += ROT_SPEED;
	else
		return (0);
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	return (1);
}

static int	try_move_fb(t_game *game, int key)
{
	double	step;
	double	dir;

	if (key != KEY_W && key != KEY_S)
		return (0);
	step = MOVE_SPEED * SIZE;
	if (key == KEY_W)
		dir = 1.0;
	else
		dir = -1.0;
	game->player.x += cos(game->player.angle) * step * dir;
	game->player.y += sin(game->player.angle) * step * dir;
	return (1);
}

static int	try_move_lr(t_game *game, int key)
{
	double	step;
	double	dir;
	double	angle;

	if (key != KEY_A && key != KEY_D)
		return (0);
	step = MOVE_SPEED * SIZE;
	if (key == KEY_D)
		dir = 1.0;
	else
		dir = -1.0;
	angle = game->player.angle + PI / 2.0;
	game->player.x += cos(angle) * step * dir;
	game->player.y += sin(angle) * step * dir;
	return (1);
}

int	key_it(int key, t_game *game)
{
	if (try_move_fb(game, key))
		return (1);
	return (try_move_lr(game, key));
}
