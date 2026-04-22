/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:30:35 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/22 16:01:35 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	print_compiler(struct s_hub_stats compiler);
void	print_help(void);

void	print_compiler(struct s_hub_stats compiler)
{
	printf(
		"\n\n======Compiler stats======\n"
		"Number of coders: %d\n"
		"Time to burnout: %d\n"
		"Time to compile: %d\n"
		"Time to debug: %d\n"
		"Time to refactor: %d\n"
		"Number of compiles required: %d\n"
		"Dongle cooldown: %d\n"
		"Scheduler: %s\n\n\n",
		compiler.number_of_coders,
		compiler.time_to_burnout,
		compiler.time_to_compile,
		compiler.time_to_debug,
		compiler.time_to_refactor,
		compiler.number_of_compiles_required,
		compiler.dongle_cooldown,
		compiler.scheduler);
}

int	main(int argc, char **argv)
{
	t_compiler	*compiler;
	int			nb_cod;
	int			err;

	if (argc == 2 && strcmp(argv[1], "--help") == 0)
		return (printf(HELP), 0);
	err = compiler_init(&compiler, argc, argv);
	if (err)
		return (err);
	nb_cod = compiler->hub.number_of_coders;
	init_all(compiler);
	err = start_threads(compiler);
	if (err)
		return (free_compiler(compiler, 4, nb_cod), err);
	err = join_threads(compiler, nb_cod);
	if (err)
		return (free_compiler(compiler, 4, nb_cod), err);
	free_compiler(compiler, 4, nb_cod);
	return (0);
}
