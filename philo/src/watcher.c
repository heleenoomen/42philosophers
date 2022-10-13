/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:06:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 18:43:15 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* status of the philosopher is checked. If she is eating, she cannot die, so
 * there is nothing to check (return false). Else, the time of her last meal is
 * checked and measured against the current time (gettime()).
 * If the time elapsed is bigger than her time_die, she dies: death is set to
 * true, the action is printed and true is return. If less time has elapsed, the
 * philo does not die and false is returned.
 */
bool	check_died(t_ctrl *ctrl, t_philo *philo)
{
	t_ms	last_meal;

	if (check_status(philo) == EATING)
		return (false);
	last_meal = time_last_meal(philo);
	if (gettime() - last_meal > ctrl->time_die)
	{
		set_death(ctrl);
		print_action(philo, DIE);
		return (true);
	}
	return (false);
}

/* if nu_philo equals 1, death is set to true to make the philosopher thread
 * return immediately. The philosopher takes a fork and, after time_die has
 * elapsed, she dies. Messages are printed and check_lonely returns to watcher,
 * which will then return immediately
 */
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

/* returns immediately in case not all threads were created succesfully
 * (threads_created != ctrl->nu_philo).
 * Checks if there is only one philosopher, in which case a separate routin is
 * carried out.
 * If there are multiple philosophers, watcher starts checking continuously if
 * one of them died or if all of them where sated. In both cases, watcher sets
 * 'death' to true to indicate that all philosophers should return and watcher
 * itself returns to start_simulation.
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
