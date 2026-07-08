#include "cub3d.h"

static char	**dup_map(char **map, int height);
static int	touches_void(char **map, int width, int height, int x, int y);

/* Closure test: every walkable tile must be surrounded by non-void tiles. */
int	check_closed(t_game *game)
{
	char	**copy;
	int		x;
	int		y;

	copy = dup_map(game->config.map, game->config.map_height);
	if (!copy)
		return (error_exit("malloc"));
	y = 0;
	while (y < game->config.map_height)
	{
		x = 0;
		while (x < game->config.map_width)
		{
			if (copy[y][x] == '0' && touches_void(copy, game->config.map_width,
					game->config.map_height, x, y))
				return (free_split(copy), error_exit("map is not closed"));
			x++;
		}
		y++;
	}
	free_split(copy);
	return (0);
}

/* Duplicate the grid so closure checks can run without touching config.map. */
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
			return (free_split(copy), NULL);
		i++;
	}
	return (copy);
}

/* True when a walkable tile touches map edge or void space in 4-neighbours. */
static int	touches_void(char **map, int width, int height, int x, int y)
{
	if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
		return (1);
	if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
		return (1);
	if (map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
		return (1);
	return (0);
}
