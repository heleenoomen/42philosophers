/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:21:29 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 11:37:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	while (philo->ctrl->run == false);
	while (philo->ctrl->death == false)
	{
		if (died(philo))
			break ;
		take_forks(philo);
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

