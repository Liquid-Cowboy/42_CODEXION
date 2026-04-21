/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:01:18 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/21 10:33:56 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	destroy_dongle_mutexes(struct s_compiler *compiler, int nb_cod);
void	destroy_dongle_cond(struct s_compiler *compiler, int nb_cod);
void	destroy_coder_mutexes(struct s_compiler *compiler, int nb_cod);
int		join_threads(struct s_compiler *compiler, int nb_cod);

void	destroy_dongle_mutexes(struct s_compiler *compiler, int nb_cod)
{
	int	i;

	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_mutex_destroy(&compiler->dongles[i].mutex) != 0)
			fprintf(stderr, "Unable to destroy dongle %d mutex.\n", i + 1);
	}
}

void	destroy_dongle_cond(struct s_compiler *compiler, int nb_cod)
{
	int	i;

	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_cond_destroy(&compiler->dongles[i].cond) != 0)
			fprintf(stderr, "Unable to destroy "
				"dongle %d condition.\n", i + 1);
	}
}

void	destroy_coder_mutexes(struct s_compiler *compiler, int nb_cod)
{
	int	i;

	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_mutex_destroy(&compiler->coders[i].mutex) != 0)
			fprintf(stderr, "Unable to destroy coder %d mutex.\n", i + 1);
	}
}

int	join_threads(struct s_compiler *compiler, int nb_cod)
{
	int	i;
	int	err;

	err = 0;
	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_join(compiler->coders[i].thread, NULL) != 0)
		{
			fprintf(stderr, "Error: Unable to join coder %d thread.\n", i + 1);
			err = 1;
		}
	}
	if (pthread_join(compiler->monitor.thread, NULL) != 0)
	{
		fprintf(stderr, "Error: Unable to join monitor thread.\n");
		err = 1;
	}
	destroy_dongle_cond(compiler, nb_cod);
	destroy_dongle_mutexes(compiler, nb_cod);
	destroy_coder_mutexes(compiler, nb_cod);
	return (err);
}
