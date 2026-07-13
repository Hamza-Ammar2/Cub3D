/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_scene(t_game *game, int fd, t_list **map_lines);
static int	finish_scene(t_game *game, t_list **map_lines);

int	check_extension(char *path)
{
	int	len;

	if (!path)
		return (1);
	len = ft_strlen(path);
	if (len <= 4)
		return (1);
	return (ft_strcmp(path + len - 4, ".cub") != 0);
}

int	all_config_set(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->config.tex_path[i])
			return (0);
		i++;
	}
	return (game->config.floor_set && game->config.ceiling_set);
}

int	parse_scene(t_game *game, char *path)
{
	int		fd;
	t_list	*map_lines;
	int		status;

	if (check_extension(path))
		return (error_exit("bad extension"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_exit("cannot open file"));
	map_lines = NULL;
	status = read_scene(game, fd, &map_lines);
	close(fd);
	if (status)
	{
		ft_lstclear(&map_lines, free);
		get_next_line(-1);
		return (1);
	}
	return (finish_scene(game, &map_lines));
}

static int	read_scene(t_game *game, int fd, t_list **map_lines)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (handle_line(game, line, &map_started, map_lines))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

static int	finish_scene(t_game *game, t_list **map_lines)
{
	int	ret;

	if (!all_config_set(game))
	{
		ft_lstclear(map_lines, free);
		return (error_exit("missing texture or color"));
	}
	if (*map_lines == NULL)
		return (error_exit("empty map"));
	ret = build_map(game, *map_lines);
	ft_lstclear(map_lines, free);
	if (ret)
		return (1);
	return (validate_map(game));
}
