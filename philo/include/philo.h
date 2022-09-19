/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/19 16:42:09 by hoomen           ###   ########.fr       */
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

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	bool			init;
}					t_mutex;

/* the controller struct is used by the main thread (controller/watcher).
 * In here we store the parameters provided by the user:
 * 	nu_philo	>	the number of philosophers
 * 	max_meals	>	the number of times each philosopher must eat
 * 	time_eat	>	the time a philosopher needs to finish her meal
 * 	time_sleep	>	the time a philosopher spends sleeping
 * 	time_die	>	the maximum length of time a philosopher can spend without
 * 					eating before she dies
 * 	philos		>	pointer to array of t_philo struct, each of them representing
 * 					one philosopher
 * 	threads		>	pointer to array of threads (every thread is a philosopher)
 * 	forks		>	pointer to array of t_mutexs (every fork is a t_mutex)
 * 	death		>	flag that is set to true as soon as one philosopher dies
 * 	lock_death	>	mutex to protect the death flag
 * 	nu_sated	>	the number of sated philosophers (who have eaten max_meals
 * 					times)
 * 	lock_sated	>	mutex to protect the nu_sated counter
 * 	lock_print	>	mutex to protect the STDOUT when multiple threads are
 * 					printing messages
 * 	lock_start >	mutex to stop philosophers from entering their routine until
 * 					all threads are created
 * 	start		>	the start time of the simulation
 */
typedef struct s_ctrl
{
	int				nu_philo;
	int				max_meals;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	struct s_philo	*philos;
	pthread_t		*threads;
	t_mutex			*forks;
	bool			death;
	t_mutex			lock_death;
	int				nu_sated;
	t_mutex			lock_sated;
	t_mutex			lock_print;
	t_mutex			lock_start;
	t_ms			start;
}					t_ctrl;

/* each t_philo struct represents a philosopher: they are the parameter that
 * each philosopher takes to here routine.
 * nbr			>	the number (index) of the philosopher
 * left			>	pointer to her left fork
 * right		>	pointer to her right fork
 * last_action	>	the time her last action started
 * last_meal	>	the time her last meal started
 * lock_meal	>	mutex to protect the last_meal timestamp
 * meals		>	number of times she has eaten
 * status		>	either EATING (she is eating an cannot die) or NOT_EATING
 * 					(she is not eating, therefore watcher can declare her dead)
 * lock_status	>	mutex to protect the status flag
 * ctrl			>	pointer to the ctrl struct
 */
typedef struct s_philo
{
	int				nbr;
	t_mutex			*left;
	t_mutex			*right;
	t_ms			last_action;
	t_ms			last_meal;
	t_mutex			lock_meal;
	int				meals;
	bool			status;
	t_mutex			lock_status;
	t_ctrl			*ctrl;
}					t_philo;

/* status of individual philosopher: either she is eating and cannot be declared
 * dead by the watcher, or she is not eating (sleeping, thinking) and can be
 * declared dead if too much time has elapsed since her last meal
 */
# define EATING 0
# define NOT_EATING 1

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

/* init_structs.c */
t_ctrl			*init_controller(int argc, char **argv, t_err *error);
void			init_philos(t_ctrl *ctrl, t_err *error);

/* mutex.c */
void			init_all_mutexes(t_ctrl *ctrl, t_err *error);
bool			init_mutex(t_mutex *mutex, t_err *error);

/* simulation.c */
void			init_threads(t_ctrl *ctrl, t_err *error);

/* watcher.c */
void			watcher(t_ctrl *ctrl, int threads_created);

/* action.c */
void			print_action(t_philo *philo, char *action);
void			ph_eat(t_philo *philo);
void			ph_sleep(t_philo *philo);

/* set.c */
void			set_death(t_ctrl *ctrl);
void			increment_sated(t_ctrl *ctrl);
void			set_status(t_philo *philo, bool status);
void			set_last_meal(t_philo *philo, t_ms time);
	
/* check.c */
bool			check_death(t_ctrl *ctrl);
bool			check_sated(t_ctrl *ctrl);
bool			check_status(t_philo *philo);
t_ms			time_last_meal(t_philo *philo);

/* time.c */
t_ms			gettime(void);
void			ph_usleep(t_philo *philo, t_ms time);

/* exit_program.c */
int				exit_program(t_ctrl *controller, t_err *error);

#endif

