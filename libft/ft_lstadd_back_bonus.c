/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:30:25 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 21:30:25 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = *lst;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new;
}

/*
#include <stdio.h>

int	main(void)
{
	t_list *list = NULL;

	ft_lstadd_back(&list, ft_lstnew("first"));
	ft_lstadd_back(&list, ft_lstnew("second"));

	printf("%s\n", (char *)list->next->content);

	return (0);
}
*/
