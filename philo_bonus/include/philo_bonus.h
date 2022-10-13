/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/19 17:19:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "message.h"

/* represent time in milliseconds */
typedef unsigned int	t_ms;

/* mark s */
typedef char			*t_err;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	bool			init;
}					t_mutex;

typedef struct s_ctrl
{
	int				nu_philo;
	int				*cpids;
	int				index;
	int				max_meals;
	int				meals;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	t_ms			last_action;
	t_ms			last_meal;
	sem_t			*last_meal_sem;
	t_ms			start;
	bool			status;
	sem_t			*status_sem;
	bool			died;
	sem_t			*died_sem;
	bool			sated;
	bool			two_forks;
	sem_t			*sated_sem;
	pthread_t		watcher;
	sem_t			*print_sem;
	sem_t			*forks;
}					t_ctrl;

/* status of individual philosopher: either she is eating and cannot be declared
 * dead by the watcher, or she is not eating (sleeping, thinking) and can be
 * declared dead if too much time has elapsed since her last meal
 */
# define EATING 0
# define OTHER 1

/* ft_atoui needs to know if the string to convert is the number
 * of philosophers (PH) or the max_meals parameter (ME). In case of PH or ME,
 * ft_aoui will set error to INV_PH if the number exceeds 200. Otherwise, the
 * number is one of the time parameters and ft_atoui will set error to INV_T if
 * the number exceeds UINT_MAX */
# define N_PH		0
# define N_MEALS	1
# define TIME		2

/* define the maximum number op philosopers */
# ifndef PH_MAX
#  define PH_MAX 200
# endif

/* exit statuses for philosophers */
# define THREAD_ERR_CHILD 7
# define DEATH 8
# define SATED 9

/* utils.c */
void			*ft_malloc(size_t size, t_err *error);
void			*ft_calloc(size_t size, t_err *error);
unsigned int	ft_atoi(char *s, t_err *error, short type);
int				ft_strcmp(char *s1, char *s2);

/* init.c */
t_ctrl			*init_ctrl(int argc, char **argv, t_err *error);

/* simulation.c */
void			start_simulation(t_ctrl *ctrl, t_err *error);

/* big_watcher.c */
void			big_watcher(t_ctrl *ctrl, t_err *error);

/* action.c */
void			print_action(t_ctrl *ctrl, char *action);
void			ph_eat(t_ctrl *ctrl);
void			ph_sleep(t_ctrl *ctrl);

/* set.c */
void			set_died(t_ctrl *ctrl);
void			set_status(t_ctrl *ctrl, bool status);
void			set_last_meal(t_ctrl *ctrl, t_ms time);
bool			incr_meals_check_sated(t_ctrl *ctrl);
void			set_sated(t_ctrl *ctrl);
	
/* check.c */
bool			check_died(t_ctrl *ctrl);
bool			check_status(t_ctrl *ctrl);
t_ms			time_last_meal(t_ctrl *ctrl);
bool			check_sated(t_ctrl *ctrl);
bool			check_sated(t_ctrl *ctrl);

/* time.c */
t_ms			gettime(void);
void			ph_usleep(t_ctrl *ctrl, t_ms time_action);

/* exit_program.c */
int				exit_program(t_ctrl *ctrl, t_err *error);

#endif

