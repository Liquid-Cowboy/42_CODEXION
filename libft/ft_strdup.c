/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:50:59 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:18:31 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	count;

	count = ft_strlen(s);
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, (count + 1));
	return (str);
}
