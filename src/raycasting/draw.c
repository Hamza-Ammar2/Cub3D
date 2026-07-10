/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile(t_game *game, int i, int j)
{
	t_rect	rect;
	int		color;

	rect.x = j * SIZE;
	rect.y = i * SIZE;
	rect.width = SIZE;
	rect.height = SIZE;
	if (game->config.map[i][j] == '1')
		color = 0xFFFFFF;
	else
		color = 0x000000;
	draw_rect(game, rect, color);
}

void	draw_map2d(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->config.map_height)
	{
		j = 0;
		while (j < game->config.map_width)
		{
			draw_tile(game, i, j);
			j++;
		}
		i++;
	}
}

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

static void	step_line(t_vect *p0, int *err, t_rect *b)
{
	if (*err * 2 > -b->height)
	{
		*err -= b->height;
		p0->x += b->x;
	}
	if (*err * 2 < b->width)
	{
		*err += b->width;
		p0->y += b->y;
	}
}

void	draw_line(t_game *game, t_vect p0, t_vect p1, int color)
{
	t_rect	b;
	int		err;

	b.width = fabs(p1.x - p0.x);
	b.height = fabs(p1.y - p0.y);
	b.x = 1 - 2 * (p0.x >= p1.x);
	b.y = 1 - 2 * (p0.y >= p1.y);
	err = b.width - b.height;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		put_pixel(&game->frame, p0.x, p0.y, color);
		step_line(&p0, &err, &b);
	}
	put_pixel(&game->frame, p1.x, p1.y, color);
}
