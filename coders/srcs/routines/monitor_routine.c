/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:32:00 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 12:13:02 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	*monitor_routine(void *arg);
int		detect_burnout(struct s_coder *coder,
			struct s_monitor *monitor, int i);
int		check_if_compiled(struct s_coder *coder, int i, int *ar);
void	run_monitor_loop(struct s_compiler *compiler, int nb_cod);

void	*monitor_routine(void *arg)
{
	t_compiler	*compiler;

	compiler = (t_compiler *)arg;
	run_monitor_loop(compiler, compiler->hub.number_of_coders);
	return (NULL);
}

void	run_monitor_loop(struct s_compiler *compiler, int nb_cod)
{
	int	i;
	int	*ar;
	int	completed;

	i = -1;
	completed = 0;
	ar = (int *) malloc(sizeof (int) * nb_cod);
	if (!ar)
		return ;
	memset((void *)ar, 0, sizeof(int) * nb_cod);
	i = 0;
	while (1)
	{
		if (detect_burnout(&compiler->coders[i], &compiler->monitor, i) != 0)
			break ;
		if (!ar[i])
			completed += check_if_compiled(&compiler->coders[i], i, ar);
		if (completed == compiler->hub.number_of_coders)
		{
			print_success_msg(compiler);
			break ;
		}
		i = (i + 1) % nb_cod;
	}
	free(ar);
}

int	detect_burnout(struct s_coder *coder, struct s_monitor *monitor, int i)
{
	pthread_mutex_lock(&coder->mutex);
	if (coder->burnt_out)
	{
		pthread_mutex_lock(&monitor->mutex);
		printf("%" PRId64 " %d burned out\n", get_time(), i + 1);
		monitor->stop = 1;
		pthread_mutex_unlock(&monitor->mutex);
		pthread_mutex_unlock(&coder->mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->mutex);
	return (0);
}

int	check_if_compiled(struct s_coder *coder, int i, int *ar)
{
	pthread_mutex_lock(&coder->mutex);
	if (coder->compiles_left == 0)
	{
		pthread_mutex_lock(&coder->compiler->monitor.mutex);
		printf("%" PRId64 " %d has finished compiling\n", get_time(), i + 1);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		ar[i] = 1;
		return (1);
	}
	pthread_mutex_unlock(&coder->mutex);
	return (0);
}
