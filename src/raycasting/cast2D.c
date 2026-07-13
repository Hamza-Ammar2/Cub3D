/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast2D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:08:04 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:08:04 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vect	get_end(t_game *game, double ray_angle)
{
	t_player	*player;
	t_vect		a;
	t_vect		b;
	double		dist_a;
	double		dist_b;

	player = &game->player;
	a = get_ray_end_horizontal(game, ray_angle);
	b = get_ray_end(game, ray_angle);
	dist_a = pow(a.x - player->x, 2) + pow(a.y - player->y, 2);
	dist_b = pow(b.x - player->x, 2) + pow(b.y - player->y, 2);
	if (dist_a < dist_b)
		return (a);
	return (b);
}
