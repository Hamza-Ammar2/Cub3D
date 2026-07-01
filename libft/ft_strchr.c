/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:14:56 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 19:09:55 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p != '\0')
	{
		if (*p == (char)c)
		{
			return (p);
		}
		p++;
	}
	if ((char)c == '\0')
	{
		return (p);
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*res;

	res = ft_strchr("hello", 'l');
	printf("%s\n", res);
	res = ft_strchr("hello", 'z');
	printf("%p\n", res);
	res = ft_strchr("hello", '\0');
	printf("%s\n", res);
	return (0);
}
*/