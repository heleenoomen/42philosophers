/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/12 19:01:25 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <errno.h>

void	print_action(t_ms time, int index, char *action)
{
	t_ms	rel_time;

	rel_time = time - ctrl->start;
	sem_wait("/print");
	if (!(check_death(ctrl)) || check_sated(ctrl)
			|| !ft_strcmp(action, DIE))
		printf("%u %i %s\n", rel_time, index, action);
	sem_post("/print");
}
	
void	ph_eat(t_ctrl *ctrl, int index)
{
	sem_wait("/forks");
	print_action(gettime(), ctrl->nbr, FORK);
	sem_wait("/forks");
	ctrl->last_meal = gettime();
	ctrl->status = EATING;
	print_action(ctrl->last_meal, ctrl->nbr, FORK);
	print_action(ctrl->last_meal, ctrl->nbr, EAT);
	philo->meals++;
	if (philo->meals == philo->ctrl->max_meals)
	{
		pthread_detach(&(ctrl->watcher));
		exit (SATED);
	}
	ph_usleep(ctrl, time_eat - (gettime() - ctrl->last_meal));	
	sem_post("/forks");
	sem_post("/forks");
	philo->status = NOT_EATING;
}

void	ph_sleep(t_philo *philo)
{
	t_ms	sleep;

	sleep = gettime();
	print_action(sleep, ctrl->nbr, SLEEP);
	ph_usleep(ctrl, ctrl->time_sleep - (gettime() - sleep));
}

