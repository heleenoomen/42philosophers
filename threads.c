/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 12:34:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	get_forks(philo);
	while (philo->ctrl->run == false);
	philo->last_action = ctrl->start;
	philo->last_meal = ctrl->start;
	while (philo->ctrl->death == false)
	{
		if (died(philo))
			break ;
		take_forks(philo, one, two);
		if (philo->ctrl->death || died(philo))
			break ;	
		eat(philo);
		if (philo->ctrl->death || died(philo))
			break ;
		sleep(philo);
		if (philo->ctrl->death || died(philo))
			break ;
		think(philo);
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
			error = THREAD_ERR
			ctrl->death = true;
			break ;
		}
		i++;
	}
	ctrl->run = true;
	join_threads(ctrl);
}


