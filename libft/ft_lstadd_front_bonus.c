/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:30:39 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 21:30:39 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
	{
		return ;
	}
	new->next = *lst;
	*lst = new;
}

/*
#include <stdio.h>

int	main(void)
{
	t_list *list = NULL;

	ft_lstadd_front(&list, ft_lstnew("donkey"));
	ft_lstadd_front(&list, ft_lstnew("hello"));

	printf("%s %s\n",
			(char *)list->content,
			(char *)list->next->content);

	return (0);
}
*/
