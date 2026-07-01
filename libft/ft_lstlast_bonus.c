/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:31:19 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 21:31:19 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
#include <stdio.h>


int	main(void)
{
	t_list n3 = { "third",  NULL };
	t_list n2 = { "second", &n3  };
	t_list n1 = { "first",  &n2  };

	printf("%s\n", (char *)ft_lstlast(&n1)->content);
	return (0);
}
*/