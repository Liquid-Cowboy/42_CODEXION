/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:12:17 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 11:00:16 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

int	start_threads(struct s_compiler *compiler);
int	init_dongle_mutexes(struct s_compiler *compiler, int nb_cod);
int	init_dongle_cond(struct s_compiler *compiler, int nb_cod);
int	init_coder_mutexes(struct s_compiler *compiler, int nb_cod);

int	start_threads(struct s_compiler *compiler)
{
	int	nb_cod;

	nb_cod = compiler->hub.number_of_coders;
	if (init_dongle_mutexes(compiler, nb_cod) != 0)
		return (1);
	if (init_dongle_cond(compiler, nb_cod) != 0)
		return (destroy_dongle_mutexes(compiler, nb_cod), 1);
	if (init_coder_mutexes(compiler, nb_cod) != 0)
	{
		destroy_dongle_mutexes(compiler, nb_cod);
		return (destroy_dongle_cond(compiler, nb_cod), 1);
	}
	if (create_monitor_thread(compiler) != 0)
	{
		destroy_dongle_mutexes(compiler, nb_cod);
		destroy_dongle_cond(compiler, nb_cod);
		return (destroy_coder_mutexes(compiler, nb_cod), 1);
	}
	if (create_coder_threads(compiler, nb_cod) != 0)
	{
		destroy_dongle_mutexes(compiler, nb_cod);
		destroy_dongle_cond(compiler, nb_cod);
		return (destroy_coder_mutexes(compiler, nb_cod), 1);
	}
	return (0);
}

int	init_dongle_mutexes(struct s_compiler *compiler, int nb_cod)
{
	int	i;

	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_mutex_init(&compiler->dongles[i].mutex, NULL) != 0)
		{
			fprintf(stderr, "Error: Unable to initiate "
				"dongle %d mutex.\n", i + 1);
			while (i-- > 0)
			{
				if (pthread_mutex_destroy(&compiler->dongles[i].mutex) != 0)
					fprintf(stderr, "Error: Unable to destroy "
						"dongle %d mutex.\n", i + 1);
				if (i == 0)
					return (1);
			}
		}
	}
	return (0);
}

int	init_dongle_cond(struct s_compiler *compiler, int nb_cod)
{
	int	i;

	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_cond_init(&compiler->dongles[i].cond, NULL) != 0)
		{
			fprintf(stderr, "Error: Unable to initiate "
				"dongle %d condition.\n", i + 1);
			while (i-- > 0)
			{
				if (pthread_cond_destroy(&compiler->dongles[i].cond) != 0)
					fprintf(stderr, "Error: Unable to destroy "
						"dongle %d condition.\n", i + 1);
				if (i == 0)
					return (1);
			}
		}
	}
	return (0);
}

int	init_coder_mutexes(struct s_compiler *compiler, int nb_cod)
{
	int	i;

	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_mutex_init(&compiler->coders[i].mutex, NULL) != 0)
		{
			fprintf(stderr, "Error: Unable to initiate "
				"coder %d mutex.\n", i + 1);
			while (i-- > 0)
			{
				if (pthread_mutex_destroy(&compiler->coders[i].mutex) != 0)
					fprintf(stderr, "Error: Unable to destroy "
						"coder %d mutex.\n", i + 1);
				if (i == 0)
					return (1);
			}
		}
	}
	return (0);
}
