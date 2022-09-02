/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:25:04 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/02 13:42:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark I (init) */

/* allocates memory for a given number of philosophers
 * returns 0 upon success
 * prints an error message and returns -1 if malloc fails
 */ /*mark a*/
int	alloc_philosophers(t_main *main)
{
	main->philos = malloc(main->num_philos * sizeof(pthread_t));
	if (main->philos == NULL)
		return (return_error(ERROR_MEM, -1));
	return (0);
}

/* allocates memory for given number of mutexes (forks array)
 * initializes mutexes in forks array and print_lock mutex
 * returns 0 upon success
 * destroys all mutexes, prints message to STDERR and returns -1 
 * in case an error occurs
 */ /*mark m */
int	alloc_init_mutexes(t_main *main)

	int	i;

	main->forks = malloc(main->num_philos * sizeof(pthread_mutex_t))
	if (main->forks == NULL)
		return (return_error(ERROR_MEM, -1));
	i = 0;
	while (i < main->num_philos)
	{
		if (pthread_mutex_init((main->forks) + i, NULL))
		{
			destroy_mutexes(main->forks, i - 1);
			return (return_error(ERROR_MUTEXES, -1));
		}
		i++;
	}
	if (pthread_mutex_init(&(main->print_lock), NULL))
	{
		destroy_mutexes(main->forks, main->num_philos);
		return (return_error(ERROR_MUTEXES, -1));
	}
	return (0);
}

/* fills in the philos array with all the information the individual
 * philosophers need: time to die, eat and sleep, times they must eat, their
 * individual number ('index') and a pointer to the
 * print_lock mutex.
 */ /*mark f */
void fill_philos(t_main *main, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < main->num_philos)
	{
		(philos + i)->time_die = main->time_die;
		(philos + i)->time_eat = main->time_eat;
		(philos + i)->time_sleep = main->time_sleep;
		(philos + i)->times_must_eat = main->times_must_eat;
		(philos + i)->died = FALSE;
		(philos + i)->index = i + 1;
		(philos + i)->print_lock = &(main->print_lock);
		i++;
	}
	i = 0;
	while (i < main->num_philos - 1)
	{
		(philos + i)->left_fork = (main->forks) + i;
		(philos + i)->right_fork = (main->forks) + i + 1;
		i++;
	}
	(philos + main->num_philos - 1)->left_fork = (main->forks) + main->num_philos - 1;
	(philos + main->num_philos - 1)->right_fork = main->forks;
}
		
/* allocate memory for the array of t_philo structs with as many entries as there are
 * philosophers. Fill in the t_philo array with all the information the
 * philosophers need.
 */ /*mark p*/
int	alloc_init_philos(t_main *main, t_philo **philos)
{
	int	i;

	*philos = malloc(main->num_philos * sizeof(t_philo));
	if (*philos == NULL)
		return (return_error(ERROR_MEM, -1));
	fill_philos(main, *philos);
	return (0);
}

/* init the pthread_t array of philosophers (threads)
 * init the array of forks (mutexes)
 * init the array of structs called 'philos' (one t_philo for every philosopher) 
 */ /*mark j*/
int	init(t_main *main, t_philo **philos)
{
	if (alloc_philosophers(main) == -1)
		return (-1);
	if (alloc_init_mutexes(main) == -1)
	{
		free_allocs(main->philosophers, main->forks, NULL);
		return (-1);
	}
	if (alloc_init_philos(main, philos) == -1)
	{
		free_allocs(main->philosophers, main->forks, *philos);
		return (-1);
	}
	return (0);
}

