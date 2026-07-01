/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:39:21 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 20:02:36 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	total;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total = len1 + len2 + 1;
	res = malloc(total);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, total);
	ft_strlcat(res, s2, total);
	return (res);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*joined;

	joined = ft_strjoin("Hello, Donkey!");
	printf("%s\n", joined);
	free(joined);
	return (0);
}
*/
