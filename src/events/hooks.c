#include "cub3d.h"

/* Key pressed: set the matching flag in game->keys (ESC quits immediately). */
int	handle_keypress(int key, t_game *game)
{
	if (!game)
		return (0);
	if (key == KEY_ESC)
		handle_close(game);
	else if (key == KEY_W)
		game->keys.w = 1;
	else if (key == KEY_A)
		game->keys.a = 1;
	else if (key == KEY_S)
		game->keys.s = 1;
	else if (key == KEY_D)
		game->keys.d = 1;
	else if (key == KEY_LEFT)
		game->keys.left = 1;
	else if (key == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

/* Key released: clear the matching flag in game->keys. */
int	handle_keyrelease(int key, t_game *game)
{
	if (!game)
		return (0);
	if (key == KEY_W)
		game->keys.w = 0;
	else if (key == KEY_A)
		game->keys.a = 0;
	else if (key == KEY_S)
		game->keys.s = 0;
	else if (key == KEY_D)
		game->keys.d = 0;
	else if (key == KEY_LEFT)
		game->keys.left = 0;
	else if (key == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

/* Red cross on the window frame: clean shutdown. */
int	handle_close(t_game *game)
{
	if (!game)
		exit(0);
	free_game(game);
	exit(0);
	return (0);
}
