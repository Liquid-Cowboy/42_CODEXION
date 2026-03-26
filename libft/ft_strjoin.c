/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:45:17 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:18:36 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	total = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *) malloc(sizeof(char) * (total + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, total + 1);
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s", ft_strjoin("Hello", "World"));
	return (0);
}*/
