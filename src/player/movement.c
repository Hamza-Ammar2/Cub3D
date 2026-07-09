#include "cub3d.h"

/*
** Apply held-key state each frame: WASD translate the position vector,
** left/right arrows rotate the facing angle.
*/
int	update_player(t_game *game)
{
	t_player	*player;
	double		speed;

	player = &game->player;
	speed = MOVE_SPEED * SIZE;
	if (game->keys.w)
	{
		player->x += cos(player->angle) * speed;
		player->y += sin(player->angle) * speed;
	}
	if (game->keys.s)
	{
		player->x -= cos(player->angle) * speed;
		player->y -= sin(player->angle) * speed;
	}
	if (game->keys.a)
	{
		player->x -= cos(player->angle + PI / 2.0) * speed;
		player->y -= sin(player->angle + PI / 2.0) * speed;
	}
	if (game->keys.d)
	{
		player->x += cos(player->angle + PI / 2.0) * speed;
		player->y += sin(player->angle + PI / 2.0) * speed;
	}
	if (game->keys.left)
		player->angle -= ROT_SPEED;
	if (game->keys.right)
		player->angle += ROT_SPEED;
	return (0);
}
