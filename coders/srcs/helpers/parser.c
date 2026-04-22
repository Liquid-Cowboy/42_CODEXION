/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:35:59 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/22 10:58:57 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void						call_err_parser(int arg_nb, int error_type);
int							check_valid_nb(int nb, char *arg, int arg_nb);
int							parser(struct s_compiler *compiler,
								int argc, char **argv);
struct s_hub_stats			hub_config(int *args, char *sch);

int	parser(struct s_compiler *compiler, int argc, char **argv)
{
	int					args[7];
	int					i;

	if (argc != 9)
		return (fprintf(stderr, "Error: Invalid number of arguments"
				" (expected 8).\n"), 1);
	i = 0;
	while (++i < 8)
	{
		args[i - 1] = atoi((const char *)argv[i]);
		if (check_valid_nb(args[i - 1], argv[i], i) != 0)
			return (1);
	}
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (fprintf(stderr, "Error: Invalid argument 8 (scheduler). "
				"Only \"fifo\" or \"edf\" are valid schedulers.\n"), 1);
	compiler->hub = hub_config(args, argv[8]);
	return (0);
}

struct s_hub_stats	hub_config(int *args, char *sch)
{
	t_hub_stats	compiler;

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

int	check_valid_nb(int nb, char *arg, int arg_nb)
{
	char	*end;

	if (arg_nb == 1 && nb < 1)
		return (call_err_parser(arg_nb, 0), 1);
	while (*arg && (*arg == ' ' || (*arg >= 9 && *arg <= 13) || *arg == '+'))
		arg++;
	if (*arg == '-')
		return (call_err_parser(arg_nb, 1), 1);
	if (!(*arg >= '0' && *arg <= '9'))
		return (call_err_parser(arg_nb, 2), 1);
	if (arg_nb == 6 && nb == 0)
		return (call_err_parser(arg_nb, 3), 1);
	end = arg;
	while (*end)
		end++;
	while (!(*end >= '0' && *end <= '9'))
		end--;
	end++;
	while (--end >= arg)
	{
		if (nb % 10 != *end - '0')
			return (call_err_parser(arg_nb, 4), 1);
		nb /= 10;
	}
	return (0);
}

void	call_err_parser(int arg_nb, int error_type)
{
	const char	*a_names[7];
	const char	*e_types[5];
	const char	*e_str[1];

	a_names[0] = "number_of_coders";
	a_names[1] = "time_to_burnout";
	a_names[2] = "time_to_compile";
	a_names[3] = "time_to_debug";
	a_names[4] = "time_to_refactor";
	a_names[5] = "number_of_compiles_required";
	a_names[6] = "dongle_cooldown";
	e_types[0] = ERR_NB_COD;
	e_types[1] = ERR_NEG_INT;
	e_types[2] = ERR_NOT_INT;
	e_types[3] = ERR_COMP_REQ;
	e_types[4] = ERR_INT_OVERFLOW;
	e_str[0] = "Error: Invalid argument";
	fprintf(stderr, "%s %d (%s): %s\n", e_str[0], arg_nb, a_names[arg_nb - 1],
		e_types[error_type]);
}
