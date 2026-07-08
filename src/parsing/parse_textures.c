#include "cub3d.h"

static int	texture_index_from_id(const char *id)
{
	static const char	*keys[] = {"NO", "SO", "WE", "EA"};
	int					i;

	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(id, keys[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	set_texture_path(t_game *game, char **texture_fields)
{
	int	i;

	i = texture_index_from_id(texture_fields[0]);
	if (i < 0)
		return (error_exit("unknown texture id"));
	if (game->config.tex_path[i])
		return (error_exit("duplicate texture"));
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
	result = set_texture_path(game, texture_fields);
	free_split(texture_fields);
	return (result);
}
