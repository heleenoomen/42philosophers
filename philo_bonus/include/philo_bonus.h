/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 14:37:52 by hoomen           ###   ########.fr       */
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
	int				*cpids;
	int				index;
	int				max_meals;
	int				meals;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	t_ms			last_meal;
	sem_t			*last_meal_sem;
	t_ms			start;
	bool			status;
	sem_t			*status_sem;
	bool			died;
	sem_t			*died_sem;
	pthread_t		watcher;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*start_sem;
}					t_ctrl;

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

/* define the maximum for time parameters */
# ifndef TIME_MAX
#  define TIME_MAX 2000 * 1000
# endif

/* define the maximum for the meals_max parameter */
# ifndef ME_MAX
#  define ME_MAX 2000 * 1000
# endif

/* exit statuses for philosophers */
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
void			print_action(t_ctrl *ctrl, t_ms time, char *action);
void			ph_eat(t_ctrl *ctrl);
void			ph_sleep(t_ctrl *ctrl);

/* set.c */
void			set_died(t_ctrl *ctrl);
void			set_status(t_ctrl *ctrl, bool status);
void			set_last_meal(t_ctrl *ctrl, t_ms time);
bool			incr_meals_check_sated(t_ctrl *ctrl);
	
/* check.c */
bool			check_died(t_ctrl *ctrl);
bool			check_status(t_ctrl *ctrl);
t_ms			time_last_meal(t_ctrl *ctrl);
bool			check_sated(t_ctrl *ctrl);

/* time.c */
t_ms			gettime(void);
void			ph_usleep(t_ctrl *ctrl, t_ms time_action);

/* exit_program.c */
int				exit_program(t_ctrl *ctrl, t_err *error);

#endif
