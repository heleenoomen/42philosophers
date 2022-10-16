/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 13:40:07 by hoomen           ###   ########.fr       */
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
 *	nu_philo	>	the number of philosophers (entered by user)
 *	max_meals	>	the number of times each philosopher must eat (entered by
 					user)
 *	nu_sated	>	the number of sated philosophers (who have eaten max_meals
 *					times)
 *	death		>	flag that is set to true as soon as one philosopher dies
 *	start		>	the start time of the simulation
 *	time_eat	>	the time a philosopher needs to finish her meal (entered
 					by user)
 *	time_sleep	>	the time a philosopher spends sleeping (entered by user)
 *	time_die	>	the maximum length of time a philosopher can go without
 *					eating before she dies (entered by user)
 *	forks		>	pointer to array of t_mutexs (every fork is a t_mutex)
 *	lock_death	>	mutex to protect the death flag
 *	lock_sated	>	mutex to protect the nu_sated counter
 *	lock_print	>	mutex to protect the STDOUT, so that only one thread can
 *					print at a time and messages don't get mixed up
 *	lock_start >	mutex to stop philosophers from entering their routine until
 *					all threads are created
 *	threads		>	pointer to array of threads (every thread is a philosopher)
 *	philos		>	pointer to array of t_philo struct, each of them representing
 *					one philosopher
 */
typedef struct s_ctrl
{
	int				nu_philo;
	int				max_meals;
	int				nu_sated;
	bool			death;
	t_ms			start;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	t_mutex			*forks;
	t_mutex			lock_death;
	t_mutex			lock_sated;
	t_mutex			lock_print;
	pthread_t		*threads;
	struct s_philo	*philos;
}					t_ctrl;

/* each t_philo struct represents a philosopher: they are the parameter that
 * each philosopher takes to her routine.
 * nbr			>			the number (index) of the philosopher
 * meals		>			number of times she has eaten
 * status		>			the philosopher is either EATING (meaning she is
 * 							cannot die) or involved in some OTHER activity
 * 							(thus she may die)
 * start_current_action	>	the time her last action started
 * last_meal	>			the time her last meal started
 * left			>			pointer to her left fork
 * right		>			pointer to her right fork
 * lock_meal	>			mutex to protect the last_meal timestamp
 * lock_status	>			mutex to protect the status flag
 * ctrl			>			pointer to the ctrl struct
 */
typedef struct s_philo
{
	int				nbr;
	int				meals;
	bool			status;
	t_ms			start_current_action;
	t_ms			last_meal;
	t_mutex			*left;
	t_mutex			*right;
	t_mutex			lock_meal;
	t_mutex			lock_status;
	t_ctrl			*ctrl;
}					t_philo;

/* status of individual philosopher: either she is EATING and thus cannot die,
 * or she is involved in any of the OTHER activities (thinking, sleeping) and
 * thus can be declared death by watcher
 */
# define EATING			0
# define OTHER			1

/* ph_atoui sets error based on the type of parameter it is converting from 
 * string to unsigned int: number of philosophers (N_PH), number of meals 
 * (N_MEALS) or one of the time parameters (TIME), in order to print an 
 * appropiate error message in case the parameter is invalid
 */
# define N_PH			0
# define N_MEALS		1
# define TIME			2

/* define the maximum number op philosopers */
# ifndef PH_MAX
#  define PH_MAX		200
# endif

/* utils.c */
void			*malloc_set_err(size_t size, t_err *error);
unsigned int	ph_atoui(char *s, t_err *error, short type);
int				my_strcmp(char *s1, char *s2);

/* init_structs.c */
t_ctrl			*init_controller(int argc, char **argv, t_err *error);

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

/* get.c */
bool			check_death(t_ctrl *ctrl);
bool			check_sated(t_ctrl *ctrl);
bool			check_status(t_philo *philo);
t_ms			time_last_meal(t_philo *philo);

/* time.c */
t_ms			gettime(void);
void			ph_usleep_eat(t_philo *philo);
void			ph_usleep_check(t_philo *philo, t_ms time);

/* exit_program.c */
int				exit_program(t_ctrl *controller, t_err *error);

#endif
