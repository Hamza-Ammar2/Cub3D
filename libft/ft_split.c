/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:39:31 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 21:25:37 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*get_next_word(const char **s, char c)
{
	int			len;
	const char	*start;
	char		*word;

	len = 0;
	while (**s == c)
		(*s)++;
	if (!**s)
		return (NULL);
	start = *s;
	while (start[len] && start[len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = start[len];
	*s += ft_strlen(word);
	return (word);
}

static void	free_split(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = malloc((words + 1) * sizeof(*array));
	if (!array)
		return (NULL);
	i = 0;
	while (i < words)
	{
		array[i] = get_next_word(&s, c);
		if (!array[i])
			return (free_split(array, i), NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	**array;
	int		j;

	array = ft_split("hello world   42", ' ');
	if (array == NULL)
		return (1);
	j = 0;
	while (array[j] != NULL)
	{
		printf("[%s]\n", array[j]);
		free(array[j]);
		j++;
	}
	free(array);
	return (0);
}
*/
