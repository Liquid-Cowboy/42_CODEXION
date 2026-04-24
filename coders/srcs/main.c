/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:30:35 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/24 19:29:02 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	print_compiler(struct s_hub_stats compiler);
void	print_help(void);
void	print_top(void);
void	print_bottom(void);

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

void	print_help(void)
{
	print_top();
	print_bottom();
}

void	print_top(void)
{
	printf(
		BLUE"╔═════════════════════════════════════════════════════╗\n"\
"║                      "GREEN"CODEXION"BLUE"                       ║\n"\
"║                   === how to ===                    ║\n"\
"║                                                     ║\n"\
"║   "CYAN"Run with the following arguments:"BLUE"                 ║\n"\
"║                                                     ║\n"\
"║       "CYAN"number of coders (digit)"BLUE"                      ║\n"\
"║           how many coders are connected             ║\n"\
"║           to the quantum compiler                   ║\n"\
"║                                                     ║\n"\
"║       "CYAN"time to burnout (digit)"BLUE"                       ║\n"\
"║           how many milliseconds until               ║\n"\
"║           a coder burns out                         ║\n"\
"║           (since last compilation start)            ║\n"\
"║                                                     ║\n"\
"║       "CYAN"time to compile (digit)"BLUE"                       ║\n"\
"║           how many milliseconds until               ║\n"\
"║           a coder compiles                          ║\n"\
"║                                                     ║\n"\
"║       "CYAN"time to debbug (digit)"BLUE"                        ║\n"\
"║           how many milliseconds until               ║\n"\
"║           a coder debbugs                           ║\n"\
"║                                                     ║\n"\
);
}

void	print_bottom(void)
{
	printf(
		"║       "CYAN"time to refactor (digit)"BLUE"                      ║\n"\
"║           how many milliseconds until               ║\n"\
"║           a coder refactors                         ║\n"\
"║                                                     ║\n"\
"║       "CYAN"numbers of compiles required (digit)"BLUE"          ║\n"\
"║           how many times a coder has to compile     ║\n"\
"║           to exit simulation                        ║\n"\
"║                                                     ║\n"\
"║       "CYAN"dongle cooldown (digit)"BLUE"                       ║\n"\
"║           how many milliseconds until a dongle      ║\n"\
"║           is available again after being used       ║\n"\
"║                                                     ║\n"\
"║       "CYAN"scheduler (\"fifo\" or \"edf\")"BLUE"                   ║\n"\
"║           set priority to \"First In First Out\"      ║\n"\
"║           or \"Earliest Deadline First\"              ║\n"\
"║                                                     ║\n"\
"╚═════════════════════════════════════════════════════╝\n"
		);
}

int	main(int argc, char **argv)
{
	t_compiler	*compiler;
	int			nb_cod;
	int			err;

	if (argc == 2 && strcmp(argv[1], "--help") == 0)
		return (print_help(), 0);
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
