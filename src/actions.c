/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/05 19:05:25 by hoomen           ###   ########.fr       */
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
	t_fork	*print_lock;
	t_ms	rel_time;

	print_lock = &(philo->controller->print_lock);
	time--;
	while (print_lock->locked)
	{
		if (!philo->controller->death && !philo->died && philo_die(philo))
			return ;
	}
	pthread_mutex_lock(&(philo->controller->print_lock.mutex));
	rel_time = gettime() - philo->controller->start;
	if (!philo->controller->death || philo->died)
		printf("%u %i %s\n", rel_time, philo->nbr, action);
	pthread_mutex_unlock(&(philo->controller->print_lock.mutex));
}
	
/* eating starts at the moment the second fork was acquired, thus the starting
 * time for the meal is equal to 'last_action' (=the taking of the 2nd fork).
 * Action is printed, last_meal is updated and philo_action is called to stop the
 * thread for time_eat ms.
 */
void	philo_eat(t_philo *philo)
{
	if (philo->died)
		return ;
	print_action(philo, EAT, philo->last_action);
	philo->last_meal = philo->last_action;
	philo_action(philo, philo->controller->time_eat);
	philo->meals++;
}

/* time is acquired and a message is printed, philo_action is called to stop the
 * thread for time_sleep ms. last_action is updated.
 */
void	philo_sleep(t_philo *philo)
{
	t_ms	time;

	time = gettime();
	print_action(philo, SLEEP, time);
	philo->last_action = time;
	philo_action(philo, philo->controller->time_sleep);
}

/* time is acquired, a messages is printed and last_action is updated
 */
void	philo_think(t_philo *philo)
{
	t_ms	time;

	time = gettime();
	print_action(philo, THINK, time);
	philo->last_action = time;
}
		
/* Current time is acquired through gettime(). If the current time minus the
 * time from the last meal is less than time_die, it means the philosopher has
 * not died of starvation yet and false is returned.
 * Else, 'death' in the controller structure and 'died' in the philo structure
 * are set to true. print_action is called to print the decease message and
 * true is returned
 */
bool	philo_die(t_philo *philo)
{
	t_ms time;

	time = gettime();
	if (philo->controller->time_die > (time - philo->last_meal))
		return (false);
	philo->controller->death = true;
	philo->died = true;
	print_action(philo, DIE, time);
	return (true);
}




