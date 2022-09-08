/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:06:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 12:34:32 by hoomen           ###   ########.fr       */
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

bool	check_lonely(t_ctrl *controller)
{
	if (controller->nu_philo > 1)
		return (false);
	printf("here\n");
	controller->death = true;
	print_action(controller->philos, FORK, gettime());
	ph_usleep(controller->philos, controller->time_die);
	print_action(controller->philos, DIE, gettime());
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

void	watcher_wait(t_ctrl *controller)
{
	while (controller->go < controller->nu_philo)
	{
		if ((gettime() - controller->start) > controller->time_die)
			break ;
	}
}

void	watcher(t_ctrl *controller)
{
	int		i;
	t_philo	*philos;
	int		nu_philos;
	int		nu_sated;
	bool	max_meals;

	if (controller->max_meals == -1)
		max_meals = false;
	else
		max_meals = true;
	philos = controller->philos;
	nu_philos = controller->nu_philo;
	nu_sated = 0;
	controller-> go = 0;
	controller->start = gettime();
	controller->run = true;
	watcher_wait(controller);
	if (check_lonely(controller))
		return ;
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

