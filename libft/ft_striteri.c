/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:00:21 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:18:34 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void	ft_my_ft(unsigned int i, char *c)
{
	(void)i;
	*c = '%';
}

#include <stdio.h>
int	main(int argc, char **argv)
{
	(void)argc;
	ft_striteri(argv[1], ft_my_ft);
	printf("%s", argv[1]);
	return (0);
}*/
