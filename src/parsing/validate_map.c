#include "cub3d.h"

static int	check_chars(t_game *game, int *player_count);
static int	check_cell(t_game *game, int x, int y, int *pc);
static void	set_player(t_game *game, int x, int y);

/*
** Validate the built grid: only legal chars + exactly one player start
** (check_chars), then confirm the map is sealed by walls (check_closed).
*/
int	validate_map(t_game *game)
{
	int	player_count;

	player_count = 0;
	if (check_chars(game, &player_count))
		return (1);
	if (player_count != 1)
		return (error_exit("need exactly 1 player"));
	if (check_closed(game))
		return (1);
	return (0);
}

/* Walk every cell, validating the character and counting player starts. */
static int	check_chars(t_game *game, int *player_count)
{
	int	y;
	int	x;

	*player_count = 0;
	y = 0;
	while (y < game->config.map_height)
	{
		x = 0;
		while (x < game->config.map_width)
		{
			if (check_cell(game, x, y, player_count))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

/* Classify one cell: floor/wall/space ok, N/S/E/W is a player, else error. */
static int	check_cell(t_game *game, int x, int y, int *pc)
{
	char	c;

	c = game->config.map[y][x];
	if (ft_strchr("NSEW", c))
	{
		(*pc)++;
		set_player(game, x, y);
	}
	else if (!ft_strchr("01 ", c))
		return (error_exit("invalid char in map"));
	return (0);
}

/* Record the spawn (centered on the tile) and replace it with floor. */
static void	set_player(t_game *game, int x, int y)
{
	game->config.start_x = x + 0.5;
	game->config.start_y = y + 0.5;
	game->config.start_dir = game->config.map[y][x];
	game->config.map[y][x] = '0';
}
