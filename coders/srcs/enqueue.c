/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:31:15 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 11:15:13 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	enqueue_fifo(struct s_coder *coder, int locked);
void	order_fifo(struct s_coder *coder, struct s_dongle *dongle);
void	enqueue_edf(struct s_coder *coder, int locked);
void	order_edf(struct s_coder *coder, struct s_dongle *dongle, int burn);
void	coder_swap(struct s_dongle *dongle);

void	enqueue_fifo(struct s_coder *coder, int locked)
{
	t_dongle	*dongles[2];

	decide_first_dongle(dongles, coder);
	if (!locked)
	{
		pthread_mutex_lock(&dongles[0]->mutex);
		order_fifo(coder, dongles[0]);
		pthread_mutex_unlock(&dongles[0]->mutex);
		pthread_mutex_lock(&dongles[1]->mutex);
		order_fifo(coder, dongles[1]);
		pthread_mutex_unlock(&dongles[1]->mutex);
	}
	else
	{
		order_fifo(coder, dongles[0]);
		order_fifo(coder, dongles[1]);
	}
}

void	order_fifo(struct s_coder *coder, struct s_dongle *dongle)
{
	if (coder == dongle->heap[0] && coder->ref_end > dongle->heap[1]->ref_end)
		coder_swap(dongle);
	if (coder == dongle->heap[1] && coder->ref_end < dongle->heap[0]->ref_end)
		coder_swap(dongle);
}

void	enqueue_edf(struct s_coder *coder, int locked)
{
	t_dongle	*dongles[2];
	int			burn;

	burn = coder->compiler->hub.time_to_burnout;
	decide_first_dongle(dongles, coder);
	if (!locked)
	{
		pthread_mutex_lock(&dongles[0]->mutex);
		order_edf(coder, dongles[0], burn);
		pthread_mutex_unlock(&dongles[0]->mutex);
		pthread_mutex_lock(&dongles[1]->mutex);
		order_edf(coder, dongles[1], burn);
		pthread_mutex_unlock(&dongles[1]->mutex);
	}
	else
	{
		order_edf(coder, dongles[0], burn);
		order_edf(coder, dongles[1], burn);
	}
}

void	order_edf(struct s_coder *coder, struct s_dongle *dongle, int burn)
{
	pthread_mutex_lock(&dongle->mutex);
	if (coder == dongle->heap[0]
		&& coder->comp_st + burn > dongle->heap[1]->comp_st + burn)
		coder_swap(dongle);
	if (coder == dongle->heap[1]
		&& coder->comp_st + burn < dongle->heap[0]->comp_st + burn)
		coder_swap(dongle);
	pthread_mutex_unlock(&dongle->mutex);
}

void	coder_swap(struct s_dongle *dongle)
{
	t_coder	*tmp;

	tmp = dongle->heap[0];
	dongle->heap[0] = dongle->heap[1];
	dongle->heap[1] = tmp;
}
