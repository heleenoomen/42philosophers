/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/10 19:09:52 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <errno.h>

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

	rel_time = time - philo->ctrl->start;
	pthread_mutex_lock(&(philo->ctrl->print_lock.mutex));
	if (!philo->ctrl->death || !ft_strcmp(action, DIE))
		printf("%u %i %s\n", rel_time, philo->nbr, action);
	pthread_mutex_unlock(&(philo->ctrl->print_lock.mutex));
}
	
void	ph_eat(t_philo *philo)
{
	t_ms	start_meal;
	pthread_mutex_lock(&(philo->left->mutex));
	print_action(philo, FORK, gettime());
	pthread_mutex_lock(&(philo->right->mutex));
	start_meal = gettime();
	meal(philo, start_meal, SET, IS_EATING);
	philo->meals++;
	if (philo->meals == max_meals)
		sated(philo, SET);
	print_action(philo, EAT, philo->last_meal);
	ph_usleep(philo, philo->ctrl->time_eat);	
	pthread_mutex_unlock(&(philo->right->mutex));
	pthread_mutex_unlock(&(philo->left->mutex));	
	meal(philo, philo->last_meal, SET, NOT_EATING);
}

/* time is acquired and a message is printed, ph_usleep is called to stop the
 * thread for time_sleep ms. last_action is updated.
 */
void	ph_sleep(t_philo *philo)
{
	print_action(philo, SLEEP, gettime());
	ph_usleep(philo, philo->ctrl->time_sleep);
}

