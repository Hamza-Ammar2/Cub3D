

#include "cub3d.h"

void	clear_image(t_img *img)
{
	unsigned char	*p;
	int				i;

	p = (unsigned char *)img->addr;
	i = 0;
	while (i < img->line_len * WIN_HEIGHT)
	{
		p[i] = 0;
		i++;
	}
}

double	get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0));
}

int	game_loop(void *param)
{
	t_game		*game = (t_game *)param;
	double		now;
	double		elapsed;
	double		frame_ms;

	frame_ms = 1000.0 / game->timing.target_fps;
	now = get_time_ms();
	elapsed = now - game->timing.last_frame;
	if (elapsed < frame_ms)
		return (0);
	game->timing.last_frame = now;
    clear_image(&game->frame);
    update_player(game);
	render_frame(game);
	return (0);
}