/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:21:29 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 17:47:20 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	while (philo->ctrl->run == false);
	while (philo->ctrl->death == false)
	{
		if (die(philo))
			break ;
		take_forks(philo);
		if (philo->ctrl->death || die(philo))
			break ;	
		eat(philo);
		leave_forks(philo);
		if (philo->ctrl->death || die(philo))
			break ;
		sleep(philo);
		if (philo->ctrl->death || die(philo))
			break ;
		think(philo);
	}
}

