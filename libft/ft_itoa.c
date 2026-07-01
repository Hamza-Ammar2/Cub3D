/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:37:21 by lpons             #+#    #+#             */
/*   Updated: 2025/05/17 20:18:03 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*string;

	nb = (long)n;
	len = count_digits(nb);
	string = malloc(len + 1);
	if (!string)
		return (NULL);
	string[len] = '\0';
	if (nb < 0)
	{
		string[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		string[--len] = '0';
	while (nb > 0)
	{
		string[--len] = '0' + (nb % 10);
		nb /= 10;
	}
	return (string);
}

/*
#include <stdlib.h>

int	main(void)
{
	ft_itoa(0)
	return (ft_itoa(0)[0] - '0');
}
*/
