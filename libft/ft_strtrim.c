/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:39:49 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 20:35:05 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*result;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, *end))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	return (result);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*trimmed;

	trimmed = ft_strtrim("  hello  ", " ");
	printf("[%s]\n", trimmed);
	free(trimmed);
	trimmed = ft_strtrim("xxabcxx", "x");
	printf("[%s]\n", trimmed);
	free(trimmed);
	trimmed = ft_strtrim("abcd", "xyz");
	printf("[%s]\n", trimmed);
	free(trimmed);
	return (0);
}
*/
