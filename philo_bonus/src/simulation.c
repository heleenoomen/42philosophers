/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/12 09:14:31 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	run_philosophers(t_ctrl *ctrl)
{
	set_status(ctrl, OTHER);
	if (ctrl->index % 2)
		ph_usleep(ctrl, ctrl->time_eat - 10);
	while (check_died(ctrl) == false)
	{
		ph_eat(ctrl);
		ph_sleep(ctrl);
		print_action(ctrl, THINK);
	}
	pthread_join(ctrl->watcher, NULL);
	free(ctrl->cpids);
	free(ctrl);
	exit(DEATH);
}

void	watcher(t_ctrl *ctrl)
{
	t_ms	last_meal;

	while (1)
	{
		last_meal = time_last_meal(ctrl);
		if (check_status(ctrl) == OTHER && ((gettime() - last_meal)
				> ctrl->time_die))
		{
			set_died(ctrl);
			sem_wait(ctrl->print);
			printf("%u %i died\n", gettime() - ctrl->start, ctrl->index);
			sem_post(ctrl->forks);
			sem_post(ctrl->forks);
			return ;
		}
		if (check_sated(ctrl))
			return ;
	}
}

int	ft_fork(t_err *error)
{
	int	ret;

	ret = fork();
	if (ret == -1)
		*error = FORK;
	return (ret);
}

void	start_simulation(t_ctrl *ctrl, t_err *error)
{
	int	i;

	i = -1;
	ctrl->start = gettime();
	ctrl->last_meal = ctrl->start;
	ctrl->last_action = ctrl->start;
	while (++i < ctrl->nu_philo)
	{
		ctrl->cpids[i] = ft_fork(error);
		if (*error)
			exit_program(ctrl, error); 
		if (ctrl->cpids[i] == 0)
		{
			ctrl->index = i + 1;
			if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, (void *)ctrl))
			{
				sem_wait(ctrl->print);
				exit(THREAD_ERR_CHILD);
			}
			run_philosophers(ctrl);
		}
	}
	big_watcher(ctrl, error);
}
