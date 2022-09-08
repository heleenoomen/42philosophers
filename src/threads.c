/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 12:28:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	routine(t_philo *philo)
{
	bool		*death;

	death = &(philo->controller->death);
	while ((philo->controller->run) == false);
	philo->last_action = philo->controller->start;
	philo->last_meal = philo->controller->start;
	philo->controller->go++;
	while (!(*death))
	{
		take_forks(philo);
		philo->free = false;
		eat(philo);
		if (philo->meals == philo->controller->max_meals)
			philo->sated = true;
		if (*death)
			return ;	
		philo_sleep(philo);
		philo->free = true;
		if (*death)
			return ;
		think(philo);
	}
}

/* when the simulation is over, the main thread waits for the other threads to 
 * return befor exiting the program. pthread_join waits for threads to join (=
 * for them to return from their routine)
 */
void	join_threads(t_ctrl *ctrl)
{
	int	i;
	int	nu_philo;

	nu_philo = ctrl->nu_philo;
	i = 0;
	while (i++ < nu_philo)
		pthread_join(ctrl->threads[i], NULL);
}


/* controller sets 'death' to false since no philosophers die befor the simulation
 * starts. Controllers sets 'run' to false so that the threads will wait until all
 * threads are created successfully before they start their eat-sleep-think routine.
 * Controller initiates a thread for each philosopher and sends her of to her routine,
 * with her entry in the philos array of structs as a parameter.
 * If thread creation fails, controller sets death to true so that any threads created
 * so far will return from the routine immediately.
 * After creating threads, controller sets start time of simulation (gettime()) and
 * sets 'run' to true so that all threads starts the simulation at the same time.
 * Controller then goes to join_threads, to wait for all threads to return from their
 * routine
 */
void	init_threads(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_philo;

	ctrl->death = false;
	ctrl->run = false;
	nu_philo = ctrl->nu_philo;
	i = 0;
	while (i < nu_philo)
	{
		if (pthread_create(ctrl->threads + i, NULL, (void *)routine, ctrl->philos + i))
		{
			*error = THREAD_ERR;
			ctrl->death = true;
			break ;
		}
		i++;
	}
	watcher(ctrl);
	join_threads(ctrl);
}


