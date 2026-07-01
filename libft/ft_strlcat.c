/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:15:05 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 19:13:01 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
		j++;
	if (size <= i)
		return (j + size);
	k = 0;
	while (src[k] && i + k < size - 1)
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (i + j);
}

/*
#include <stdio.h>

int	main(void)
{
	char	buffer[12] = "yo";
	size_t	ret;

	ret = ft_strlcat(buffer, "hello", 12);
	printf("%zu\n", ret);
	printf("%s\n", buffer);
	return (0);
}
*/
