/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:39:09 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 01:49:44 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*duplicate;

	len = ft_strlen(s1);
	duplicate = malloc(len + 1);
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, s1, len + 1);
	return (duplicate);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	const char	*original = "libft_strduplicate";
	char		*copy;

	copy = ft_strdup(original);
	printf("Original: %s\n", original);
	printf("duplicate: %s\n", copy);
	free(copy);
	return (0);
}
*/