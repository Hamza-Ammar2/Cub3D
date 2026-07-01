/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:36:54 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 18:52:12 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*pointer;

	total = count * size;
	if (size != 0 && total / size != count)
		return (NULL);
	pointer = malloc(total);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, total);
	return (pointer);
}

/*
#include <stdio.h>

int	main(void)
{
	int	*arr;

	arr = ft_calloc(3, sizeof *arr);
	if (!arr)
		return (1);
	printf("%d\n", arr[1]);
	free(arr);
	return (0);
}
*/
