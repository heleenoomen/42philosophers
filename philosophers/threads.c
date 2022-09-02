/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:08:11 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/02 13:54:43 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark R */

/* mark p */
int	print_timestamp(t_philo *philos, char *message)
{
	long int	timestamp;

	timestamp = get_timediff(&(philos->start_of_simulation));
	if (timestamp == -1)
	{
		philos->died = TIME_ERR;
		return ;
	}
	if (pthread_mutex_lock(philos->print_lock))
	{
		philos->died = LOCK_ERR;
		return ;
	}
	printf("%i ms %i %s", timestamp, philos->index, message);
	if (pthread_mutex_unlock(philos->print_lock))
		philos->died = UNLOCK_ERR;
}
	
/* checks if 'died' parameter has been set to true already, in which case it returns 1 immediately
 * compares the actual time with the time of the last meal. If the difference is greater than the
 * time to die, the philosopher has died of starvation: a message is printed, died is set to true and
 * 1 is returned. Else, 0 is returned (philosopher didn't die of starvation so far)
 */ /* mark d */
int	died(t_philo *philos)
{
	long int	time_passed;

	if (philos->died != FALSE)
		return (1);
	time_passed = get_timediff(philos->last_meal);
	if (time_passed == -1)
	{
		philos->died == TIME_ERR;
		return (1);
	}
	if (time_passed > philos->time_die)
	{
		printf("%i %i died\n", actual_time.tv_usec, philos->index);
		philos->died = TRUE;
		return (1);
	}
	return (0);
}

/* checks if philosopher died, if so, returns immediately. Takes left fork
 * first, then right fork. Eats. Places left fork back on the table (i.e.
 * unlocks), then right fork. At every step, prints a status message and checks
 * if the philosopher died. If so, returns. If one of the mutex functions fails,
 * sets 'died' parameter in philos struct to true, so that philosopher will
 * return.
 */ /* mark e */
void	eat(t_philo *philos)
{
	if (died(philos));
		return ;
	if (pthread_mutex_lock(philos->left_fork))
		philos->died = LOCK_ERR;
	if (died(philos))
		return ;
	print_timestamp(philos, FORK);
	if (died(philos))
		return ;
	if (pthread_mutex_lock(philos->right_fork))
	{
		philos->died = LOCK_ERR;
		pthread_mutex_unlock(philos->left_fork);
	}
	if (died(philos))
		return ;
	print_timestamp(philos, FORK);
	if (died(philos))
		return ;
	print_timestamp(philos, EAT);
	if (set_time(philos->last_meal) == -1)
		philos->died = TIME_ERR;
	usleep(philos->time_eat);
	if (pthread_mutex_unlock(philos->right_fork))
		philos->died = UNLOCK_ERR;
	if (pthread_mutex_unlock(philos->left_fork))
		philos->died = UNLOCK_ERR;
}	

/* calls eat to let philosopher eat. Afterwards, philosopher sleeps, then
 * thinks. At every step, checks if philosopher died. If so, returns immediately
 */ /* mark r */
void	routine(t_philo *philos)
{
	eat(philos);
	if (died(philos))
		return ;
	print_timestamp(philos, SLEEP);
		return ;
	usleep(philos->time_sleep);
	if (died(philos))
		return ;
	print_timestamp(philos, THINK);
}

/* create threads for all philosophers and sends them off to their routine, with
 * their entry in the philos array as a paramater.
 * right before creating the thread, sets the 'last_meal' time.
 * returns 0 upon succes
 * In case of an error, calls free_philo to join all threads and free all allocs
 * prints an error message and returns -1
 */ /* mark c */
int	create_threads(t_main *main, t_philo *philos)
{
	int				i;
	struct timeval	start;

	if (set_time(&start) == -1)
	{
		free_philo(main, philos, main->num_philos, 0);
		return (return_error(ERROR_TIME, -1);
	}
	i = 0;
	while (i < main->num_philos)
	{
		(philos + i)->start_of_simulation = start;
		(philos + i)->last_meal = start;
		if (pthread_create((main->philosophers) + i, NULL, (void *)routine, philos + i))
		{
			if (i > 0)
				free_philo(main, philos, main->num_philos, i - 1);
			return (return_error(ERROR_THREADS, -1));
		}
		i++;
	}
	return (0);
}

