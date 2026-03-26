/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:59:27 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:17:23 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static
char	*ft_putnbr(int n, char *dest, int *i)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		dest[*i] = '-';
		nbr = -nbr;
		(*i)++;
	}
	if (nbr < 10)
		dest[*i] = (nbr + '0');
	else
		ft_putnbr(nbr / 10, dest, i);
	dest[*i] = ((nbr % 10) + '0');
	(*i)++;
	return (dest);
}

char	*ft_itoa(int n)
{
	long	digits;
	long	nbr;
	char	*dest;
	int		i;

	i = 0;
	digits = 1;
	nbr = (long)n;
	if (nbr < 0)
	{
		digits++;
		nbr = -nbr;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		digits++;
	}
	dest = (char *)malloc(sizeof(char) * (digits + 1));
	if (!dest)
		return (NULL);
	dest = ft_putnbr(n, dest, &i);
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char *il = ft_itoa(2147483647);
	printf("%s", il);
}
*/
