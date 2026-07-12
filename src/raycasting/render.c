/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_game *game, int x, int start_y)
{
	t_rect	rect;

	if (start_y <= 0)
		return ;
	rect.x = x;
	rect.y = 0;
	rect.width = WIN_WIDTH / NUM_RAYS;
	rect.height = start_y;
	draw_rect(game, rect, game->config.ceiling_color);
}

static void	draw_floor(t_game *game, int x, int start_y, int line_h)
{
	t_rect	rect;
	int		floor_y;

	floor_y = start_y + line_h;
	if (floor_y >= WIN_HEIGHT)
		return ;
	rect.x = x;
	rect.y = floor_y;
	rect.width = WIN_WIDTH / NUM_RAYS;
	rect.height = WIN_HEIGHT - floor_y;
	draw_rect(game, rect, game->config.floor_color);
}

void	draw_column(t_game *game, t_rect uv, int x, int line_h)
{
	int		start_y;
	t_rect	rect;

	start_y = (WIN_HEIGHT - line_h) / 2;
	rect.x = x;
	rect.y = start_y * (line_h < WIN_HEIGHT);
	rect.width = WIN_WIDTH / NUM_RAYS;
	rect.height = line_h;
	if (line_h > WIN_HEIGHT)
		rect.height = WIN_HEIGHT;
	draw_img(&game->frame, &game->textures[game->config.cur_side], uv, rect);
	draw_ceiling(game, x, start_y);
	draw_floor(game, x, start_y, line_h);
}

int	render_frame(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	return (0);
}
