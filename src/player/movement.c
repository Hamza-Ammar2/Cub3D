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

static void	move_wasd(t_game *game, double speed)
{
	t_player	*player;

	player = &game->player;
	if (game->keys.w)
	{
		player->x += cos(player->angle) * speed;
		player->y += sin(player->angle) * speed;
	}
	if (game->keys.s)
	{
		player->x -= cos(player->angle) * speed;
		player->y -= sin(player->angle) * speed;
	}
	if (game->keys.a)
	{
		player->x -= cos(player->angle + PI / 2.0) * speed;
		player->y -= sin(player->angle + PI / 2.0) * speed;
	}
	if (game->keys.d)
	{
		player->x += cos(player->angle + PI / 2.0) * speed;
		player->y += sin(player->angle + PI / 2.0) * speed;
	}
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
	move_wasd(game, MOVE_SPEED * SIZE);
	rotate_player(game);
	return (0);
}
