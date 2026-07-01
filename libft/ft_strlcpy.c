/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:15:17 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 19:13:23 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *target, const char *source, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (source[i])
		i++;
	if (size > 0)
	{
		while (source[j] && j < size - 1)
		{
			target[j] = source[j];
			j++;
		}
		target[j] = '\0';
	}
	return (i);
}

/*
#include <stdio.h>

int	main(void)
{
	char	buffer[10];
	size_t	ret;

	ret = ft_strlcpy(buffer, "hello", 3);
	printf("Copied: '%s'\n", buffer);
	printf("Length: %zu\n", ret);
	return (0);
}
*/