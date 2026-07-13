/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:08:34 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:08:34 by haammar          ###   ########.fr       */
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

static void	free_imgs(t_game *game)
{
	int	i;

	if (!game->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].ptr)
			mlx_destroy_image(game->mlx, game->textures[i].ptr);
		i++;
	}
	if (game->frame.ptr)
		mlx_destroy_image(game->mlx, game->frame.ptr);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_imgs(game);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game);
	free_textures(game);
	ft_bzero(game, sizeof(*game));
}
