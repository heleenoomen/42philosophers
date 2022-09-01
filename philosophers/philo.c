/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:52:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/01 15:58:56 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark H	philo.h
 * mark P	parse.c
 * mark I	initialize.c
 * mark U	utils.c
 * mark M	main.c
 * mark F	free.c
 */



/* checks if 'died' parameter has been set to true already, in which case it returns 1 immediately
 * compares the actual time with the time of the last meal. If the difference is greater than the
 * time to die, the philosopher has died of starvation: a message is printed, died is set to true and
 * 1 is returned. Else, 0 is returned (philosopher didn't die of starvation so far)
 */
int	died(t_philo *philo_data)
{
	struct timeval	actual_time;
	
	if (philo_data->died == true)
		return (1);
	my_gettimeofday(&actual_time, NULL);
	if (actual_time.tv_usec - philo_data->last_meal.tv_usec > (philo_data->time_die * 1000))
	{
		printf("%i %i died\n", actual_time.tv_usec, philo_data->index);
		philo_data->died = true;
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo_data)
{
	pthread_mutex_lock(philo_data->left_fork);
	pthread_mutex_lock(philo_data->right_fork);
	if (!died(philo_data))
	{
		print_timestamp(philo_data, EAT);
		usleep(philo_data->time_eat);
	}
	pthread_mutex_unlock(philo_data->right_fork);
	pthread_mutex_unlock(philo_data->left_fork);
}	


void	routine(t_philo *philo_data)
{
	eat(philo_data);
	if (philo_data->died == true)
		return ;
	print_timpestamp(philo_data SLEEP);
	usleep(philo_data->time_sleep);
	if (died(philo_data))
		return ;
}

int	create_threads(pthread_t *philosophers, t_philo *philo_data, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		gettimeofday(&((philo_data + i)->last_meal), NULL);
		if (pthread_create(philosophers + i, NULL, (void *)routine, philo_data + i) == -1)
		{
			free_philo(philosophers, philo_data, num_philos, i - 1);
			return (putstr_return(ERROR_THREADS, -1));
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_parms		parms;
	t_philo		*philo_data;
	pthread_mutex_t	*forks;
	pthread_t	*philosophers;	
	int		i;

	if (parse(parms, argc, argv) == -1)
		return (1);
	if (init(parms, &forks, &philosophers, &philo_data) == -1)
		return (2);
	if (create_threads(philosophers, philo_data, parms.num_philos) == -1)
		return (3);
	while (1)
	{
		i = 0;
		while (i < parms.num_philos)
		{
			if ((philo_data + i)->died == true)
				break ;
			printf(

			i++;
		}
	}
	free_philo(philosophers, philo_data, parms.num_philos, parms.num_philos);
	return (0);
}

