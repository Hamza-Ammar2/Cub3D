/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:15:54 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 19:18:05 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*last;

	last = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			last = (char *)&s[i];
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (last);
}

/*
#include <stdio.h>

int	main(void)
{
	const char	*str = "hello donkey";
	char		*p;

	p = ft_strrchr(str, 'o');
	printf("%s\n", p);
	p = ft_strrchr(str, 'z');
	printf("%p\n", p);
	return (0);
}
*/
