/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:16:39 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 18:58:59 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	forward_copy(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

static void	backward_copy(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		i--;
		d[i] = s[i];
	}
}

void	*ft_memmove(void *target, const void *source, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)target;
	s = (const unsigned char *)source;
	if (d == s || n == 0)
	{
		return (target);
	}
	if (d < s)
	{
		forward_copy(d, s, n);
	}
	else
	{
		backward_copy(d, s, n);
	}
	return (target);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	buf[7] = "donkey";

	ft_memmove(buf, "abcdef", 6);
	printf("%s\n", buf);
	return (0);
}
*/