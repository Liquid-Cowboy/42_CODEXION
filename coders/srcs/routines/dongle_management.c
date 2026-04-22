/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:07:31 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/22 10:26:16 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

int		grab_both_dongles(struct s_coder *coder);
int		grab_single_dongle(struct s_coder *coder,
			struct s_dongle *dongle, int cooldown);
void	leave_both_dongles(struct s_coder *coder, int used);
int		request_dongle(struct s_coder *coder,
			struct s_dongle *dongle, int cooldown);

int	grab_both_dongles(struct s_coder *coder)
{
	t_dongle	**dongles;
	int			cooldown;

	dongles = (t_dongle**)malloc(sizeof (t_dongle)*2);
	if (!dongles)
		return (1);
	cooldown = coder->compiler->hub.dongle_cooldown;
	decide_first_dongle(dongles, coder);
	if (grab_single_dongle(coder, dongles[0], cooldown) != 0)
		return (free(dongles), 1);
	if (strcmp(coder->compiler->hub.scheduler, "fifo") == 0)
	{
		if (enqueue_fifo(coder) != 0)
			return(free(dongles),
			leave_both_dongles(coder, 0), 1);
	}
	else
	{
		if (enqueue_edf(coder) != 0)
			return(free(dongles),
			leave_both_dongles(coder, 0), 1);
	}
	if (grab_single_dongle(coder, dongles[1], cooldown) != 0)
		return (free(dongles),
		leave_both_dongles(coder, 0), 1);
	return (free(dongles), 0);
}

int	grab_single_dongle(struct s_coder *coder,
	struct s_dongle *dongle, int cooldown)
{
	if (request_dongle(coder, dongle, cooldown) != 0)
		return (1);
	if (can_start(coder) != 0)
		return (1);
	pthread_mutex_lock(&dongle->mutex);
	dongle->in_use = 1;
	pthread_mutex_unlock(&dongle->mutex);
	pthread_mutex_lock(&coder->compiler->monitor.mutex);
	printf("%" PRId64 " %d has taken a dongle\n",
		get_prog_time(&coder->compiler->monitor), coder->id);
	pthread_mutex_unlock(&coder->compiler->monitor.mutex);
	return (0);
}

void	leave_both_dongles(struct s_coder *coder, int used)
{
	t_dongle	**dongles;

	dongles = (t_dongle **)malloc(sizeof (t_dongle) * 2);
	if(!dongles)
		return ;
	decide_first_dongle(dongles, coder);
	pthread_mutex_lock(&dongles[1]->mutex);
	dongles[1]->in_use = 0;
	if (used)
		dongles[1]->last_used = get_time();
	pthread_cond_broadcast(&dongles[1]->cond);
	pthread_mutex_unlock(&dongles[1]->mutex);
	pthread_mutex_lock(&dongles[0]->mutex);
	dongles[0]->in_use = 0;
	if (used)
		dongles[0]->last_used = get_time();
	pthread_cond_broadcast(&dongles[0]->cond);
	pthread_mutex_unlock(&dongles[0]->mutex);
	free(dongles);
}

int	request_dongle(struct s_coder *coder, struct s_dongle *dongle, int cooldown)
{
	struct timespec	deadline;
	uint64_t		target;

	pthread_mutex_lock(&dongle->mutex);
	pthread_mutex_lock(&coder->mutex);
	target = coder->comp_st + coder->compiler->hub.time_to_burnout;
	pthread_mutex_unlock(&coder->mutex);
	while (dongle->in_use || dongle->last_used + cooldown > get_time())
	{
		if (!dongle->in_use && target > dongle->last_used + cooldown)
			target = (dongle->last_used + cooldown);
		deadline.tv_sec = target / 1000;
		deadline.tv_nsec = (target % 1000) * 1000000;
		pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &deadline);
	}
	return (pthread_mutex_unlock(&dongle->mutex), 0);
}
