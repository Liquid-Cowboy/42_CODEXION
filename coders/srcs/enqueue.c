/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:31:15 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 17:12:39 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	enqueue_fifo(struct s_coder *coder, int locked);
int		is_first_fifo(struct s_coder *coder, struct s_dongle *dongle);
int	enqueue_edf(struct s_coder *coder, int locked);
int		is_first_edf(struct s_coder *coder, struct s_dongle *dongle, int burn);

int	enqueue_fifo(struct s_coder *coder, int locked)
{
	t_dongle	*dongles[2];

	decide_first_dongle(dongles, coder);
	if (!locked)
	{
		pthread_mutex_lock(&dongles[0]->mutex);
		if (is_first_fifo(coder, dongles[0]) != 0)
			return (pthread_mutex_unlock(&dongles[0]->mutex), 1);
		pthread_mutex_unlock(&dongles[0]->mutex);
		pthread_mutex_lock(&dongles[1]->mutex);
		if (is_first_fifo(coder, dongles[1]) != 0)
			return (pthread_mutex_unlock(&dongles[1]->mutex), 1);
		return (pthread_mutex_unlock(&dongles[1]->mutex), 0);
	}
	else
	{
		if ((is_first_fifo(coder, dongles[0]) == 0
		&& is_first_fifo(coder, dongles[1]) == 0))
			return (0);
		return (1);
	}
}

int	is_first_fifo(struct s_coder *coder, struct s_dongle *dongle)
{
	if (coder == dongle->heap[0] && coder->ref_end < dongle->heap[1]->ref_end)
		return(0);
	if (coder == dongle->heap[1] && coder->ref_end < dongle->heap[0]->ref_end)
		return(0);
	return (1);
}

int	enqueue_edf(struct s_coder *coder, int locked)
{
	t_dongle	*dongles[2];
	int			burn;

	burn = coder->compiler->hub.time_to_burnout;
	decide_first_dongle(dongles, coder);
	if (!locked)
	{
		pthread_mutex_lock(&dongles[0]->mutex);
		if (is_first_edf(coder, dongles[0], burn) != 0)
			return (pthread_mutex_unlock(&dongles[0]->mutex), 1);
		pthread_mutex_unlock(&dongles[0]->mutex);
		pthread_mutex_lock(&dongles[1]->mutex);
		if (is_first_edf(coder, dongles[1], burn) != 0)
			return(pthread_mutex_unlock(&dongles[1]->mutex), 1);
		return (pthread_mutex_unlock(&dongles[1]->mutex), 0);
	}
	else
	{
		if (is_first_edf(coder, dongles[0], burn) == 0
		&& is_first_edf(coder, dongles[1], burn) == 0)
			return (0);
		return (1);
	}
}

int		is_first_edf(struct s_coder *coder, struct s_dongle *dongle, int burn)
{
	pthread_mutex_lock(&dongle->mutex);
	if (coder == dongle->heap[0]
		&& coder->comp_st + burn < dongle->heap[1]->comp_st + burn)
		return (pthread_mutex_unlock(&dongle->mutex), 0);
	if (coder == dongle->heap[1]
		&& coder->comp_st + burn < dongle->heap[0]->comp_st + burn)
		return (pthread_mutex_unlock(&dongle->mutex), 0);
	return (pthread_mutex_unlock(&dongle->mutex), 1);
}