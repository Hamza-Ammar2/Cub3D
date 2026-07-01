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

#include "../../includes/cub3d.h"

typedef struct s_line
{
	char	*str;
	size_t	len;
}	t_line;

/* Refill the static buffer from fd. Returns bytes read (0 = EOF, <0 = err). */
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

/* Append the next chunk of buf to ln. Returns 1 if a '\n' was reached,
** 0 if the buffer was consumed without one, -1 on allocation failure. */
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

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static size_t	pos;
	static size_t	len;
	t_line			ln;
	int				status;

	if (fd < 0)
		return (NULL);
	ln.str = NULL;
	ln.len = 0;
	status = 0;
	while (status == 0)
	{
		if (pos >= len)
		{
			status = refill(fd, buf, &pos, &len);
			if (status < 0)
				return (free(ln.str), NULL);
			if (status == 0)
				break ;
			status = 0;
		}
		status = take_chunk(&ln, buf, &pos, len);
	}
	if (status < 0)
		return (free(ln.str), NULL);
	return (ln.str);
}
