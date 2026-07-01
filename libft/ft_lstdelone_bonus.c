/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:31:08 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 21:31:08 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	t_list *node = ft_lstnew(strdup("donkey"));
	ft_lstdelone(node, free);
	printf("ft_lstdelone OK\n");
	return (0);
}
*/