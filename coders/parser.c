/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:35:59 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/10 17:23:22 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void						check_valid_nb(int nb, char *arg, int arg_nb);
struct	quantum_compiler_s	parser(int argc, char **argv);
void						call_err_parser(int arg_nb, int error_type);
struct quantum_compiler_s	build_compiler(int *args, char *sch);

struct	quantum_compiler_s	parser(int argc, char **argv)
{
	int					args[7];
	int					i;
	quantum_compiler_t	compiler;

	if (argc != 9)
	{
		fprintf(stderr, "Error: Invalid number of arguments (expected 8).\n");
		exit(1);
	}
	i = 0;
	while (++i < 8)
	{
		args[i - 1] = atoi((const char *)argv[i]);
		check_valid_nb(args[i - 1], argv[i], i);
	}
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
	{
		fprintf(stderr, "Error: Invalid argument 8 (scheduler). "
			"Only \"fifo\" or \"edf\" are valid schedulers.\n");
		exit(8);
	}
	compiler = build_compiler(args, argv[8]);
	return (compiler);
}

struct quantum_compiler_s	build_compiler(int *args, char *sch)
{
	quantum_compiler_t	compiler;

	compiler.number_of_coders = args[0];
	compiler.time_to_burnout = args[1];
	compiler.time_to_compile = args[2];
	compiler.time_to_debug = args[3];
	compiler.time_to_refactor = args[4];
	compiler.number_of_compiles_required = args[5];
	compiler.dongle_cooldown = args[6];
	compiler.scheduler = sch;
	return (compiler);
}

void	check_valid_nb(int nb, char *arg, int arg_nb)
{
	char	*end;

	if (arg_nb == 1 && nb < 2)
		call_err_parser(arg_nb, 0);
	while (*arg && (*arg == ' ' || (*arg >= 9 && *arg <= 13) || *arg == '+'))
		arg++;
	if (*arg == '-')
		call_err_parser(arg_nb, 1);
	if (!(*arg >= '0' && *arg <= '9'))
		call_err_parser(arg_nb, 2);
	if (arg_nb == 6 && nb == 0)
		call_err_parser(arg_nb, 3);
	end = arg;
	while (*end)
		end++;
	while (!(*end >= '0' && *end <= '9'))
		end--;
	end++;
	while (--end >= arg)
	{
		if (nb % 10 != *end - '0')
			call_err_parser(arg_nb, 4);
		nb /= 10;
	}
}

void	call_err_parser(int arg_nb, int error_type)
{
	char	*a_names[7];
	char	*e_types[5];
	char	*e_str[1];

	a_names[0] = "number_of_coders";
	a_names[1] = "time_to_burnout";
	a_names[2] = "time_to_compile";
	a_names[3] = "time_to_debug";
	a_names[4] = "time_to_refactor";
	a_names[5] = "number_of_compiles_required";
	a_names[6] = "dongle_cooldown";
	e_types[0] = "Number of coders cannot be < 2.";
	e_types[1] = "Value is a negative integer.";
	e_types[2] = "Argument is not a valid integer.";
	e_types[3] = "Coders must compile at least 1 time.";
	e_types[4] = "Value exceeds INT_MAX.";
	e_str[0] = "Error: Invalid argument";
	fprintf(stderr, "%s %d (%s): %s\n", e_str[0], arg_nb, a_names[arg_nb - 1],
		e_types[error_type]);
	exit(arg_nb + 1);
}
