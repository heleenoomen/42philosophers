/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:50:48 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/01 14:51:50 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_parms 
{
	int	num_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	times_must_eat;
}		t_parms;

typedef struct	s_philo 
{
	struct timeval		last_meal;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			times_must_eat;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;	
	pthread_mutex_t		*print_lock;
	bool			died;
	int			index;
}				t_philo;

# define USAGE "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times\
	each philosopher must eat"
# define PHILOS "Please provide a valid number of philosophers. The number of philosophers must be of integer\
	type and the minimum number is 2"
# define	TIME "Please provide time parameters in whole milliseconds. Time parameters must be of integer type\
	(long int) and must be bigger than 0" 
# define ERROR_THREADS "Error: could not initialize threads"
# define ERROR_MUTEXES "Error: could not initialize mutexes"
# define ERROR_MUTEX_DESTROY "Error: unable to destroy mutex"
# define ERROR_MEM "Error: out of memory (malloc failed)"

#endif
