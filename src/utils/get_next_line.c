/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:39:11 by haammar           #+#    #+#             */
/*   Updated: 2026/07/13 11:27:39 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*clean(int l, char *dup)
{
	if (l < 0)
		return (free(dup), (char *) 0);
	return (dup);
}

static char	*nc(char *dup, t_gnl *gnl)
{
	if (dup)
		return (dup);
	gnl->start = 0;
	gnl->end = 0;
	return ((char *) 0);
}

static char	*iterread(int fd, t_gnl *gnl)
{
	int		l;
	size_t	dl;
	char	*s;
	char	*dup;

	dl = gnl->end - gnl->start;
	dup = 0;
	if (gnl->end > gnl->start)
		dup = append(0, gnl->buf + gnl->start, 0, gnl->end - gnl->start);
	if (gnl->end > gnl->start && !dup)
		return (gnl->start = 0, gnl->end = 0, clean(0, dup));
	while (1)
	{
		l = read(fd, gnl->buf, BUFFER_SIZE);
		if (l <= 0)
			return (gnl->start = 0, gnl->end = 0, clean(l, dup));
		s = find_char(gnl->buf, '\n', l);
		if (s)
			return (gnl->start = 1 + (size_t)(s - gnl->buf),
				gnl->end = l, nc(append(dup, gnl->buf, dl, gnl->start), gnl));
		dup = append(dup, gnl->buf, dl, l);
		if (!dup)
			return (gnl->start = 0, gnl->end = 0, clean(0, dup));
		dl += l;
	}
}

char	*get_next_line(int fd, t_gnl *gnl)
{
	char	*dup;
	char	*s;

	if (fd < 0 || BUFFER_SIZE <= 0 || !gnl)
		return (0);
	if (gnl->end > gnl->start)
	{
		s = find_char(gnl->buf + gnl->start, '\n', gnl->end - gnl->start);
		if (s)
		{
			dup = append(0, gnl->buf + gnl->start, 0,
					(size_t)(s - (gnl->buf + gnl->start)) + 1);
			gnl->start = 1 + (size_t)(s - gnl->buf);
			if (!dup)
				return (gnl->start = 0, gnl->end = 0, clean(0, dup));
			return (dup);
		}
	}
	return (iterread(fd, gnl));
}
