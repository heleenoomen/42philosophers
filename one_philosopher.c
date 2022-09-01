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
	t_philo		philo_data;
	pthread_t	philosopher;

	philo_data.time_die = 500;
	philo_data.time_eat = 2;
	philo_data.time_sleep = 8;
	philo_data.died = false;
	pthread_mutex_init(&philo_data.left_fork, NULL);
	pthread_mutex_init(&philo_data.right_fork, NULL);
	gettimeofday(&philo_data.last_meal, NULL);
	pthread_create(&philosopher, NULL, (void *) &routine, &philo_data);
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
