/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:32:00 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 12:18:35 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	*coder_routine(void *arg);
int		start_routine(struct s_coder *coder);
int		make_coder_work(struct s_coder *coder);
void	do_coder_action(struct s_coder *coder,
			const char *action, uint64_t time);
int		can_start(struct s_coder *coder);

void	*coder_routine(void *arg)
{
	t_coder		*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->mutex);
	coder->comp_st = get_time();
	coder->ref_end = get_time();
	pthread_mutex_unlock(&coder->mutex);
	while (1)
	{
		if (can_start(coder) != 0)
			break ;
		if (start_routine(coder) != 0)
			break ;
		pthread_mutex_lock(&coder->mutex);
		coder->compiles_left--;
		pthread_mutex_unlock(&coder->mutex);
	}
	printf("Coder %d exiting\n", coder->id);
	return (NULL);
}

int	can_start(struct s_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	pthread_mutex_lock(&coder->compiler->monitor.mutex);
	if (coder->compiles_left <= 0 || coder->burnt_out
		|| coder->compiler->monitor.stop)
	{
		pthread_mutex_unlock(&coder->mutex);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_unlock(&coder->compiler->monitor.mutex);
	return (0);
}

int	start_routine(struct s_coder *coder)
{
	if (strcmp(coder->compiler->hub.scheduler, "fifo"))
		enqueue_fifo(coder, 0);
	else
		enqueue_edf(coder, 0);
	if (!(coder == coder->l_dongle->heap[0]
			&& coder == coder->r_dongle->heap[0]))
		return (1);
	if (grab_both_dongles(coder) != 0)
		return (1);
	if (make_coder_work(coder) != 0)
		return (1);
	return (0);
}

int	make_coder_work(struct s_coder *coder)
{
	uint64_t	time;

	time = get_time();
	if (can_start(coder) != 0)
		return (1);
	do_coder_action(coder, "compile", time);
	if (can_start(coder) != 0)
		return (1);
	do_coder_action(coder, "debbug", time);
	if (can_start(coder) != 0)
		return (1);
	do_coder_action(coder, "refactor", time);
	time = get_time();
	pthread_mutex_lock(&coder->mutex);
	coder->ref_end = time;
	pthread_mutex_unlock(&coder->mutex);
	return (0);
}

void	do_coder_action(struct s_coder *coder,
	const char *action, uint64_t time)
{
	if (strcmp(action, "compile") == 0)
	{
		pthread_mutex_lock(&coder->compiler->monitor.mutex);
		printf("%" PRId64 "%d is compiling\n", time, coder->id);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		pthread_mutex_lock(&coder->mutex);
		coder->comp_st = time;
		pthread_mutex_unlock(&coder->mutex);
		usleep(coder->compiler->hub.time_to_compile * 1000);
		leave_both_dongles(coder);
	}
	else if (strcmp(action, "debbug") == 0)
	{
		pthread_mutex_lock(&coder->compiler->monitor.mutex);
		printf("%" PRId64 " %d is debugging\n", get_time(), coder->id);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		usleep(coder->compiler->hub.time_to_debug * 1000);
	}
	else if (strcmp(action, "refactor") == 0)
	{
		pthread_mutex_lock(&coder->compiler->monitor.mutex);
		printf("%" PRId64 " %d is refactoring\n", get_time(), coder->id);
		pthread_mutex_unlock(&coder->compiler->monitor.mutex);
		usleep(coder->compiler->hub.time_to_refactor * 1000);
	}
}
