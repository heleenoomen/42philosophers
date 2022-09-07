/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 19:53:33 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* prints the action. Prints the time since the beginning of the simulation. 
 * Uses the print_lock mutex from the controller struct so that multiple philo-
 * sophers cannot print at the same time (this would mix up the messages to std-
 * out).
 * If 'death' has ocurred at the table, nothing gets printed, except when the 
 * philosopher himself is the one who died.
 */
void	print_action(t_philo *philo, char *action, t_ms time)
{
	t_ms	rel_time;

	pthread_mutex_lock(&(philo->controller->print_lock.mutex));
	rel_time = time - philo->controller->start;
	if (!philo->controller->death || !ft_strcmp(action, DIE))
		printf("%u %i %s\n", rel_time, philo->nbr, action);
	pthread_mutex_unlock(&(philo->controller->print_lock.mutex));
}
	
/* eating starts at the moment the second fork was acquired, thus the starting
 * time for the meal is equal to 'last_action' (=the taking of the 2nd fork).
 * Action is printed, last_meal is updated and ph_usleep is called to stop the
 * thread for time_eat ms.
 */
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->one->mutex));
	print_action(philo, FORK, gettime());
	pthread_mutex_lock(&(philo->two->mutex));
	philo->last_action = gettime();
	print_action(philo, FORK, philo->last_action);
}

void	eat(t_philo *philo)
{
	philo->last_meal = philo->last_action;
	print_action(philo, EAT, philo->last_meal);
	philo->meals++;
	ph_usleep(philo, philo->controller->time_eat);	
	pthread_mutex_unlock(&(philo->one->mutex));
	pthread_mutex_unlock(&(philo->two->mutex));	
}

/* time is acquired and a message is printed, ph_usleep is called to stop the
 * thread for time_sleep ms. last_action is updated.
 */
void	philo_sleep(t_philo *philo)
{
	philo->last_action = gettime();
	print_action(philo, SLEEP, philo->last_action);
	ph_usleep(philo, philo->controller->time_sleep);
}

/* time is acquired, a messages is printed and last_action is updated
 */
void	think(t_philo *philo)
{
	print_action(philo, THINK, gettime());
}
		
