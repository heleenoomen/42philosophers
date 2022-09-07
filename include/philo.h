/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 12:41:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include "message.h"

/* represent time in milliseconds */
typedef unsigned int	t_ms;
/* mark s */
typedef char			*t_err;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			init;
	bool			locked;
	t_ms			queue;
}					t_fork;

typedef struct s_ctrl
{
	int				nu_philo;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	int				max_meals;
	t_ms			start;
	bool			death;
	bool			run;
	pthread_t		*threads;
	struct s_fork	print_lock;
	t_ms			print_queue;
	struct s_fork	*forks;
	struct s_philo	*philos;
}					t_ctrl;

typedef struct s_philo
{
	int				nbr;
	t_fork			*one;
	t_fork			*two;
	bool			has_forks;
	t_ms			last_action;
	t_ms			last_meal;
	int				meals;
	t_ctrl			*controller;
	bool			died;
}					t_philo;

/* ft_atoui needs to know if the string to convert is the number
 * of philosophers (PH) or a time parameter (T). In case of PH, 
 * ft_aoui will set error to INV_PH if the number exceeds 200. In case of TI,
 * ft_atoui will set error to INV_T if the number exceeds UINT_MAX */
# define PH 0
# define TI 1
# define ME 2

/* define the maximum number op philosopers */
# define PH_MAX 200

/* utils.c */
void			*ft_malloc(size_t size, t_err *error);
unsigned int	ft_atoui(char *s, t_err *error, short type);
int				ft_strcmp(char *s1, char *s2);

/* init_controller.c */
t_ctrl			*init_controller(int argc, char **argv, t_err *error);

/* fork.c */
void			init_forks(t_ctrl *ctrl, t_err *error);
void			get_forks(t_philo *philo);
void			take_forks(t_philo *philo);
void			leave_forks(t_philo *philo);

/* philo.c */
void			init_philos(t_ctrl *ctrl);

/* threads.c */
void			init_threads(t_ctrl *ctrl, t_err *error);

/* actions.c */
void			print_action(t_philo *philo, char *action, t_ms time);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
bool			philo_die(t_philo *philo);

/* time.c */
t_ms			gettime(void);
void			philo_action(t_philo *philo, t_ms time);

/* exit_program.c */
int				exit_program(t_ctrl *controller, t_err *error);

#endif

