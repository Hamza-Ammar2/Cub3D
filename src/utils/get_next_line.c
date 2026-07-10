/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:39:11 by haammar           #+#    #+#             */
/*   Updated: 2026/01/24 03:02:55 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		g_buf[BUFFER_SIZE];
static size_t	g_pos;
static size_t	g_len;

static int	refill(int fd, char *buf, size_t *pos, size_t *len)
{
	int	r;

	r = read(fd, buf, BUFFER_SIZE);
	if (r <= 0)
		return (r);
	*pos = 0;
	*len = (size_t)r;
	return (r);
}

static int	take_chunk(t_line *ln, char *buf, size_t *pos, size_t len)
{
	char	*nl;
	size_t	n;
	int		found;

	nl = find_char(buf + *pos, '\n', len - *pos);
	found = (nl != NULL);
	if (found)
		n = (size_t)(nl - (buf + *pos)) + 1;
	else
		n = len - *pos;
	ln->str = append(ln->str, buf + *pos, ln->len, n);
	*pos += n;
	if (!ln->str)
		return (-1);
	ln->len += n;
	return (found);
}

static int	fill_line(int fd, t_line *ln)
{
	int	status;

	status = 0;
	while (status == 0)
	{
		if (g_pos >= g_len)
		{
			status = refill(fd, g_buf, &g_pos, &g_len);
			if (status <= 0)
				return (status);
			status = 0;
		}
		status = take_chunk(ln, g_buf, &g_pos, g_len);
	}
	return (status);
}

char	*get_next_line(int fd)
{
	t_line	ln;
	int		status;

	if (fd < 0)
		return (NULL);
	ln.str = NULL;
	ln.len = 0;
	status = fill_line(fd, &ln);
	if (status < 0)
	{
		free(ln.str);
		return (NULL);
	}
	return (ln.str);
}
