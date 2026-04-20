/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:31:15 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 18:49:50 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	enqueue_fifo(struct s_coder *coder);
int		is_first_fifo(struct s_coder *coder, struct s_dongle *dongle);
int	enqueue_edf(struct s_coder *coder);
int		is_first_edf(struct s_coder *coder, struct s_dongle *dongle, int burn);

int	enqueue_fifo(struct s_coder *coder)
{
	t_dongle	*dongles[2];

	decide_first_dongle(dongles, coder);
	pthread_mutex_lock(&dongles[0]->mutex);
	if (is_first_fifo(coder, dongles[0]) != 0)
		return (pthread_mutex_unlock(&dongles[0]->mutex), 1);
	pthread_mutex_unlock(&dongles[0]->mutex);
	pthread_mutex_lock(&dongles[1]->mutex);
	if (is_first_fifo(coder, dongles[1]) != 0)
		return (pthread_mutex_unlock(&dongles[1]->mutex), 1);
	return (pthread_mutex_unlock(&dongles[1]->mutex), 0);

}

int	is_first_fifo(struct s_coder *coder, struct s_dongle *dongle)
{
	t_coder	*enemy;

	if (coder == dongle->heap[0])
		enemy = dongle->heap[1];
	else
		enemy = dongle->heap[0];
	if (coder->ref_end < enemy->ref_end)
		return (0);
	return (1);
}

int	enqueue_edf(struct s_coder *coder)
{
	t_dongle	*dongles[2];
	int			burn;

	burn = coder->compiler->hub.time_to_burnout;
	decide_first_dongle(dongles, coder);
	pthread_mutex_lock(&dongles[0]->mutex);
	if (is_first_edf(coder, dongles[0], burn) != 0)
		return (pthread_mutex_unlock(&dongles[0]->mutex), 1);
	pthread_mutex_unlock(&dongles[0]->mutex);
	pthread_mutex_lock(&dongles[1]->mutex);
	if (is_first_edf(coder, dongles[1], burn) != 0)
		return(pthread_mutex_unlock(&dongles[1]->mutex), 1);
	return (pthread_mutex_unlock(&dongles[1]->mutex), 0);
}

int		is_first_edf(struct s_coder *coder, struct s_dongle *dongle, int burn)
{
	t_coder *enemy;

	if (coder == dongle->heap[0])
		enemy = dongle->heap[1];
	else
		enemy = dongle->heap[0];
	if (coder->comp_st + burn < enemy->comp_st + burn)
		return (0);
	return (1);
}