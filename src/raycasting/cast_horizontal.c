/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_h_step(double ray_angle, double *dy, double *y, double py)
{
	if (sin(ray_angle) > 0)
	{
		*dy = SIZE;
		*y = get_map_index(py) * SIZE + SIZE;
	}
	else
	{
		*dy = -SIZE;
		*y = get_map_index(py) * SIZE;
	}
}

static int	hit_wall_h(t_game *game, double x, double y, double dy)
{
	int	i;
	int	j;

	i = get_map_index(y);
	j = get_map_index(x);
	if (dy < 0)
		i -= 1;
	if (i < 0 || i >= game->config.map_height)
		return (1);
	if (j < 0 || j >= game->config.map_width)
		return (1);
	if (game->config.map[i][j] == '1')
		return (1);
	return (0);
}

static void	trace_h_ray(t_game *game, t_ray *ray)
{
	while (!hit_wall_h(game, ray->x, ray->y, ray->dy))
	{
		ray->x += ray->dx;
		ray->y += ray->dy;
	}
}

t_vect	get_ray_end_horizontal(t_game *game, double ray_angle)
{
	t_player	*player;
	t_ray		ray;
	double		m;
	t_vect		end;

	player = &game->player;
	m = tan(ray_angle);
	init_h_step(ray_angle, &ray.dy, &ray.y, player->y);
	ray.dx = ray.dy / m;
	ray.x = player->x + (ray.y - player->y) / m;
	trace_h_ray(game, &ray);
	end.x = ray.x;
	end.y = ray.y;
	return (end);
}
