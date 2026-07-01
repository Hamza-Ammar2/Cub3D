/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:31:00 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 21:31:00 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	t_list *list = NULL;

	// build a list with two nodes
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("one")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("two")));

	// clear the list
	ft_lstclear(&list, free);

	// should print "0" if list is now empty
	printf("%d\n", ft_lstsize(list));

	return (0);
}
*/
