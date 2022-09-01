/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:25:04 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/01 15:46:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark I (init) */

/* allocates memory for a given number of philosophers
 * returns 0 upon success
 * prints an error message and returns -1 if malloc fails
 */
int	init_philos(int	num_philos, pthread_t **philos)
{
	*philos = malloc(num_philos * sizeof(pthread_t));
	if (*philos == NULL)
		return (putstr_return(ERROR_MEM, -1));
	return (0);
}

/* mark f (forks) */
/* allocates memory for given number of mutexes (forks array)
 * initializes mutexes
 * writes error message to standard error if malloc or initialization fails and
 * returns -1.
 * On succes, returns 0.
 */
int	init_forks(int num_philos, pthread_mutex_t **forks)
{
	int	i;

	*forks = malloc(num_philos * sizeof(pthread_mutex_t))
	if (forks == NULL)
		return (putstr_return(ERROR_MEM, -1));
	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(forks + i, NULL))
		{
			destroy_forks(forks, i - 1);
			return (putstr_return(ERROR_MUTEXES, -1));
		}
		i++;
	}
	return (0);
}

int fill_in_data(t_parms parms, pthread_mutex_t **forks, t_philo *data)
{
	int	i;

	if (pthread_mutex_init(&(data->print_lock), NULL))
		return (putstr_return(ERROR_MUTEXES, -1));
	i = 0;
	while (i < parms.num_philos)
	{
		(data + i)->time_die = parms.time_die;
		(data + i)->time_eat = parms.time_eat;
		(data + i)->time_sleep = parms.time_sleep;
		(data + i)->times_must_eat = parms.times_must_eat;
		(data + i)->died = false;
		(data + i)->index = i + 1;
		(data + i)->print_lock = data->print_lock;
		if (i == 0)
			(data + i)->left_fork = forks + parms.num_philos - 1;
		else
			(data + i)->left_fork = forks + i - 1;
		if (i == parms.num_philos - 1)
			(data + i)->right_fork = forks;
		else
			(data + i)->right_fork = forks + i; 
		i++;
	}
	return (0);
}
		
int	init_data(t_parms parms, pthread_mutex_t **forks, t_philo **data)
{
	int	i;

	*data = malloc(parms.num_philos * sizeof(t_philo));
	if (*data == NULL)
		return (putstr_return(ERROR_MEM, -1));
	if (fill_in_data(parms, forks, *data) == -1)
		return (-1);
	return (0);
}

int	init(t_parms *parms, pthread_mutex_t **forks, pthread_t **philos, t_philo **data)
{
	if (init_philos(parms->num_philos, philos) == -1)
		return (-1);
	if (init_forks(parms->num_philos, forks) == -1)
	{
		free_philos(philos);
		return (-1);
	}
	if (init_data(parms, forks, data) == -1)
	{
		free_philos(philos);
		destroy_forks(forks, parms->num_philos);
		return (-1);
	}
	return (0);
}

