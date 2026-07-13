/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:07:50 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:07:50 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_v_step(double ray_angle, double *dx, double *x, double px)
{
	if (cos(ray_angle) > 0)
	{
		*dx = SIZE;
		*x = get_map_index(px) * SIZE + SIZE;
	}
	else
	{
		*dx = -SIZE;
		*x = get_map_index(px) * SIZE;
	}
}

static int	hit_wall_v(t_game *game, double x, double y, double dx)
{
	int	i;
	int	j;

	i = get_map_index(y);
	j = get_map_index(x);
	if (dx < 0)
		j -= 1;
	if (i < 0 || i >= game->config.map_height)
		return (1);
	if (j < 0 || j >= game->config.map_width)
		return (1);
	if (game->config.map[i][j] == '1')
		return (1);
	return (0);
}

static void	trace_v_ray(t_game *game, t_ray *ray)
{
	while (!hit_wall_v(game, ray->x, ray->y, ray->dx))
	{
		ray->x += ray->dx;
		ray->y += ray->dy;
	}
}

t_vect	get_ray_end(t_game *game, double ray_angle)
{
	t_player	*player;
	t_ray		ray;
	double		m;
	t_vect		end;

	player = &game->player;
	m = tan(ray_angle);
	init_v_step(ray_angle, &ray.dx, &ray.x, player->x);
	ray.dy = m * ray.dx;
	ray.y = player->y + m * (ray.x - player->x);
	trace_v_ray(game, &ray);
	end.x = ray.x;
	end.y = ray.y;
	return (end);
}
