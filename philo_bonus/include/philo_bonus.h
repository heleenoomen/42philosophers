/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 15:40:24 by hoomen           ###   ########.fr       */
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

/* error status */
typedef char			*t_err;

/* all data and semaphores needed for the simulation:
 * nu_philo			the number of philosophers (entered by user)
 * index			the number of the individual philosopher (for printing logs)
 * max_meals		the max_meals parameter (entered by user)
 * meals			counter: number of times the philosopher has eaten
 * cpids			array of process id's (every philosopher is a child process)
 * status			boolean: philosopher is either EATING (meaning she cannot
 * 					die), or busy withsome OTHER activity (sleeping, thinking;
 * 					meaning she may die)
 * died				boolean: set to true when philosopher dies
 * sated			boolean: set to true when number of times philosopher has
 * 					eaten equals max_meals
 * time_eat			time it takes the philosopher to eat a meal (entered by user)
 * time_sleep		time philosopher spends sleeping (entered by user)
 * time_die			max time a philosopher can go without eating before she dies
 * start_current_action	time when the philosopher started her last
 * 						activity
 * last_meal			time when the philosopher started her last meal
 * sem_t parameters:	semaphores used to protect variables checked and set by
 * 						philosopher (main thread) and watcher (helper thread) to
 * 						avoid data races
 * print_sem			semaphore to protect stdout, so that only one philosopher
 * 						can print to stdout at time and log messages don't get
 * 						mixed up
 * forks				semaphore representing the forks. Value is equal to number of
 * 						philosophers
 * watcher				each philosopher generates a watcher thread that checks if 
 * 						the philosopher has died or is sated (and should thus exit)
 */

typedef struct s_ctrl
{
	int				nu_philo;
	int				index;
	int				max_meals;
	int				meals;
	int				*cpids;
	bool			status;
	bool			died;
	bool			sated;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	t_ms			start_current_action;
	t_ms			last_meal;
	t_ms			start;
	sem_t			*last_meal_sem;
	sem_t			*status_sem;
	sem_t			*died_sem;
	sem_t			*sated_sem;
	sem_t			*print_sem;
	sem_t			*forks;
	pthread_t		watcher;
}					t_ctrl;

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

/* define the maximum number op philosopers and protect the system against
 * users who start the program with more than 200 threads.
 */
# ifndef PH_MAX
#  define PH_MAX		200
# endif

/* exit statuses for philosophers */
# define THREAD_ERR_CHILD	7
# define DEATH				8
# define SATED				9

/* exit status for program if user enters invalid parameters */
# define EXIT_USER_ERROR	2

/* utils.c */
void			*malloc_set_err(size_t size, t_err *error);
void			*calloc_set_err(size_t size, t_err *error);
unsigned int	ph_atuoi(char *s, t_err *error, short type);
int				my_strcmp(char *s1, char *s2);

/* init.c */
t_ctrl			*init_ctrl(int argc, char **argv, t_err *error);

/* simulation.c */
void			start_simulation(t_ctrl *ctrl, t_err *error);

/* big_watcher.c */
void			big_watcher(t_ctrl *ctrl, t_err *error);

/* actions.c */
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
void			ph_usleep_eat(t_ctrl *ctrl);
void			ph_usleep_sleep(t_ctrl *ctrl);

/* exit_program.c */
void			free_ctrl(t_ctrl *ctrl);
void			exit_program(t_ctrl *ctrl, t_err *error);

#endif
