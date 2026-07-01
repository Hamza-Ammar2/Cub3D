/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:12:25 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 18:51:44 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*pointer;

	pointer = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		pointer[i] = 0;
		i++;
	}
}

/*
#include <unistd.h>

int	main(void)
{
	int		j;
	char	buffer[8] = "donkeeey";

	j = 0;
	ft_bzero(buffer, 5);
	while(j < 8)
	{
		write(1, &buffer[j], 1);
		j ++;
	}
}
*/
