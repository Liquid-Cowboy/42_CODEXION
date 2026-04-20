/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:01:57 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:15 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

int	create_monitor_thread(struct s_compiler *compiler);
int	create_coder_threads(struct s_compiler *compiler, int nb_cod);

int	create_monitor_thread(struct s_compiler *compiler)
{
	if (pthread_mutex_init(&compiler->monitor.mutex, NULL) != 0)
	{
		fprintf(stderr, "Error: Unable to initiate monitor mutex.\n");
		return (1);
	}
	if (pthread_create(&compiler->monitor.thread,
			NULL, &monitor_routine, compiler) != 0)
	{
		fprintf(stderr, "Error: Unable to create monitor thread.\n");
		return (pthread_mutex_destroy(&compiler->monitor.mutex), 1);
	}
	return (0);
}

int	create_coder_threads(struct s_compiler *compiler, int nb_cod)
{
	int	i;

	i = -1;
	while (++i < nb_cod)
	{
		if (pthread_create(&compiler->coders[i].thread,
				NULL, &coder_routine, &compiler->coders[i]) != 0)
		{
			fprintf(stderr, "Error: Unable to create "
				"coder %d thread.\n", i + 1);
			return (join_threads(compiler, i), 1);
		}
	}
	return (0);
}
