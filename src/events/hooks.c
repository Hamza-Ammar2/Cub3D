/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int key, t_game *game)
{
	if (!game)
		return (0);
	if (key == KEY_ESC)
		handle_close(game);
	else if (key == KEY_W)
		game->keys.w = 1;
	else if (key == KEY_A)
		game->keys.a = 1;
	else if (key == KEY_S)
		game->keys.s = 1;
	else if (key == KEY_D)
		game->keys.d = 1;
	else if (key == KEY_LEFT)
		game->keys.left = 1;
	else if (key == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	handle_keyrelease(int key, t_game *game)
{
	if (!game)
		return (0);
	if (key == KEY_W)
		game->keys.w = 0;
	else if (key == KEY_A)
		game->keys.a = 0;
	else if (key == KEY_S)
		game->keys.s = 0;
	else if (key == KEY_D)
		game->keys.d = 0;
	else if (key == KEY_LEFT)
		game->keys.left = 0;
	else if (key == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

int	handle_close(t_game *game)
{
	if (!game)
		exit(0);
	free_game(game);
	exit(0);
	return (0);
}
