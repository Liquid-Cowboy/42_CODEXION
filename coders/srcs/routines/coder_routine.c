/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:32:00 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 19:45:31 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	*coder_routine(void *arg);
int		start_routine(struct s_coder *coder);
int		make_coder_work(struct s_coder *coder);
void	do_coder_action(struct s_coder *coder,
			const char *action, struct s_monitor *monitor);
int		can_start(struct s_coder *coder);

void	*coder_routine(void *arg)
{
	t_coder		*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->mutex);
	coder->comp_st = get_time();
	coder->ref_end = get_time();
	pthread_mutex_unlock(&coder->mutex);
	while (can_start(coder) != 0)
	{
		if (start_routine(coder) != 0)
			continue ;
		pthread_mutex_lock(&coder->mutex);
		coder->compiles_left--;
		pthread_mutex_unlock(&coder->mutex);
	}
	pthread_mutex_lock(&coder->compiler->monitor.mutex);
	printf("Coder %d exiting\n", coder->id);
	pthread_mutex_unlock(&coder->compiler->monitor.mutex);
	return (NULL);
}

int	can_start(struct s_coder *coder)
{
	int	compiled;
	int	burned_out;
	int	stop;

	compiled = 0;
	burned_out = 0;
	stop = 0;
	pthread_mutex_lock(&coder->mutex);
	if (coder->compiles_left <= 0)
		compiled = 1;
	if (coder->burned_out)
		burned_out = 1;
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_lock(&coder->compiler->monitor.mutex);
	if (coder->compiler->monitor.stop)
		stop = 1;
	pthread_mutex_unlock(&coder->compiler->monitor.mutex);
	if (compiled || burned_out || stop)
		return (1);
	return (0);
}

int	start_routine(struct s_coder *coder)
{
	if (strcmp(coder->compiler->hub.scheduler, "fifo") == 0)
	{
		if (enqueue_fifo(coder) != 0)
			return (1);
	}
	else
	{
		if (enqueue_edf(coder) != 0)
			return (1);
	}
	if (grab_both_dongles(coder) != 0)
		return (1);
	if (make_coder_work(coder) != 0)
		return (1);
	return (0);
}

int	make_coder_work(struct s_coder *coder)
{
	if (can_start(coder) != 0)
		return (1);
	do_coder_action(coder, "compile", &coder->compiler->monitor);
	if (can_start(coder) != 0)
		return (1);
	do_coder_action(coder, "debbug", &coder->compiler->monitor);
	if (can_start(coder) != 0)
		return (1);
	do_coder_action(coder, "refactor", &coder->compiler->monitor);
	pthread_mutex_lock(&coder->mutex);
	coder->ref_end = get_time();
	pthread_mutex_unlock(&coder->mutex);
	return (0);
}

void	do_coder_action(struct s_coder *coder,
	const char *action, struct s_monitor *monitor)
{
	pthread_mutex_lock(&coder->compiler->monitor.mutex);
	if (strcmp(action, "compile") == 0)
	{
		printf("%" PRId64 "%d is compiling\n",
			get_prog_time(monitor), coder->id);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		pthread_mutex_lock(&coder->mutex);
		coder->comp_st = get_time();
		pthread_mutex_unlock(&coder->mutex);
		usleep(coder->compiler->hub.time_to_compile * 1000);
		leave_both_dongles(coder, 1);
	}
	else if (strcmp(action, "debbug") == 0)
	{
		printf("%" PRId64 " %d is debugging\n",
			get_prog_time(&coder->compiler->monitor), coder->id);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		usleep(coder->compiler->hub.time_to_debug * 1000);
	}
	else
	{
		printf("%" PRId64 " %d is refactoring\n",
			get_prog_time(monitor), coder->id);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		usleep(coder->compiler->hub.time_to_refactor * 1000);
	}
}
