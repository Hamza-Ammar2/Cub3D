/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:31:32 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 21:31:32 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	t_list *n = ft_lstnew("hello");
	if (n)
	{
		printf("Content: %s\n", (char *)n->content);
		printf("Next:    %p\n", (void *)n->next);
		free(n);
	}
	return (0);
}
*/