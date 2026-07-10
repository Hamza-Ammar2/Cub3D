/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_config_line(char *line)
{
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| line[0] == 'F' || line[0] == 'C');
}

static int	parse_config(t_game *game, char *line)
{
	if (line[0] == 'F' || line[0] == 'C')
		return (parse_colors(game, line));
	return (parse_textures(game, line));
}

static int	add_map_line(t_list **map_lines, char *line)
{
	t_list	*node;
	char	*dup;

	dup = ft_strdup(line);
	if (!dup)
		return (error_exit("malloc failed"));
	strip_newline(dup);
	node = ft_lstnew(dup);
	if (!node)
	{
		free(dup);
		return (error_exit("malloc failed"));
	}
	ft_lstadd_back(map_lines, node);
	return (0);
}

int	handle_line(t_game *game, char *line, int *map_started, t_list **map_lines)
{
	if (!*map_started)
	{
		if (is_empty_line(line))
			return (0);
		if (is_config_line(line))
			return (parse_config(game, line));
		if (!all_config_set(game))
			return (error_exit("map before all config set"));
		*map_started = 1;
	}
	if (is_empty_line(line))
		return (error_exit("empty line inside map"));
	return (add_map_line(map_lines, line));
}
