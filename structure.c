/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:38:29 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/22 19:53:08 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	routine(t_philo *philo_data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo_data->left_fork);
		pthread_mutex_lock(&philo_data->right_fork);
		philo_data->last_meal.tv_usec = gettimeofday(&philo_data->last_meal, NULL);
		gettimeofday(&philo_data->actual_time, NULL);
		if (philo_data->actual_time.tv_usec - philo_data->last_meal.tv_usec < philo_data->time_die)
		{
			philo_data->died = true;
			return ;
		}
		printf("philosopher is eating\n");
		usleep(philo_data->time_eat);
		pthread_mutex_unlock(&philo_data->right_fork);
		pthread_mutex_unlock(&philo_data->left_fork);
		gettimeofday(&philo_data->actual_time, NULL);
		if (philo_data->actual_time.tv_usec - philo_data->last_meal.tv_usec < philo_data->time_die)
		{
			philo_data->died = true;
			return ;
		}
		printf("philosopher is sleeping\n");
		usleep(philo_data->time_sleep);
		gettimeofday(&philo_data->actual_time, NULL);
		if (philo_data->actual_time.tv_usec - philo_data->last_meal.tv_usec < philo_data->time_die)
		{
			philo_data->died = true;
			return ;
		}
		printf("philosopher is thinking\n");
		if (i > 9)
		{
			philo_data->died = true;
			return ;
		}
		i++;
	}
}


int	main(void)
{
	t_ph_parms	philo_parms;
	t_philo		*philo_data;
	pthread_t	*philosophers;
	int		i;

	/* get philo_data from user input, if argc is < 4 or > 5, return */
	if (parse(&philo_parms, argc, argv) == -1)
		return (1);
	/* initialize philo structs */
	if (initialize(philo_parms, philo_data, philosophers) == -1);
		/* malloc an array of pthread_t, for each philosopher one thread */
		/* malloc an array of philo_data, for each philosopher one t_philo entry */
		/* malloc the right and left fork mutex for each philosopher. For the last one:
		 * only the right fork, the left fork will point to the fork of the first philosopher */
		/* initialize the mutextes */
		/* fill in time_die, time_eat and time_sleep and set 'died' to false in every entry of the
		 * philo_data table */	
		/* in case of failure, free and destroy everything created so far and return -1 */
		return (2);
	i = 0;
	/* send off the philosophers to their routine */
	while (i < philo_parms.num_philos)
	{
		gettimeofday(&philo_data[i].last_meal);
		if (pthread_create(philosophers + i, NULL, (void *) routine, philo_parms + i)
			return (join_and_return(philo_data, philosophers, i - 1, 3);
				/* sets the 'died' value of all philosophers created so far to true, so that they return */
				/* then destroys mutexes, free philosophers array and philo_data array, returns with ret value */
		i++;
	}
	while (1)
	{
		if (philo_data.died == true)
		{
			pthread_join(philosopher, NULL);
			pthread_mutex_destroy(&philo_data.left_fork);
			pthread_mutex_destroy(&philo_data.right_fork);
			return (0);
		}
	}	

}
