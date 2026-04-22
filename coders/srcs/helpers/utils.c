/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:18:51 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/22 12:37:40 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void		decide_first_dongle(struct s_dongle **dongles,
				struct s_coder *coder);
u_int64_t	get_time(void);
int			check_if_stopped(struct s_monitor monitor);
void		print_success_msg(struct s_compiler *compiler);
uint64_t	get_prog_time(struct s_monitor *monitor);

void	decide_first_dongle(struct s_dongle **dongles, struct s_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->l_dongle < coder->r_dongle)
	{
		first = coder->l_dongle;
		second = coder->r_dongle;
	}
	else
	{
		first = coder->r_dongle;
		second = coder->l_dongle;
	}
	dongles[0] = first;
	dongles[1] = second;
}

int	check_if_stopped(struct s_monitor monitor)
{
	pthread_mutex_lock(&monitor.mutex);
	if (monitor.stop)
	{
		pthread_mutex_unlock(&monitor.mutex);
		return (1);
	}
	pthread_mutex_unlock(&monitor.mutex);
	return (0);
}

inline
__attribute__((always_inline))
uint64_t	get_time(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

uint64_t	get_prog_time(struct s_monitor *monitor)
{
	return (get_time() - monitor->prog_start);
}

void	print_success_msg(struct s_compiler *compiler)
{
	pthread_mutex_lock(&compiler->monitor.mutex);
	printf("%" PRId64 " all coders compiled successfully\n",
		get_prog_time(&compiler->monitor));
	pthread_mutex_unlock(&compiler->monitor.mutex);
}
