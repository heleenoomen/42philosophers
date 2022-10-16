/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 13:46:42 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* prints the action. To avoid messages getting mixed up, threads wanting to
 * print can only do so after locking the lock_print mutex.
 * In case death has occurred, threads can no longer print, unless 'death' was
 * set to true because of saturation or unless the message is the DIE message
 */
void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&(philo->ctrl->lock_print.mutex));
	philo->start_current_action = gettime();
	if (!(check_death(philo->ctrl)) || !my_strcmp(action, DIE))
		printf("%u %i %s\n", philo->start_current_action - philo->ctrl->start, \
		philo->nbr, action);
	pthread_mutex_unlock(&(philo->ctrl->lock_print.mutex));
}

/* acquire the mutex for left fork and print the action, then idem for right
 * fork.
 */
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left->mutex));
	print_action(philo, FORK);
	pthread_mutex_lock(&(philo->right->mutex));
	print_action(philo, FORK);
}

/* unlock both mutexes that represent right and left fork
 */
void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->right->mutex));
	pthread_mutex_unlock(&(philo->left->mutex));
}

/* take forks, print EAT message, set status to eating and set last meal to
 * the time the current action (EAT) started. Call ph_usleep_eat to stop the
 * thread for time_eat precisely, then leave forks, increment meals and check
 * if max_meals is reached. If so, increment the sated counter.
 */
void	ph_eat(t_philo *philo)
{
	bool	sated;

	if (philo->ctrl->time_eat == 0)
		return ;
	take_forks(philo);
	print_action(philo, EAT);
	set_status(philo, EATING);
	set_last_meal(philo, philo->start_current_action);
	sated = ++philo->meals == philo->ctrl->max_meals;
	ph_usleep_eat(philo);
	leave_forks(philo);
	if (sated && philo->ctrl->max_meals != -1)
		increment_sated(philo->ctrl);
}

/* time is acquired and a message is printed, ph_usleep_sleep is called to
 * stop the thread for time_sleep ms. start_current_action is updated.
 */
void	ph_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	set_status(philo, OTHER);
	ph_usleep_check(philo, philo->ctrl->time_sleep);
}
