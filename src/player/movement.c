#include "cub3d.h"

/*
** Apply held-key state each frame: WASD translate the position vector (with
** wall collision checks), left/right arrows rotate dir + camera plane.
*/



int	update_player(t_game *game)
{
	t_player *player = &game->player;
	double speed = MOVE_SPEED * SIZE;

	if (player->move_forward)
	{
		player->x += cos(player->angle) * speed;
		player->y += sin(player->angle) * speed;
	}
	if (player->move_backward)
	{
		player->x -= cos(player->angle) * speed;
		player->y -= sin(player->angle) * speed;
	}
	if (player->move_left)
	{
		player->x -= cos(player->angle + PI / 2) * speed;
		player->y -= sin(player->angle + PI / 2) * speed;
	}
	if (player->move_right)
	{
		player->x += cos(player->angle + PI / 2) * speed;
		player->y += sin(player->angle + PI / 2) * speed;
	}
	if (player->rotate_left)
		player->angle -= ROT_SPEED;
	if (player->rotate_right)
		player->angle += ROT_SPEED;
	return (1);
}
