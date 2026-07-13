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

static char	*clean(int l, char **buff, char *dup)
{
	if (l > 0)
		return (dup);
	free(*buff);
	*buff = 0;
	if (l < 0)
		return (free(dup), (char *) 0);
	return (dup);
}

static char	*nc(char *dup, char **buff, size_t *start, size_t *end)
{
	if (dup)
		return (dup);
	*start = 0;
	*end = 0;
	free(*buff);
	*buff = 0;
	return ((char *) 0);
}

static char	*iterread(int fd, char **buff, size_t *start, size_t *end)
{
	int		l;
	size_t	dl;
	char	*s;
	char	*dup;

	dl = *end - *start;
	dup = 0;
	if (*end > *start)
		dup = append(0, *buff + *start, 0, *end - *start);
	if (*end > *start && !dup)
		return (*start = 0, *end = 0, clean(0, buff, dup));
	while (1)
	{
		l = read(fd, *buff, BUFFER_SIZE);
		if (l <= 0)
			return (*start = 0, *end = 0, clean(l, buff, dup));
		s = find_char(*buff, '\n', l);
		if (s)
			return (*start = 1 + (size_t)(s - *buff),
				*end = l, nc(append(dup, *buff, dl, *start), buff, start, end));
		dup = append(dup, *buff, dl, l);
		if (!dup)
			return (*start = 0, *end = 0, clean(0, buff, dup));
		dl += l;
	}
}

char	*get_next_line(int fd)
{
	static char		*buff;
	static size_t	start;
	static size_t	end;
	char			*dup;
	char			*s;

	if (!buff)
	{
		buff = malloc(sizeof(char) * BUFFER_SIZE);
		if (!buff)
			return (0);
	}
	if (end > start)
	{
		s = find_char(buff + start, '\n', end - start);
		if (s)
		{
			dup = append(0, buff + start, 0, (size_t)(s - (buff + start)) + 1);
			start = 1 + (size_t)(s - buff);
			if (!dup)
				return (start = 0, end = 0, clean(0, &buff, dup));
			return (dup);
		}
	}
	return (iterread(fd, &buff, &start, &end));
}
