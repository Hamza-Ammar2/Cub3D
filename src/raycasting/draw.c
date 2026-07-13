/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:08:09 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:08:09 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_game *game, t_rect rect, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			put_pixel(&game->frame, rect.x + j, rect.y + i, color);
			j++;
		}
		i++;
	}
}
