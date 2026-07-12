/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	collide(t_game *game, double dx, double dy)
{
	int		i;
	int		j;

	i = get_map_index(game->player.y);
	j = get_map_index(game->player.x);
	if (game->config.map[i][get_map_index(game->player.x + dx)] == '1')
	{
		if (dx > 0)
			game->player.x = (double) j * SIZE + SIZE - 1;
		else
			game->player.x = (double) j * SIZE + 1;
	}
	else
		game->player.x += dx;
	j = get_map_index(game->player.x);
	if (game->config.map[get_map_index(game->player.y + dy)][j] == '1')
	{
		if (dy > 0)
			game->player.y = (double) i * SIZE + SIZE - 1;
		else
			game->player.y = (double) i * SIZE + 1;
	}
	else
		game->player.y += dy;
}

static void	move_wasd(t_game *game, double speed, double dx, double dy)
{
	if (game->keys.w)
	{
		dx += cos(game->player.angle) * speed;
		dy += sin(game->player.angle) * speed;
	}
	if (game->keys.s)
	{
		dx -= cos(game->player.angle) * speed;
		dy -= sin(game->player.angle) * speed;
	}
	if (game->keys.a)
	{
		dx -= cos(game->player.angle + PI / 2.0) * speed;
		dy -= sin(game->player.angle + PI / 2.0) * speed;
	}
	if (game->keys.d)
	{
		dx += cos(game->player.angle + PI / 2.0) * speed;
		dy += sin(game->player.angle + PI / 2.0) * speed;
	}
	collide(game, dx, dy);
}

static void	rotate_player(t_game *game)
{
	if (game->keys.left)
		game->player.angle -= ROT_SPEED;
	if (game->keys.right)
		game->player.angle += ROT_SPEED;
	normalize_angle(&game->player.angle);
}

int	update_player(t_game *game)
{
	move_wasd(game, MOVE_SPEED * SIZE, 0, 0);
	rotate_player(game);
	return (0);
}
