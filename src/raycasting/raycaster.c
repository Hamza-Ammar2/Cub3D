/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_wall_side(t_game *game, t_vect end, double ray_angle)
{
	double	eps;

	eps = 0.0001;
	(void)game;
	if (fmod(end.x, SIZE) < eps)
	{
		if (cos(ray_angle) > 0)
			return (EAST);
		return (WEST);
	}
	if (sin(ray_angle) > 0)
		return (SOUTH);
	return (NORTH);
}

t_rect	getuv_rect(t_game *game, t_vect end, double ray_angle)
{
	t_rect	uv;
	int		side;

	side = get_wall_side(game, end, ray_angle);
	uv.width = 1;
	uv.height = game->textures[side].height;
	uv.x = (int)(fmod(end.x, SIZE) * game->textures[side].width / SIZE);
	if (side == SOUTH)
		uv.x = game->textures[side].width - uv.x - 1;
	else if (side == EAST || side == WEST)
		uv.x = (int)(fmod(end.y, SIZE) * game->textures[side].width / SIZE);
	if (side == WEST)
		uv.x = game->textures[side].width - uv.x - 1;
	uv.y = 0;
	game->config.cur_side = side;
	return (uv);
}

void	cast_rays(t_game *game)
{
	double	ray_angle;
	t_vect	ray_end;
	int		i;
	double	dist;
	int		line_h;

	ray_angle = game->player.angle - (FOV_SCALE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_end = get_end(game, ray_angle);
		dist = get_distance((t_vect){game->player.x, game->player.y}, ray_end);
		dist *= cos(ray_angle - game->player.angle);
		line_h = (int)(WIN_HEIGHT * SIZE / dist);
		draw_column(game, getuv_rect(game, ray_end, ray_angle),
			i * (WIN_WIDTH / NUM_RAYS), line_h);
		ray_angle += FOV_SCALE / NUM_RAYS;
		i++;
	}
}
