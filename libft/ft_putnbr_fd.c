/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:59:58 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:18:19 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		write (fd, "-", 1);
		nbr = -nbr;
	}
	if (nbr < 10)
		write (fd, &"0123456789"[nbr], 1);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		write (fd, &"0123456789"[nbr % 10], 1);
	}
}
