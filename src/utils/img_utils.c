

#include "cub3d.h"

void	draw_img(t_img *frame, t_img *src, t_rect src_rect, t_rect dst)
{
	int     i;
    int     j;
    int     color;
    int     src_x;
    int     src_y;
    char    *src_pixel;

    i = 0;
    while (i < dst.height)
    {
        j = 0;
        while (j < dst.width)
        {
            // FIX: Keep src_x locked to the ray's sample point instead of stretching it
            src_x = src_rect.x + (j * src_rect.width) / dst.width;
            
            src_y = src_rect.y + (i * src_rect.height) / dst.height;
            src_pixel = src->addr + src_y * src->line_len
                + src_x * (src->bpp / 8);
            color = *(unsigned int *)src_pixel;
            put_pixel(frame, dst.x + j, dst.y + i, color);
            j++;
        }
        i++;
    }
}

int	load_image(t_game *game, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->ptr)
	{
		fprintf(stderr, "Error: failed to load image: %s\n", path);
		return (-1);
	}
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
	{
		fprintf(stderr, "Error: failed to get image data: %s\n", path);
		mlx_destroy_image(game->mlx, img->ptr);
		return (-1);
	}
	return (0);
}
