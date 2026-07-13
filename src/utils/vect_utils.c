/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:09:04 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:09:04 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_distance(t_vect start, t_vect end)
{
	double	dx;
	double	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}

int	get_map_index(double v)
{
	return ((int)(v / SIZE));
}

void	normalize_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}
