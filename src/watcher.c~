/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:06:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 14:22:03 by hoomen           ###   ########.fr       */
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
		print_action(philo, DIE, gettime());
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

/* if not all threads were created succesfully (threads_created !=
 * ctrl->nu_philo), watcher returns immediately. Otherwise, watcher checks first
 * if there is only one philosopher (check_lonely). If so, returns. If nu_philo
 * is more then one, watcher goes through the array of philos continuously to
 * check if one of them died (check_died). If so, watcher returns. At the end of
 * every cycle, watcher checkes if all philosophers are sated, in which case it
 * sets death to true for the simulation to end.
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

