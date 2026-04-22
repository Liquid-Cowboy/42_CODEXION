/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:30:35 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/22 10:52:53 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

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

void	handle_single_coder(struct s_compiler *compiler,
		struct s_monitor *monitor)
{
	compiler->coders[0].comp_st = 1;
	compiler->coders[0].compiles_left = 1;
	compiler->coders[0].compiler = compiler;
	compiler->coders[0].id = 1;
	init_coder_mutexes(compiler, 1);
	compiler->coders[0].comp_st = get_prog_time(monitor);
	create_monitor_thread(compiler);
	if (pthread_join(monitor->thread, NULL) != 0)
		fprintf(stderr, "Error: Unable to join monitor thread.\n");
	pthread_mutex_destroy(&monitor->mutex);
}

int	main(int argc, char **argv)
{
	t_compiler	*compiler;
	int			nb_cod;
	int			err;

	err = compiler_init(&compiler, argc, argv);
	if (err)
		return (err);
	nb_cod = compiler->hub.number_of_coders;
	if (nb_cod == 1)
		return (handle_single_coder(compiler,
			&compiler->monitor), 1);
	init_all(compiler);
	err = start_threads(compiler);
	if (err)
		return (free_compiler(compiler, 4, nb_cod), err);
	err = join_threads(compiler, nb_cod);
	if (err)
		return (free_compiler(compiler, 4, nb_cod), err);
	//print_compiler(compiler->hub);
	free_compiler(compiler, 4, nb_cod);
	return (0);
}
