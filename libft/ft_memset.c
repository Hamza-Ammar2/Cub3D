/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:14:47 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 18:59:20 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pointer;
	unsigned char	fill;

	pointer = (unsigned char *)s;
	fill = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		pointer[i] = fill;
		i++;
	}
	return (s);
}

/*
#include <stdio.h>

int	main(void)
{
	char	buf[8] = "donkey";

	ft_memset(buf, 'X', 3);
	printf("%s\n", buf);
	return (0);
}
*/