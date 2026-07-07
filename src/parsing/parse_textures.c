#include "cub3d.h"

static int	get_texture_index(char *id)
{
	if (ft_strcmp(id, "NO") == 0)
		return (NORTH);
	if (ft_strcmp(id, "SO") == 0)
		return (SOUTH);
	if (ft_strcmp(id, "WE") == 0)
		return (WEST);
	if (ft_strcmp(id, "EA") == 0)
		return (EAST);
	return (-1);
}

static int	assign_texture_path(t_game *game, char **texture_fields)
{
	int	i;

	i = get_texture_index(texture_fields[0]);
	if (i < 0)
		return (error_exit("unknown texture id"));
	game->config.tex_path[i] = ft_strdup(texture_fields[1]);
	if (!game->config.tex_path[i])
		return (error_exit("malloc failed"));
	return (0);
}

/* Parse the NO / SO / WE / EA identifier lines into config.tex_path[]. */
int	parse_textures(t_game *game, char *line)
{
	char	**texture_fields;
	int		result;

	strip_newline(line);
	texture_fields = ft_split(line, ' ');
	if (!texture_fields || count_words(texture_fields) != 2)
	{
		free_split(texture_fields);
		return (error_exit("bad texture line"));
	}
	result = assign_texture_path(game, texture_fields);
	free_split(texture_fields);
	return (result);
}
