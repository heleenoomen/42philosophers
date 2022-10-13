/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 18:42:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* The philosophers (threads) are send to this function upon creation. They
 * wait for the main trhead to unlcok the lock_start mutex, so that they all
 * start simultaneously. They set their last_meal and start_current_action
 * variables to the start time of the simulation and set their status to OTHER
 * (meaning that, from now on, they may die if they are not eating). Uneven
 * philosophers wait for almost time_eat milliseconds, to avoid all philosophers
 * taking one fork at the same time, which would result in deadlock, and to make
 * sure that all philosophers get a fair chance to eat in time, without their
 * neighbours grabbing the forks all the time before they can.
 * The philosophers enter their routine (eat, sleep, think), and continue until
 * ctrl struct sets death to true.
 */
void	run_philosophers(t_philo *philo)
{
	pthread_mutex_lock(&(philo->ctrl->lock_start.mutex));
	pthread_mutex_unlock(&(philo->ctrl->lock_start.mutex));
	philo->last_meal = philo->ctrl->start;
	philo->start_current_action = philo->ctrl->start;
	set_status(philo, OTHER);
	if (philo->nbr % 2)
		ph_usleep_check(philo, philo->ctrl->time_eat - 10);
	while ((check_death(philo->ctrl) == false))
	{
		ph_eat(philo);
		ph_sleep(philo);
		print_action(philo, THINK);
	}
}

/* before exiting the program, main waits for all threads that were succesfully
 * created
 */
void	join_threads(t_ctrl *ctrl, int nu_created)
{
	int	i;

	i = -1;
	while (++i < nu_created)
		pthread_join(ctrl->threads[i], NULL);
}

/* Locks the lock_start mutex to prevent the simulation from starting until all
 * philosopers are created. Creates a thread for each philosopher, and
 * sends the philsopher off to the run_philosophers routine with her entry in
 * the philos array as a parameter. In case creation of a thread fails, death
 * is set to true so that all philosophers who were already created will return
 * immediately. After all threads are created, the start time is set and the
 * lock_start mutex is unlocked for the simulation to start.
 * Watcher is called to oversee if someone dies or if all become sated.
 * When watcher returns, join_threads is called to wait for all philophers who
 * were created succesfully to return.
 */
void	init_threads(t_ctrl *ctrl, t_err *error)
{
	int		nu_created;

	nu_created = -1;
	pthread_mutex_lock(&(ctrl->lock_start.mutex));
	while (++nu_created < ctrl->nu_philo)
	{
		if (pthread_create(ctrl->threads + nu_created, NULL, \
		(void *) &run_philosophers, ctrl->philos + nu_created))
		{
			*error = THREAD_ERR;
			set_death(ctrl);
			break ;
		}
	}
	ctrl->start = gettime();
	pthread_mutex_unlock(&(ctrl->lock_start.mutex));
	watcher(ctrl, nu_created);
	join_threads(ctrl, nu_created);
}
