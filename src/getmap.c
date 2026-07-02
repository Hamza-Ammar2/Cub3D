

#include "cub3d.h"

static char	**append_ptr(char **strs, char *str)
{
	int		n;
	char	**apd;

	n = 0;
	while (strs && strs[n])
		n++;
	apd = malloc(sizeof(char *) * (n + 2));
	n = 0;
	while (strs && strs[n])
	{
		apd[n] = strs[n];
		n++;
	}
	if (strs)
		free(strs);
	return (apd[n] = str, apd[n + 1] = 0, apd);
}

void	get_map(char *file, t_game *game)
{
	int		fd;
	char	**strs;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	str = get_next_line(fd);
    printf("First line of the map: %s\n", str); // Debugging line
	game->config.map_width = ft_strlen(str);
	strs = 0;
	game->config.map_height = 0;
	while (str)
	{
		strs = append_ptr(strs, str);
		str = get_next_line(fd);
		game->config.map_height++;
	}
	game->config.map = strs;
    close(fd);
}
