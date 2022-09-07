/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 12:45:45 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*who_is_neighbour(t_philo *philo, int neighbour_nbr)
{
	int	nu_philo;

	nu_philo = philo->controller->nu_philo;
	if (neighbour_nbr == 0)
		return (philo->controller->philos + nu_philo - 1);
	return (philo->controller->philos + philo->nbr - 2);
}

/* tells the philo which forks to use (get_forks). Waits until the controller
 * sets 'run' to true and sets last_action and last_meal to this timestamp.
 * Starts the routine until death occurred at the table.
 * if the philo has died (philo_die returns true) or another philo has died at
 * the table (philo->controller->death is true), breaks out of the routine and 
 * returns. 
 * takes forks, eats and leave forks. In between, death/die is only checked in the
 * respective function, for a philo should always leave the forks she has taken
 * before she returns (i.e. unlock any mutexes before returning).
 * in between the other steps (philo_sleep, philo_think) death/die is checked.
 */
void	routine(t_philo *philo)
{
	t_philo	*left;
	t_philo *right;
	
	get_forks(philo);
	left = who_is_neighbour(philo, philo->nbr - 1);
	right = who_is_neighbour(philo, philo->nbr + 1);
	while (philo->controller->run == false);
	philo->last_action = philo->controller->start;
	philo->last_meal = philo->controller->start;
	while (philo->controller->death == false)
	{
		if (philo_die(philo))
			break ;
		take_forks(philo);
		philo_eat(philo);
		leave_forks(philo);
		if (philo->controller->death || philo_die(philo))
			break ;
		philo_sleep(philo);
		if (philo->controller->death || philo_die(philo))
			break ;
		philo_think(philo);
		while (philo->meals > left->meals || philo->meals > right->meals)
		{
			if (philo->controller->death)
				return ;
		}
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

void	count_meals(t_ctrl *controller)
{
	int		max_meals;
	int		i;
	t_philo	*philos;
	int		nu_philos;

	if (controller->max_meals == -1)
		return ;
	max_meals = controller->max_meals;
	philos = controller->philos;
	nu_philos = controller->nu_philo;
	while (!controller->death)
	{
		i = -1;
		while (++i < nu_philos)
		{
			if (philos[i].meals < max_meals)
				break ;
			if (controller->death)
				return ;
		}
		if (i == nu_philos && !controller->death)
		{
			printf("max meals reached\n");
			controller->death = true;
			return ;
		}
	}
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
	ctrl->start = gettime();
	ctrl->run = true;
	count_meals(ctrl);
	join_threads(ctrl);
}


