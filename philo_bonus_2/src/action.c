/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/14 12:27:09 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_ctrl *ctrl, t_ms time, char *action)
{
	sem_wait(ctrl->print);
	if (!(ctrl->died) || !ft_strcmp(action, DIE))
		printf("%u %i %s\n", time, ctrl->index, action);
	sem_post(ctrl->print);
}
	
void	ph_eat(t_ctrl *ctrl)
{
	t_ms	last_meal;

	sem_wait(ctrl->forks);
	print_action(ctrl, gettime() - ctrl->start, FORK);
	sem_wait(ctrl->forks);
	last_meal = gettime();
	set_status(ctrl, EATING);
	set_last_meal(ctrl, last_meal);
	print_action(ctrl, last_meal - ctrl->start, FORK);
	print_action(ctrl, last_meal - ctrl->start, EAT);
	ph_usleep(ctrl, ctrl->time_eat - (gettime() - ctrl->last_meal));	
	sem_post(ctrl->forks);
	sem_post(ctrl->forks);
	printf("%i is here (38)\n", ctrl->index);
//	set_status(ctrl, NOT_EATING);
	ctrl->meals++;
	printf("%i is here\n", ctrl->index);
	if (ctrl->meals == ctrl->max_meals)
	{
		pthread_detach(ctrl->watcher);
		print_action(ctrl, gettime() - ctrl->start, "IS SATED");
		printf("nu meals = %i\n", ctrl->meals);
		exit(SATED);
	}
}

void	ph_sleep(t_ctrl *ctrl)
{
	t_ms	sleep;

	sleep = gettime();
	print_action(ctrl, sleep - ctrl->start, SLEEP);
	ph_usleep(ctrl, ctrl->time_sleep - (gettime() - sleep));
}

