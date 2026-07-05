#include "cub3d.h"

static int	read_scene(t_game *game, int fd, t_list **map_lines);
static int	finish_scene(t_game *game, t_list **map_lines);

/* Reject anything that isn't a "*.cub" file (also rejects NULL and ".cub"). */
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

/* True only when all 4 textures and both colors have been parsed. */
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

/*
** Entry point for parsing the .cub file: check the extension, open the file,
** read + dispatch every line, then build and validate the map. Owns the fd and
** the temporary map_lines list.
*/
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
		return (1);
	}
	return (finish_scene(game, &map_lines));
}

/*
** Read the file line by line and hand each line to handle_line(). map_started
** is loop-local state (it only matters while reading).
*/
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

/*
** Post-read checks: all 6 elements present, a non-empty map, then build the
** grid and validate it. The map_lines list is disposable once build_map has
** copied it into config.map.
*/
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
