/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:16:29 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 18:58:38 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*d1 = (const unsigned char *)s1;
	const unsigned char	*d2 = (const unsigned char *)s2;

	i = 0;
	while (i < n)
	{
		if (d1[i] != d2[i])
			return ((int)d1[i] - (int)d2[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*donkey;
	int		result1;
	int		result2;
	int		result3;
	int		result4;

	donkey = "donkey";
	result1 = ft_memcmp(donkey, "donkey", 6);
	printf("result1: %d1\n", result1);
	result2 = ft_memcmp(donkey, "donkex", 6);
	printf("result2: %d1\n", result2);
	return (0);
}
*/
