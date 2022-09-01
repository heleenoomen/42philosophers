/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:19:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/01 15:23:29 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*mark F (free */

/* frees the array of philosopers and sets the pointer to NULL */
void	free_philos(pthread_t **philos)
{
	free(*philos);
	*philos = NULL;
}

/* destroys a given number mutexes in the forks array
 * does NOT free the forks array
 */
void	destroy_forks(pthread_mutex_t **forks, int num_of_mutexes)
{
	int	i;

	i = 0;
	while (i < num_of_mutexes)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
}

/* sets the 'died' parameter for all running philosophers to true. Sets their time_eat
 * and time_sleep parameters to 0, so that they will return immediately from their routines.
 * Waits for all the threads to join
 */
void	join_threads(pthread_t *philosophers, t_philo *philo_data, int num_to_join)
{
	int	i;

	i = 0;
	while (i < num_to_join)
	{
		(philo_data + i)->died = true;
		(philo_data + i)->time_to_eat = 0;
		(philo_data + i)->time_to_sleep = 0;
		i++;
	}
	i = 0;
	while (i < num_to_join)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
}

/* joins all threads, destroys all mutexes, free the philosophers array, the
 * philo_data array and the fork array.
 */
void	free_philo(pthread_t *philosophers, t_philo *philo_data, int num_philos, int num_to_join)
{
	int	i;

	join_threads(philosophers, philo_data, num_to_join);
	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy((philo_data + i)->right_fork) == -1)
			ft_putstr_fd(ERROR_MUTEX_DESTROY, 2);
		i++;
	}
	free(philo_data->right_fork);
	free(philosophers);
	free(philo_data);
}
