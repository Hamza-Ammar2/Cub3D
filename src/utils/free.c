#include "cub3d.h"

/* Free everything: map grid, texture paths, mlx images, window, display. */
void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->frame.ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->frame.ptr);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->config.map)
	{
		i = 0;
		while (game->config.map[i])
			free(game->config.map[i++]);
		free(game->config.map);
	}
	if (game->config.tex_path[0])
		free(game->config.tex_path[0]);
	if (game->config.tex_path[1])
		free(game->config.tex_path[1]);
	if (game->config.tex_path[2])
		free(game->config.tex_path[2]);
	if (game->config.tex_path[3])
		free(game->config.tex_path[3]);
	ft_bzero(game, sizeof(*game));
}
