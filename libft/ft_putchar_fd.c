/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:46:08 by mnogueir          #+#    #+#             */
/*   Updated: 2025/10/17 17:18:13 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

/*
#include <stdio.h>


int	main(void)
{
	write (1, "Teste stdout: ", 14);
	ft_putchar_fd('A', 1);
	ft_putchar_fd('\n', 1);

	write (2, "Teste stderr: ", 14);
	ft_putchar_fd('A', 2);
	ft_putchar_fd('\n', 2);	
}*/
