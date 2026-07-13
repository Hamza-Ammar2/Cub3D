/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:08:28 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 12:08:28 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	return (1);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
