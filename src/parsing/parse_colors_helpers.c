/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:07:02 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:07:02 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color_fields(char **color_fields, int *is_floor)
{
	if (ft_strcmp(color_fields[0], "F") == 0)
		*is_floor = 1;
	else if (ft_strcmp(color_fields[0], "C") == 0)
		*is_floor = 0;
	else
		return (error_exit("unknown color id"));
	return (0);
}

int	store_color(t_game *game, int is_floor, int rgb)
{
	if (is_floor)
	{
		if (game->config.floor_set)
			return (error_exit("dup floor"));
		game->config.floor_color = rgb;
		game->config.floor_set = 1;
	}
	else
	{
		if (game->config.ceiling_set)
			return (error_exit("dup ceiling"));
		game->config.ceiling_color = rgb;
		game->config.ceiling_set = 1;
	}
	return (0);
}
