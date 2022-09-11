/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 13:55:36 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* philosophers wait until main treads unlocks the start mutex, so that they all
 * start simultaneously.
 * Phillosophers set their last_meal and last_action param to the start time of
 * the simulation. Philosophers set their status to NOT_EATING (from this moment
 * on, they can be declared dead by the main thread). Uneven philosophers wait
 * time_eat - 10 ms to avoid deadlocks. Philosophers enter their routine (eat,
 * sleep, think), and continue until ctrl struct sets death to true
 */
void	run_philosophers(t_philo *philo)
{
	pthread_mutex_lock(&(philo->ctrl->lock_start.mutex));
	pthread_mutex_unlock(&(philo->ctrl->lock_start.mutex));
	philo->last_meal = philo->ctrl->start;
	philo->last_action = philo->ctrl->start;
	set_status(philo, NOT_EATING);
	if (philo->nbr % 2)
		ph_usleep(philo, philo->ctrl->time_eat - 10);
	while ((check_death(philo->ctrl) == false))
	{
		ph_eat(philo);
		ph_sleep(philo);
		print_action(philo, THINK, gettime());
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

/* Creation of the philosophers and start sign for the simulation.
 * Start of the simulation is prohibited by the lock_start mutex until all
 * philosophers are created and start time is set.
 * In case creation of a thread fails, death is set to true so that all
 * philosophers who were already created will return immediately. 
 * After starting the simulation, watcher is called to oversee if someone dies
 * or if all become full.
 * Finally, join_threads is called to wait for all philos that were created to
 * return.
 */
void	init_threads(t_ctrl *ctrl, t_err *error)
{
	int		nu_created;

	nu_created = -1;
	pthread_mutex_lock(&(ctrl->lock_start.mutex));
	while (++nu_created < ctrl->nu_philo)
	{
		if (pthread_create(ctrl->threads + nu_created, NULL, (void *) &run_philosophers,
					ctrl->philos + nu_created))
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

