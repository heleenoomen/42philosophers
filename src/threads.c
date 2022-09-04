/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 19:14:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	get_forks(philo);
	while (philo->controller->run == false);
	philo->last_action = philo->controller->start;
	philo->last_meal = philo->controller->start;
	while (philo->controller->death == false)
	{
		if (philo_die(philo))
			break ;
		take_forks(philo);
		if (philo->controller->death || philo_die(philo))
			break ;	
		philo_eat(philo);
		leave_forks(philo);
		if (philo->controller->death || philo_die(philo))
			break ;
		philo_sleep(philo);
		if (philo->controller->death || philo_die(philo))
			break ;
		philo_think(philo);
	}
}

void	join_threads(t_ctrl *ctrl)
{
	int	i;
	int	nu_philo;

	nu_philo = ctrl->nu_philo;
	i = 0;
	while (i++ < nu_philo)
		pthread_join(ctrl->threads[i], NULL);
}

void	init_threads(t_ctrl *ctrl, char *error)
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
			error = THREAD_ERR;
			ctrl->death = true;
			break ;
		}
		i++;
	}
	ctrl->run = true;
	join_threads(ctrl);
}


