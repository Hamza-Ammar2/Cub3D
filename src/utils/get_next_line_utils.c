/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:57:05 by haammar           #+#    #+#             */
/*   Updated: 2026/01/04 16:25:21 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*append(char *s1, char *s2, size_t l1, size_t l2)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = malloc((l1 + l2 + 1) * sizeof(char));
	if (s1 && !dup)
		free(s1);
	if (!dup)
		return (0);
	while (i < l1)
	{
		dup[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		dup[i] = s2[i - l1];
		i++;
	}
	dup[i] = '\0';
	if (s1)
		free(s1);
	return (dup);
}

char	*find_char(char *s, char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}
