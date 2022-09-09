/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/09 15:09:39 by hoomen           ###   ########.fr       */
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
}					t_fork;

/* the controller struct is used by the main thread (controller/watcher).
 * In here we store the parameters provided by the user:
 * 	nu_philo	>	the number of philosophers
 * 	max_meals	>	the number of times each philosopher must eat
 * 	time_eat	>	the time a philosopher needs to finish her meal
 * 	time_sleep	>	the time a philosopher spends sleeping
 * 	time_die	>	the maximum length of time a philosopher can spend without
 * 					eating before she dies
 * 	start		>	the start time of the simulation
 * 	run			>	controller sets this flag to true when the simulation starts
 * 	death		>	controller sets this flag to true when death occurred at
 * 					the table
 * 	watcher_go	>	is 0 at the start, each philosopher adds +1 to this parameter
 * 					and after watcher_go == nu_philo, watcher can start overseeing
 * 					the simulation
 * 	*threads	>	pointer to array of threads (every thread is a philosopher)
 * 	*forks		>	pointer to array of t_forks (every fork is a t_fork)
 * 	*philos		>	pointer to array of t_philo struct, each of them representing
 * 					one philosopher
 */
typedef struct s_ctrl
{
	int				nu_philo;
	int				max_meals;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	t_ms			start;
	bool			death;
	bool			run;
	pthread_t		*threads;
	struct s_fork	*forks;
	struct s_fork	print_lock;
	struct s_philo	*philos;
}					t_ctrl;

/* each t_philo struct represents a philosopher: they are the parameter that
 * each philosopher takes to here routine.
 * nbr			>	the number (index) of the philosopher
 * *one			>	pointer to the fork she takes first
 * *two			>	pointer to the fork she takes second
 * last_action	>	the time her last action started
 * last_meal	>	the time her last meal started
 * meals		>	the number of times she has eaten
 * sated		>	flag she sets to true when she has eaten max_meals times
 * free			>	flag she sets to true when she is not busy sleeping or
 * 					eating. (while she is sleeping or eating, she cannot die)
 * controller	>	pointer to the controller struct. She needs to acces her
 * 					time_eat and time_sleep paramters from there, plus this
 * 					pointer is needed in case something goes wrong and the whole
 * 					program needs to be freed in order to exit cleanly
 */
typedef struct s_philo
{
	int				nbr;
	t_fork			*left;
	t_fork			*right;
	t_ms			last_action;
	t_ms			last_meal;
	int				meals;
	bool			sated;
	bool			free;
	t_ctrl			*controller;
}					t_philo;

/* ft_atoui needs to know if the string to convert is the number
 * of philosophers (PH) or the max_meals parameter (ME). In case of PH or ME,
 * ft_aoui will set error to INV_PH if the number exceeds 200. Otherwise, the
 * number is one of the time parameters and ft_atoui will set error to INV_T if
 * the number exceeds UINT_MAX */
# define PH 0
# define ME 1
# define TI	2

/* define the maximum number op philosopers */
# ifndef PH_MAX
#  define PH_MAX 200
# endif

/* utils.c */
void			*ft_malloc(size_t size, t_err *error);
unsigned int	ft_atoui(char *s, t_err *error, short type);
int				ft_strcmp(char *s1, char *s2);

/* init_controller.c */
t_ctrl			*init_controller(int argc, char **argv, t_err *error);

/* fork.c */
void			init_forks(t_ctrl *ctrl, t_err *error);
void			get_forks(t_philo *philo);
void			leave_forks(t_philo *philo);

/* philo.c */
void			init_philos(t_ctrl *ctrl, t_err *error);

/* threads.c */
void			init_threads(t_ctrl *ctrl, t_err *error);

/* watcher.c */
void			watcher(t_ctrl *controller);

/* actions.c */
void			print_action(t_philo *philo, char *action, t_ms time);
void			take_forks(t_philo *philo);
void			eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			think(t_philo *philo);

/* time.c */
t_ms			gettime(void);
void			ph_usleep(t_philo *philo, t_ms time);

/* exit_program.c */
int				exit_program(t_ctrl *controller, t_err *error);

#endif

