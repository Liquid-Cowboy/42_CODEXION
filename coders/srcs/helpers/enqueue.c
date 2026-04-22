/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:31:15 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/22 10:56:01 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

int	enqueue_fifo(struct s_coder *coder);
int		is_first_fifo(struct s_coder *coder, struct s_dongle *dongle);
int	enqueue_edf(struct s_coder *coder);
int		is_first_edf(struct s_coder *coder, struct s_dongle *dongle, int burn);

int	enqueue_fifo(struct s_coder *coder)
{
	t_dongle	*dongles[2];

	decide_first_dongle(dongles, coder);
	if (is_first_fifo(coder, dongles[0]) != 0)
		return (1);
	if (is_first_fifo(coder, dongles[1]) != 0)
		return (1);
	return (0);
}

int	is_first_fifo(struct s_coder *coder, struct s_dongle *dongle)
{
	t_coder	*enemy;
	uint64_t c_deadline;
	uint64_t e_deadline;

	if (coder == dongle->heap[0])
		enemy = dongle->heap[1];
	else
		enemy = dongle->heap[0];
	pthread_mutex_lock(&coder->mutex);
	c_deadline = coder->ref_end;
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_lock(&enemy->mutex);
	e_deadline = enemy->ref_end;
	pthread_mutex_unlock(&enemy->mutex);
	if (c_deadline <= e_deadline)
		return (0);
	return (1);
}

int	enqueue_edf(struct s_coder *coder)
{
	t_dongle	*dongles[2];
	int			burn;

	burn = coder->compiler->hub.time_to_burnout;
	decide_first_dongle(dongles, coder);
	if (is_first_edf(coder, dongles[0], burn) != 0)
		return (1);
	if (is_first_edf(coder, dongles[1], burn) != 0)
		return (1);
	return (0);
}

int		is_first_edf(struct s_coder *coder, struct s_dongle *dongle, int burn)
{
	t_coder *enemy;
	uint64_t  c_deadline;
	uint64_t  e_deadline;

	if (coder == dongle->heap[0])
		enemy = dongle->heap[1];
	else
		enemy = dongle->heap[0];
	pthread_mutex_lock(&coder->mutex);
	c_deadline = coder->comp_st + burn;
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_lock(&enemy->mutex);
	e_deadline = enemy->comp_st + burn;
	pthread_mutex_unlock(&enemy->mutex);
	if (c_deadline <= e_deadline)
	{
		//printf("Coder %d is first!\n", coder->id);
		return (0);
	}
	return (1);
}