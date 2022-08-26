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

#include "philo.h"

int	main(void)
{
	t_philo		philo_data;
	pthread_t	philosopher;

	philo_data.time_die = 500;
	philo_data.time_eat = 2;
	philo_data.time_sleep = 8;
	philo_data.last_meal.tv.tv_usec = 0;
	pthread_mutex_init(&philo_data.left_fork, NULL);
	pthread_mutex_init(&philo_data.right_fork, NULL);
	pthread_create(&philosopher, NULL, (void *) &routine);
	while (1)



