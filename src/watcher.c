/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:06:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/09 12:02:13 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_died(t_ctrl *controller, t_philo *philo)
{
	if (!philo->free)
		return (false);
	if (gettime() - philo->last_meal > controller->time_die)
	{
		controller->death = true;
		print_action(philo, DIE, gettime());
		return (true);
	}
	return (false);
}

bool	check_sated(t_philo *philo)
{
	if (philo->sated)
	{
		philo->sated = false;
		return (true);
	}
	return (false);
}

bool	check_lonely(t_ctrl *controller, t_philo *philos, int nu_philo)
{
	if (nu_philo > 1)
		return (false);
	controller->start = gettime();
	controller->run = true;
	while (!philos->free);
	while (gettime() - philos->last_meal < controller->time_die);
	print_action(philos, DIE, gettime());
	// {
		// if (check_died(controller, philos))
			// return (true);
	// }
	return (true);
}

bool	check_all_sated(t_ctrl *controller, int nu_sated, int nu_philos, bool max_meals)
{
	if (nu_sated == nu_philos && max_meals)
	{
		controller->death = true;
		return (true);
	}
	return (false);
}

/* controller sets local parameters to avoid redirection and access data faster.
 * Max_meals is set to true when the max_meals parameter was entered by the
 * user, to false if it wasn't entered. nu_philos is set to
 * controller->nu_philos, nu_sated is set to zero since no philosopher has eaten
 * yet right after the start of the simulation. Check lonely is called in case
 * their is only one philosopher. Now, watcher is ready to starts the
 * simulation: she sets the start time to the current time (gettime()) and sets
 * run to true for the philosophers to start their routines. Once simulation is 
 * started, watcher enters a whileloop where he constantly checks if a 
 * philosopher has died or is sated or if all philosophers are sated.
 */
void	watcher(t_ctrl *controller)
{
	int		i;
	t_philo	*philos;
	int		nu_philos;
	int		nu_sated;
	bool	max_meals;

	nu_philos = controller->nu_philo;
	philos = controller->philos;
	if (check_lonely(controller, philos, nu_philos))
		return ;
	if (controller->max_meals == -1)
		max_meals = false;
	else
		max_meals = true;
	nu_sated = 0;
	controller->start = gettime();
	controller->run = true;
	while (1)
	{
		i = -1;
		while (++i < nu_philos)
		{
			if (check_sated(philos + i))
				nu_sated++;
			if (check_died(controller, philos + i))
				return ;
		}
		if (check_all_sated(controller, nu_philos, nu_sated, max_meals))
			return ;
	}
}

