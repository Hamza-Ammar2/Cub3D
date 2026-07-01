/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:16:03 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 19:18:51 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%c\n", ft_tolower('B'));
	printf("%c\n", ft_tolower('a'));
	printf("%c\n", ft_tolower('1'));
	return (0);
}
*/
