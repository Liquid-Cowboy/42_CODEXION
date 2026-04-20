/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnogueir <mnogueir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:11:28 by mnogueir          #+#    #+#             */
/*   Updated: 2026/04/20 18:39:41 by mnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _DEFAULT_SOURCE
#ifndef CODEXION_H
# define CODEXION_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> // gettimeofday
# include <unistd.h> // write && usleep
# include <pthread.h>
# include <inttypes.h>
# include <stdint.h>
# include "structs.h"

void	print_compiler(struct s_hub_stats compiler);
// parser.c
void				call_err_parser(int arg_nb, int error_type);
int					check_valid_nb(int nb, char *arg, int arg_nb);
int					parser(struct s_compiler *compiler,
						int argc, char **argv);
struct s_hub_stats	hub_config(int *args, char *sch);

//memory_handling.c
int					compiler_init(struct s_compiler **compiler,
						int argc, char **argv);
void				free_compiler(struct s_compiler *compiler,
						int stage, int heap_i);

//thread_start_1.c
int					start_threads(struct s_compiler *compiler);
int					init_dongle_mutexes(struct s_compiler *compiler, int nb_cod);
int					init_dongle_cond(struct s_compiler *compiler, int nb_cod);
int					init_coder_mutexes(struct s_compiler *compiler, int nb_cod);

//thread_start_2.c
int					create_monitor_thread(struct s_compiler *compiler);
int					create_coder_threads(struct s_compiler *compiler, int nb_cod);

//thread_cleanup.c
void				destroy_dongle_mutexes(struct s_compiler *compiler, int nb_cod);
void				destroy_dongle_cond(struct s_compiler *compiler, int nb_cod);
void				destroy_coder_mutexes(struct s_compiler *compiler, int nb_cod);
int					join_threads(struct s_compiler *compiler, int nb_cod);

//init.c
void				init_all(struct s_compiler *compiler);
void				init_coders(struct s_compiler *compiler);
void				init_dongles(struct s_compiler *compiler);

// routines.coder_routine.c
void	*coder_routine(void *arg);
int		start_routine(struct s_coder *coder);
int		make_coder_work(struct s_coder *coder);
void	do_coder_action(struct s_coder *coder, const char* action, struct s_monitor *monitor);
int		can_start(struct s_coder *coder);

// routines.monitor_routine.c
void	*monitor_routine(void *arg);
int		detect_burnout(struct s_coder *coder,
			struct s_monitor *monitor);
int		check_if_compiled(struct s_coder *coder, int i, int *ar);
void	run_monitor_loop(struct s_compiler *compiler, int nb_cod);

// routines/dongle_management.c
int					grab_both_dongles(struct s_coder *coder);
int					grab_single_dongle(struct s_coder *coder, struct s_dongle *dongle, int cooldown);
void	leave_both_dongles(struct s_coder *coder);
int		request_dongle(struct s_coder *coder, struct s_dongle *dongle, int cooldown);

// enqueue.c
int				enqueue_fifo(struct s_coder *coder, int locked);
int				is_first_fifo(struct s_coder *coder, struct s_dongle *dongle);
int				enqueue_edf(struct s_coder *coder, int locked);
int				is_first_edf(struct s_coder *coder, struct s_dongle *dongle, int burn);
void				coder_swap(struct s_dongle *dongle);

// utils.c
void		decide_first_dongle(struct s_dongle **dongles, struct s_coder *coder);
u_int64_t	get_time(void);
int			check_if_stopped(struct s_monitor monitor);
void		print_success_msg(struct s_compiler *compiler);
uint64_t	get_prog_time(struct s_monitor *monitor);


//error macros
# define ERR_NB_COD "Codexion cannot run with < 2 coders." \
		"If number_of_coders is 1, coder 1 will inevitably burnout."
# define ERR_NEG_INT  "Value is a negative integer."
# define ERR_NOT_INT "Argument is not a valid integer."
# define ERR_COMP_REQ  "Coders must compile at least 1 time."
# define ERR_INT_OVERFLOW "Value exceeds INT_MAX." 

#endif