/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:29:11 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 11:14:22 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* check continuously if the main thread (the philosopher) has spend too much
 * time without eating. If she is not in a protected state (i.e. her status is
 * not EATING, but some OTHER activity), watcher prints a death message, blocks
 * further access to stdout and posts on stop_all semaphore to wake up ripper,
 * which will then terminate all child processes.
 *)
 */
void	watcher(t_ctrl *ctrl)
{
	t_ms	last_meal;

	while (1)
	{
		last_meal = get_time_last_meal(ctrl);
		if (((current_time() - last_meal) > ctrl->time_die))
		{
			sem_wait(ctrl->print_sem);
				printf("%u %i died\n", current_time() - ctrl->start, \
				ctrl->index);
			sem_post(ctrl->stop_all);
			sem_post(ctrl->stop_all);
			return ;
		}
	}
}

/* create two watcher threads. In case of failure, post on semaphores
 * and join any existing threads, free up resoursec and exit with a
 * status that indicates thread error to parent process
 */
void	create_watcher_thread(t_ctrl *ctrl)
{
	if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, \
	(void *)ctrl))
	{
		sem_wait(ctrl->print_sem);
		printf("%s %s\n", PHILO, THREAD_ERR_CHILD);
		sem_post(ctrl->stop_all);
	}
}

/* philosophers create their watcher threads and detach it, so that
 * the thread will clean up its own resources once the process receives the
 * SIGTERM signal from ripper.
 * set their status to OTHER, meaning that form now on, they may die when
 * not eating. Uneven philos sleep for almost time_eat to avoid deadlock and
 * give them all a fair chance at grabbing forks. Philos enter in a while loop
 * and will carry out their routine (eat, sleep, think) until the ripper in the
 * main process sends it SIGTERM signal.
 */
void	run_philosophers(t_ctrl *ctrl)
{
	create_watcher_thread(ctrl);
	pthread_detach(ctrl->watcher);
	set_status(ctrl, 0);
	if (ctrl->index % 2)
		ph_usleep(ctrl, ctrl->time_eat - 10);
	while (1)
	{
		ph_eat(ctrl);
		ph_sleep(ctrl);
		print_action(ctrl, THINK);
	}
}
