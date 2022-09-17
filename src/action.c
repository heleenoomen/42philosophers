/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 15:47:55 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <errno.h>

/* prints the action. To avoid messages getting mixed up, threads wanting to
 * print can only do so after locking the lock_print mutex.
 * In case death has occurred, threads can no longer print, unless 'death' was
 * set to true because of saturation or unless the message is the DIE message
 */
void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&(philo->ctrl->lock_print.mutex));
	philo->last_action = gettime();
	if (!(check_death(philo->ctrl)) || check_sated(philo->ctrl)
			|| !ft_strcmp(action, DIE))
		printf("%u %i %s\n", philo->last_action - philo->ctrl->start, philo->nbr, action);
	pthread_mutex_unlock(&(philo->ctrl->lock_print.mutex));
}
	
/* first, left and right fork mutexes must be acquired (corresponding messages
 * must be printed). Immediately after the second fork is acquired, start_meal
 * is set and philo changes her status to EATING to avoid the main thread from
 * declaring her dead. Consequently, last_meal is updated, the number of meals
 * is incremented, saturation is checkedd for and incremented in the ctrl struct
 * if the philo is indeed full. Messages are printed (FORK, EAT) and the threads
 * goes to sleep for the remaining eating time (ph_usleep). When done eating,
 * the forks mutexes are unlocked and status is changed to NOT_EATING.
 */
void	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left->mutex));
	print_action(philo, FORK);
	pthread_mutex_lock(&(philo->right->mutex));
	print_action(philo, FORK);
	print_action(philo, EAT);
	set_status(philo, EATING);
	set_last_meal(philo, philo->last_action);
	ph_usleep(philo, philo->ctrl->time_eat);	
	pthread_mutex_unlock(&(philo->right->mutex));
	pthread_mutex_unlock(&(philo->left->mutex));	
	set_status(philo, NOT_EATING);
	philo->meals++;
	if (philo->meals == philo->ctrl->max_meals)
		increment_sated(philo->ctrl);
}

/* time is acquired and a message is printed, ph_usleep is called to stop the
 * thread for time_sleep ms. last_action is updated.
 */
void	ph_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	ph_usleep(philo, philo->ctrl->time_sleep);
}

