

#include "cub3d.h"

int	handle_rotation(int key, t_game *game)
{
	double rot_speed;

	rot_speed = ROT_SPEED; // small value like 0.05

	if (key == KEY_LEFT)
	{
		game->player.angle -= rot_speed;
	}
	else if (key == KEY_RIGHT)
	{
		game->player.angle += rot_speed;
	}
    else
    {
        return (0); // No rotation key pressed
    }

	// keep angle in range [0, 2π]
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
	if (game->player.angle > 2 * M_PI)
		game->player.angle -= 2 * M_PI;

	return (1);
}

int	key_it(int key, t_game *game)
{
	double move_step;
	double new_x = 0;
	double new_y = 0;

	move_step = MOVE_SPEED * SIZE;

	// Forward / Backward
	if (key == KEY_W || key == KEY_S)
	{
		double dir = (key == KEY_W) ? 1.0 : -1.0;

		new_x = game->player.x + cos(game->player.angle) * move_step * dir;
		new_y = game->player.y + sin(game->player.angle) * move_step * dir;
	}

	// Strafing (left/right)
	if (key == KEY_A || key == KEY_D)
	{
		double dir = (key == KEY_D) ? 1.0 : -1.0;

		new_x = game->player.x + cos(game->player.angle + M_PI_2) * move_step * dir;
		new_y = game->player.y + sin(game->player.angle + M_PI_2) * move_step * dir;
	}
    if (new_x == 0 && new_y == 0){
        return (0);} // No movement key pressed
	game->player.x = new_x;
	game->player.y = new_y;

	return (1);
}

// int	key_it2(int key, t_game *game)
// {
// 	if (key == KEY_A)
// 	{
// 		data->camera.phis[1] += 0.1;
// 		return (1);
// 	}
// 	if (key == KEY_D)
// 	{
// 		data->camera.phis[1] -= 0.1;
// 		return (1);
// 	}
// 	if (key == KEY_W)
// 	{
// 		data->camera.phis[0] += 0.1;
// 		return (1);
// 	}
// 	if (key == KEY_S)
// 	{
// 		data->camera.phis[0] -= 0.1;
// 		return (1);
// 	}
// 	return (0);
// }

// int	key_it3(int key, t_game *game)
// {
// 	if (key == KEY_Q)
// 	{
// 		data->camera.phis[2] += 0.1;
// 		return (1);
// 	}
// 	if (key == KEY_E)
// 	{
// 		data->camera.phis[2] -= 0.1;
// 		return (1);
// 	}
// 	return (0);
// }
