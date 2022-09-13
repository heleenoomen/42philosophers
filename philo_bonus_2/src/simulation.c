/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 19:27:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_died(t_ctrl *ctrl)
{
	bool	ret;
	sem_wait(ctrl->died_sem);
	ret = ctrl->died;
	sem_post(ctrl->died_sem);
	return (ret);
}

bool	check_status(t_ctrl *ctrl)
{
	bool	ret;

	sem_wait(ctrl->status_sem);
	ret = ctrl->status;
	sem_post(ctrl->status_sem);
	return (ret);
}

t_ms	timediff_last_meal(t_ctrl *ctrl)
{
	t_ms	time;

	sem_wait(ctrl->last_meal_sem);
	time = ctrl->last_meal;
	sem_post(ctrl->last_meal_sem);
	return (gettime() - time);
}

void	run_philosophers(t_ctrl *ctrl)
{
	ctrl->status = NOT_EATING;
	while (check_died(ctrl) == false)
	{
		ph_eat(ctrl);
		ph_sleep(ctrl);
		print_action(ctrl, gettime() - ctrl->start, THINK);
	}
	sem_close(ctrl->print);
	sem_close(ctrl->forks);
	sem_unlink("/forks");
	sem_unlink("/print");
	free(ctrl);
	exit(DEATH);
}

void	watcher(t_ctrl *ctrl)
{
	while (1)
	{
		if (check_status(ctrl) == NOT_EATING && timediff_last_meal(ctrl)
				> ctrl->time_die)
		{
			sem_wait(ctrl->died_sem);
			ctrl->died = true;
			sem_post(ctrl->died_sem);
			sem_wait(ctrl->print);
			printf("%u %i died\n", gettime() - ctrl->start, ctrl->index);
			exit(DEATH) ;
		}
		ph_usleep(ctrl, 200);
	}
}

void	big_watcher(t_ctrl *ctrl)
{
	int	status;
	int	sated;
	// int	i;

	sated = 0;
	while (1)
	{
		while (1)
		{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				if (status == DEATH)
				{
					i = -1;
					while (++i < ctrl->nu_philo)
						kill(ctrl->cpids[i], SIGKILL);
					return ;
				}
				if (status == SATED)
					sated++;
			}
			if (sated == ctrl->nu_philo)
				return ;
		}	
	}
}

void	start_simulation(t_ctrl *ctrl, t_err *error)
{
	int	i;

	ctrl->cpids = ft_malloc(ctrl->nu_philo * sizeof(int), error);
	i = -1;
	ctrl->start = gettime();
	ctrl->last_meal = ctrl->start;
	while (++i < ctrl->nu_philo)
	{
		ctrl->cpids[i] = ft_fork(ctrl, i - 1, error);
		if (ctrl->cpids[i] == 0)
		{
			ctrl->index = i + 1;
			if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, (void *)ctrl))
				exit_program (ctrl, i, error);
			pthread_detach(ctrl->watcher);
			run_philosophers(ctrl);
		}
	}
	big_watcher(ctrl);
}

