/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:06:49 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:06:49 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**split_color_fields(char *line)
{
	char	**color_fields;

	strip_newline(line);
	color_fields = ft_split(line, ' ');
	return (color_fields);
}

static int	validate_color_fields(char **color_fields)
{
	if (!color_fields || count_words(color_fields) != 2)
		return (error_exit("bad color line"));
	return (0);
}

static int	parse_color_value(char **color_fields, int *is_floor, int *rgb)
{
	int	result;

	result = parse_color_fields(color_fields, is_floor);
	if (result != 0)
		return (result);
	*rgb = parse_rgb(color_fields[1]);
	if (*rgb == -1)
		return (error_exit("bad rgb"));
	return (0);
}

static int	finish_color_parse(t_game *game, char **color_fields, int is_floor,
		int rgb)
{
	int	result;

	result = store_color(game, is_floor, rgb);
	free_split(color_fields);
	return (result);
}

int	parse_colors(t_game *game, char *line)
{
	char	**color_fields;
	int		rgb;
	int		is_floor;
	int		result;
	int		color_parse_result;

	color_fields = split_color_fields(line);
	result = validate_color_fields(color_fields);
	if (result != 0)
	{
		free_split(color_fields);
		return (result);
	}
	result = parse_color_value(color_fields, &is_floor, &rgb);
	if (result != 0)
	{
		free_split(color_fields);
		return (result);
	}
	color_parse_result = finish_color_parse(game, color_fields, is_floor, rgb);
	return (color_parse_result);
}
