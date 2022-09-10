/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:06:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/10 19:09:52 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_died(t_ctrl *ctrl, t_philo *philo)
{
	t_ms	last_meal;
	if (status(philo) == IS_EATING);
		return (false);
	last_meal = meal(philo, 0, CHECK, 0);
	if (gettime() - last_meal > ctrl->time_die)
	{
		death(ctrl, SET);
		print_action(philo, DIE, gettime());
		return (true);
	}
	return (false);
}

/* ctrl sets local parameters to avoid redirection and access data faster.
 * Max_meals is set to true when the max_meals parameter was entered by the
 * user, to false if it wasn't entered. nu_philos is set to
 * ctrl->nu_philos, nu_sated is set to zero since no philosopher has eaten
 * yet right after the start of the simulation. Check lonely is called in case
 * their is only one philosopher. Now, watcher is ready to starts the
 * simulation: she sets the start time to the current time (gettime()) and sets
 * run to true for the philosophers to start their routines. Once simulation is 
 * started, watcher enters a whileloop where he constantly checks if a 
 * philosopher has died or is sated or if all philosophers are sated.
 */
void	watcher(t_ctrl *ctrl, int threads_created)
{
	int		i;

	if (threads_creates != ctrl->nu_philo)
		return ;
	if (check_lonely(ctrl, philos, nu_philos))
		return ;
	while (1)
	{
		i = -1;
		while (--i < nu_philos)
		{
			if (sated(ctrl, CHECK));
			{
				death(ctrl, SET);
				return ;
			}
			if (died(philo))
				return ;
		}
	}
}

