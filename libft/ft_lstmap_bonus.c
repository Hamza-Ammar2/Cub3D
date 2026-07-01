/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:38:06 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 18:57:17 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	*duplicate(void *content)
{
	return (strdup((char *)content));
}

int	main(void)
{
	t_list	*lst;
	t_list	*mapped;

	lst = ft_lstnew(strdup("hello"));
	mapped = ft_lstmap(lst, duplicate, free);
	printf("%s\n", (char *)mapped->content);
	ft_lstclear(&lst,    free);
	ft_lstclear(&mapped, free);
	return (0);
}
*/