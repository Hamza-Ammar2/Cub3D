/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:07:13 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:07:13 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**dup_map(char **map, int height);
static int	touches_void(t_flood *flood, int x, int y);
static int	scan_map(t_flood *flood);

int	check_closed(t_game *game)
{
	char	**copy;
	t_flood	flood;

	copy = dup_map(game->config.map, game->config.map_height);
	if (!copy)
		return (error_exit("malloc"));
	flood.map = copy;
	flood.width = game->config.map_width;
	flood.height = game->config.map_height;
	if (scan_map(&flood))
	{
		free_split(copy);
		return (error_exit("map is not closed"));
	}
	free_split(copy);
	return (0);
}

static int	scan_map(t_flood *flood)
{
	int	x;
	int	y;

	y = 0;
	while (y < flood->height)
	{
		x = 0;
		while (x < flood->width)
		{
			if (flood->map[y][x] == '0' && touches_void(flood, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static char	**dup_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i <= height)
		copy[i++] = NULL;
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_split(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

static int	touches_void(t_flood *flood, int x, int y)
{
	if (x == 0 || y == 0 || x == flood->width - 1 || y == flood->height - 1)
		return (1);
	if (flood->map[y][x + 1] == ' ' || flood->map[y][x - 1] == ' ')
		return (1);
	if (flood->map[y + 1][x] == ' ' || flood->map[y - 1][x] == ' ')
		return (1);
	return (0);
}
