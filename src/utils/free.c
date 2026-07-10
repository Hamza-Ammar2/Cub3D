/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukep <lukep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by lukep             #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by lukep            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_textures(t_game *game)
{
	if (game->config.tex_path[0])
		free(game->config.tex_path[0]);
	if (game->config.tex_path[1])
		free(game->config.tex_path[1]);
	if (game->config.tex_path[2])
		free(game->config.tex_path[2]);
	if (game->config.tex_path[3])
		free(game->config.tex_path[3]);
}

static void	free_map(t_game *game)
{
	int	i;

	if (!game->config.map)
		return ;
	i = 0;
	while (game->config.map[i])
		free(game->config.map[i++]);
	free(game->config.map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->frame.ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->frame.ptr);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free_map(game);
	free_textures(game);
	ft_bzero(game, sizeof(*game));
}
