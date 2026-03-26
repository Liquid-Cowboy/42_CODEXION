/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:01:18 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:19:01 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return (ft_strdup(""));
	while (s1[i] && ft_strchr(set, (int)s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_strchr(set, (int)s1[j - 1]))
		j--;
	return (ft_substr(s1, i, j - i));
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strtrim("! * **!Hello World   !!!*!!", "!* "));
	printf("%d", ft_strtrim("", "!* ")[0]);

	return (0);
}*/
