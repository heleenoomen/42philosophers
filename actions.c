/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 13:03:44 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action, t_ms time)
{
	pthread_mutex_lock(&(philo->controller->print_lock);
	printf("%u ms\t%i %s\n", time, philo->nbr, action);
	pthread_mutex_unlock(&(philo->controller->print_lock);
}
	
void	eat(t_philo *philo)
{
	print_action(philo, EAT, philo->last_action);
	philo->last_meal = philo->last_action;
	philo_sleep(philo, philo->time_eat);
}

void	sleep(t_philo *philo)
{
	t_ms	time;

	time = gettime();
	print_action(philo, SLEEP);
	philo->last_action = time;
	philo_sleep(philo, philo->time_sleep);
}

void	think(t_philo *philo)
{
	t_ms	time;

	time = gettime();
	print_action(philo, THINK);
	philo->last_action = time;
}
		
