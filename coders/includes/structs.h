/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:01:35 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/22 12:53:49 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <time.h>
#include <stdint.h>

typedef struct s_hub_stats	t_hub_stats;
typedef struct s_compiler	t_compiler;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_monitor	t_monitor;

struct s_hub_stats
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
};

struct s_coder
{
	t_compiler		*compiler;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_dongle		*l_dongle;
	t_dongle		*r_dongle;
	int				id;
	uint64_t		comp_st;
	uint64_t		ref_end;
	int				compiles_left;

};

struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_coder			**heap;
	int				in_use;
	uint64_t		last_used;
};

struct s_monitor
{
	pthread_mutex_t	mutex;
	pthread_t		thread;
	uint64_t		prog_start;
	int				stop;
};

struct s_compiler
{
	t_coder			*coders;
	t_dongle		*dongles;
	t_hub_stats		hub;
	t_monitor		monitor;
};