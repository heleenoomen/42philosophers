/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:06:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 10:43:15 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_died(t_ctrl *ctrl, t_philo *philo)
{
	t_ms	last_meal;

	if (check_status(philo) == EATS)
		return (false);
	last_meal = time_last_meal(philo);
	if (gettime() - last_meal > ctrl->time_die)
	{
		set_death(ctrl);
		print_action(philo, DIE, gettime());
		return (true);
	}
	return (false);
}

bool	check_lonely(t_ctrl *ctrl)
{
	if (ctrl->nu_philo > 1)
		return (false);
	set_death(ctrl);
	printf("%u 1 %s\n", gettime() - ctrl->start, FORK);
	while (gettime() - ctrl->start < ctrl->time_die)
		usleep(500);
	printf("%u 1 %s\n", gettime() - ctrl->start, DIE);
	return (true);
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

	if (threads_created != ctrl->nu_philo)
		return ;
	if (check_lonely(ctrl))
		return ;
	while (1)
	{
		i = -1;
		while (++i < ctrl->nu_philo)
		{
			if (check_died(ctrl, ctrl->philos + i))
				return ;
		}
		if (check_sated(ctrl))
		{
			set_death(ctrl);
			return ;
		}
	}
}

