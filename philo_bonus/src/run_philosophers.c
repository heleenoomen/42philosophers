/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:29:11 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/14 21:01:23 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* thread routine for each philosopher. Continuously checks if the status of the
 * philosopher is OTHER, in which case watcher also checks if the time since the
 * last meal is bigger than time_die. If so, sets 'died' parameter to true,
 * waits for the print semaphore, prints the death message and does not post on
 * the print semaphore again, so that no other thread will be able to print any
 * more messages. To avoid any chance of deadlock, posts twice on the forks and
 * returns. At each iterations, checks for saturation too and returns if the
 * philosopher is sated.
 */
void	watcher(t_ctrl *ctrl)
{
	t_ms	last_meal;

	while (!check_died(ctrl))
	{
		last_meal = time_last_meal(ctrl);
		if (check_status(ctrl) == OTHER && ((gettime() - last_meal)
				> ctrl->time_die))
		{
			sem_wait(ctrl->print_sem);
			if (!check_died(ctrl))
				printf("%u %i died\n", gettime() - ctrl->start, ctrl->index);
			set_died(ctrl);
			sem_post(ctrl->forks);
			sem_post(ctrl->forks);
			sem_post(ctrl->end_of_simulation);
			return ;
		}
	}
}

void	watcher2(void *parm)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *)parm;
	sem_wait(ctrl->end_of_simulation);
	set_died(ctrl);
	sem_post(ctrl->end_of_simulation);
	sem_post(ctrl->end_of_simulation);
}

void	create_watcher_threads(t_ctrl *ctrl)
{
	if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, \
	(void *)ctrl))
	{
		sem_post(ctrl->end_of_simulation);
		sem_post(ctrl->end_of_simulation);
		free_ctrl(ctrl);
		exit(THREAD_ERR_CHILD);
	}
	if (pthread_create(&(ctrl->watcher2), NULL, (void *) &watcher2, \
	(void *)ctrl))
	{
		sem_post(ctrl->all_sated);
		sem_post(ctrl->end_of_simulation);
		sem_post(ctrl->end_of_simulation);
		set_died(ctrl);
		pthread_join(ctrl->watcher, NULL);
		free_ctrl(ctrl);
		exit(THREAD_ERR_CHILD);
	}
}

/* uneven philosophers wait for time_eat - 10 milliseconds to avoid deadlocks.
 * the, philosophers enter their routine of eat, sleep, think until they die.
 * if they die, they wait for the watcher thread to join, free their resources
 * and exit with exit status DEATH
 */
void	run_philosophers(t_ctrl *ctrl)
{
	create_watcher_threads(ctrl);
	set_status(ctrl, OTHER);
	if (ctrl->index % 2)
		ph_usleep_sleep(ctrl);
	while (check_died(ctrl) == false)
	{
		ph_eat(ctrl);
		ph_sleep(ctrl);
		print_action(ctrl, THINK);
	}
	pthread_join(ctrl->watcher2, NULL);
	pthread_join(ctrl->watcher, NULL);
	sem_post(ctrl->all_sated);
	sem_post(ctrl->print_sem);
	free_ctrl(ctrl);
	exit(EXIT_SUCCESS);
}
