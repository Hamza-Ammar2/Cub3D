#include "cub3d.h"

/* True if the line is one of the six identifier lines (NO/SO/WE/EA/F/C). */
static int	is_config_line(char *line)
{
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| line[0] == 'F' || line[0] == 'C');
}

/* Route an identifier line to the texture or color parser. */
static int	parse_config(t_game *game, char *line)
{
	if (line[0] == 'F' || line[0] == 'C')
		return (parse_colors(game, line));
	return (parse_textures(game, line));
}

/* Duplicate a map row and append it to the map_lines list. */
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
		return (free(dup), error_exit("malloc failed"));
	ft_lstadd_back(map_lines, node);
	return (0);
}

/*
** Classify one line: before the map, blanks are skipped and identifiers are
** parsed; the first non-identifier line starts the map (requires all config
** present). Inside the map, blank lines are illegal and rows are collected.
*/
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
