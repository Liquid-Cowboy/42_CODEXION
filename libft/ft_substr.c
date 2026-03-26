/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:00:20 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:19:04 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			start_size;
	char			*substr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
	{
		return (ft_strdup(""));
	}
	start_size = ft_strlen(s + start);
	if (start_size < len)
		len = start_size;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s", ft_substr("Hello World", 5, 3));
	return (0);
}*/
