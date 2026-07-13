/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:06:16 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:06:16 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_chars(t_game *game, int *player_count);
static int	check_cell(t_game *game, int x, int y, int *pc);
static void	set_player(t_game *game, int x, int y);

int	validate_map(t_game *game)
{
	int	player_count;

	player_count = 0;
	if (check_chars(game, &player_count))
		return (1);
	if (player_count != 1)
		return (error_exit("need exactly 1 player"));
	if (check_closed(game))
		return (1);
	return (0);
}

static int	check_chars(t_game *game, int *player_count)
{
	int	y;
	int	x;

	*player_count = 0;
	y = 0;
	while (y < game->config.map_height)
	{
		x = 0;
		while (x < game->config.map_width)
		{
			if (check_cell(game, x, y, player_count))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	check_cell(t_game *game, int x, int y, int *pc)
{
	char	c;

	c = game->config.map[y][x];
	if (ft_strchr("NSEW", c))
	{
		(*pc)++;
		set_player(game, x, y);
	}
	else if (!ft_strchr("01 ", c))
		return (error_exit("invalid char in map"));
	return (0);
}

static void	set_player(t_game *game, int x, int y)
{
	game->config.start_x = x + 0.5;
	game->config.start_y = y + 0.5;
	game->config.start_dir = game->config.map[y][x];
	game->config.map[y][x] = '0';
}
