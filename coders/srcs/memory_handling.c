/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:32:13 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 11:18:11 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int		compiler_init(struct s_compiler **compiler, int argc, char **argv);
void	free_compiler(struct s_compiler *compiler, int stage, int heap_i);

int	compiler_init(struct s_compiler **compiler, int argc, char **argv)
{
	int	i;
	int	nb_cod;

	*compiler = (t_compiler *)malloc(sizeof(t_compiler));
	if (!*compiler)
		return (1);
	if (parser(*compiler, argc, argv) != 0)
		return (free_compiler(*compiler, 1, 0), 1);
	nb_cod = (*compiler)->hub.number_of_coders;
	(*compiler)->coders = (t_coder *)malloc(sizeof(t_coder) * nb_cod);
	if (!(*compiler)->coders)
		return (free_compiler(*compiler, 2, 0), 1);
	(*compiler)->dongles = (t_dongle *)malloc(sizeof(t_dongle) * nb_cod);
	if (!(*compiler)->dongles)
		return (free_compiler(*compiler, 3, 0), 1);
	i = -1;
	while (++i < nb_cod)
	{
		(*compiler)->dongles[i].heap = (t_coder **)malloc(sizeof
				(t_coder*)*2);
		if (!(*compiler)->dongles[i].heap)
			return (free_compiler(*compiler, 4, i), 1);
	}
	return (0);
}

void	free_compiler(struct s_compiler *compiler, int stage, int heap_i)
{
	int	i;

	if (stage > 1)
	{
		free(compiler->coders);
		if (stage > 2)
		{
			free(compiler->dongles);
			if (stage > 3)
			{
				i = -1;
				while (++i < heap_i)
					free(compiler->dongles[i].heap);
			}
		}
	}
	free(compiler);
}
