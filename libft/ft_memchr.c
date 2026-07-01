/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:38:24 by lpons             #+#    #+#             */
/*   Updated: 2025/05/16 23:27:00 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*pointer;

	pointer = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (pointer[i] == (unsigned char)c)
		{
			return ((void *)(pointer + i));
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	const char	*s = "donkey";
	char		*p;

	p = ft_memchr(s, 'k', 6);
	if (p)
		printf("Found 'k' at: %s\n", p);
	else
		printf("Not found\n");
	return (0);
}
*/
