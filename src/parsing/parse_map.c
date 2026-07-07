#include "cub3d.h"

static int	get_max_width(t_list *map_lines);
static char	*pad_line(char *src, int width);

/*
** Convert the collected map rows (t_list) into config.map (char **). Every row
** is padded with spaces to the width of the longest row so the grid is
** rectangular, which makes bounds checks and the flood fill trivial.
*/
int	build_map(t_game *game, t_list *map_lines)
{
	int		height;
	int		i;
	t_list	*cur;

	height = ft_lstsize(map_lines);
	game->config.map = malloc(sizeof(char *) * (height + 1));
	if (!game->config.map)
		return (error_exit("malloc map"));
	game->config.map_width = get_max_width(map_lines);
	game->config.map_height = height;
	cur = map_lines;
	i = 0;
	while (cur)
	{
		game->config.map[i] = pad_line(cur->content, game->config.map_width);
		if (!game->config.map[i])
			return (error_exit("malloc line"));
		cur = cur->next;
		i++;
	}
	game->config.map[i] = NULL;
	return (0);
}

/* Length of the longest row, excluding a trailing newline. */
static int	get_max_width(t_list *map_lines)
{
	int		max;
	int		len;
	t_list	*cur;

	max = 0;
	cur = map_lines;
	while (cur)
	{
		len = ft_strlen(cur->content);
		if (len > 0 && ((char *)cur->content)[len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		cur = cur->next;
	}
	return (max);
}

/* Copy src (minus trailing '\n') into a fresh string right-padded to width. */
static char	*pad_line(char *src, int width)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(src);
	if (len > 0 && src[len - 1] == '\n')
		len--;
	dst = malloc(width + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < width)
		dst[i++] = ' ';
	dst[width] = '\0';
	return (dst);
}
