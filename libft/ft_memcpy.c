/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:14:33 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 18:58:49 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *target, const void *source, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (target == source || n == 0)
		return (target);
	d = (unsigned char *)target;
	s = (const unsigned char *)source;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (target);
}

/*
#include <stdio.h>

int	main(void)
{
	char	buffer[12] = "1234567890";

	ft_memcpy(buffer + 3, "ABC", 3);
	printf("%s\n", buffer);
	return (0);
}
*/