/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:46:57 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 20:28:53 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	init_all(struct s_compiler *compiler);
void	init_coders(struct s_compiler *compiler);
void	init_dongles(struct s_compiler *compiler);

void	init_all(struct s_compiler *compiler)
{
	init_coders(compiler);
	init_dongles(compiler);
	compiler->monitor.stop = 0;
}

void	init_coders(struct s_compiler *compiler)
{
	int			i;
	int			left;
	int			right;
	int			nb_cod;

	nb_cod = compiler->hub.number_of_coders;
	i = -1;
	while (++i < nb_cod)
	{
		left = (i + nb_cod - 1) % nb_cod;
		right = (i + 1) % nb_cod;
		compiler->coders[i].compiler = compiler;
		compiler->coders[i].l_dongle = &compiler->dongles[left];
		compiler->coders[i].r_dongle = &compiler->dongles[right];
		compiler->coders[i].id = i + 1;
		compiler->coders[i].compiles_left = (
				compiler->hub.number_of_compiles_required);
		compiler->coders[i].comp_st = 0;
		compiler->coders[i].ref_end = 0;
		compiler->coders[i].burned_out = 0;
	}
}

void	init_dongles(struct s_compiler *compiler)
{
	int	i;
	int	nb_cod;
	int	first;
	int	second;

	i = -1;
	nb_cod = compiler->hub.number_of_coders;
	while (++i < nb_cod)
	{
		first = (i + 1) % nb_cod;
		second = (i + nb_cod - 1) % nb_cod;
		compiler->dongles[i].heap[0] = &compiler->coders[first];
		compiler->dongles[i].heap[1] = &compiler->coders[second];
		compiler->dongles[i].in_use = 0;
		compiler->dongles[i].last_used = 0;
	}
}
