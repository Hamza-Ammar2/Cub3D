#include "cub3d.h"

/* Key pressed: set the matching flag in game->keys (ESC quits immediately). */
int	handle_keypress(int key, t_game *game)
{
	(void)key;
	(void)game;
	return (0);
}

/* Key released: clear the matching flag in game->keys. */
int	handle_keyrelease(int key, t_game *game)
{
	(void)key;
	(void)game;
	return (0);
}

/* Red cross on the window frame: clean shutdown. */
int	handle_close(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
