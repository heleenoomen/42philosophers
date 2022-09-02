/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:19:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/02 13:57:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*mark F (free */

/* frees malloced entities. Pass NULL for entities that are not (yet) malloced
 */
void	free_allocs(pthread_t *phils, pthread_mutex_t *forks, t_philo *philos)
{
	free(phils);
	free(forks);
	free(philos);
}

/* destroys all mutexes (i.e. 'forks'). Frees the fork array 
 */ /* mark m */
void	destroy_mutexes(t_main *main, int num_of_mutexes)
{
	int	i;

	i = 0;
	while (i < num_of_mutexes)
	{
		pthread_mutex_destroy((main->forks) + i);
		i++;
	}
}

/* sets the 'died' parameter for all running philosophers to true. Sets their
 * time_eat and time_sleep parameters to 0, so that they will return immediately
 * from their routines. Waits for all the threads to join.
 */ /* mark t */
void	join_threads(t_main *main, t_philo *philos, int num_to_join)
{
	int	i;

	i = 0;
	while (i < num_to_join)
	{
		if ((philos + i)->died == FALSE)
			(philos + i)->died = TRUE;
		(philos + i)->time_to_eat = 0;
		(philos + i)->time_to_sleep = 0;
		i++;
	}
	i = 0;
	while (i < num_to_join)
	{
		pthread_join((main->philosophers) + i, NULL);
		i++;
	}
}

/* joins all threads, destroys all mutexes, free the philosophers array, the
 * philos array and the fork array.
 */ /* mark f */
void	free_philo(t_main *main, t_philo *philos, int num_philos, int num_to_join)
{
	int	i;

	join_threads(main, philos, num_to_join);
	destroy_mutexes(main, num_philos);
	pthread_mutex_destroy(&(main->print_mutex));
	free(main->forks);
	i = 0;
	while (i < main->num_philos)
	{
		if (philos[i]->died > 1)
		{
			if (philos[i]->died == TIME_ERR)
				ft_putstr_fd(ERROR_TIME, 2);
			if (philos[i]->died == LOCK_ERR)
				ft_putstr_fd(ERROR_LOCK);
			if (philos[i]->ided = UNLOCK_ERR)
				ft_putstr_fd(ERROR_UNLOCK);
		}
		i++;
	}
	free(main->philosophers);
	free(philos);
}

