/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:16:51 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:18:06 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *) dest;
	if (n <= 0)
		return (dest);
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	return (dest);
}

/*
int	main(void)
{
	char src[] = "Hello World";
	printf("%s\n", (char *)ft_memmove((src + 1), (const char *)src, 12));
	return (0);
}*/
