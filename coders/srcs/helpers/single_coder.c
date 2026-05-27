/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_coder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:28:45 by mnogueir          #+#    #+#             */
/*   Updated: 2026/05/27 11:43:52 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	handle_single_coder(struct s_hub_stats hub, struct s_monitor *monitor)
{
	usleep(hub.time_to_burnout * 1000);
	printf("%" PRId64 " %d burned out\n", get_prog_time(monitor), 1);
}
