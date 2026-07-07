#include "cub3d.h"

static char	**dup_map(char **map, int height);
static void	flood_fill(t_flood *f, int x, int y);

/*
** Closure test: flood fill a throwaway copy of the grid from the player start.
** If the fill ever reaches a space or the grid edge, the map is not sealed.
*/
int	check_closed(t_game *game)
{
	t_flood	f;

	f.map = dup_map(game->config.map, game->config.map_height);
	if (!f.map)
		return (error_exit("malloc"));
	f.width = game->config.map_width;
	f.height = game->config.map_height;
	f.leaked = 0;
	flood_fill(&f, (int)game->config.start_x, (int)game->config.start_y);
	free_split(f.map);
	if (f.leaked)
		return (error_exit("map is not closed"));
	return (0);
}

/* Duplicate the grid so the fill can mutate it without touching config.map. */
static char	**dup_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			return (free(copy), NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

/* Recursive 4-way fill; marks visited floor 'F', flags leaks to void/edge. */
static void	flood_fill(t_flood *f, int x, int y)
{
	char	c;

	if (x < 0 || y < 0 || y >= f->height || x >= f->width)
	{
		f->leaked = 1;
		return ;
	}
	c = f->map[y][x];
	if (c == ' ')
	{
		f->leaked = 1;
		return ;
	}
	if (c == '1' || c == 'F')
		return ;
	f->map[y][x] = 'F';
	flood_fill(f, x + 1, y);
	flood_fill(f, x - 1, y);
	flood_fill(f, x, y + 1);
	flood_fill(f, x, y - 1);
}
