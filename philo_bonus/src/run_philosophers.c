/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:29:11 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 23:50:05 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* check continuously if the main thread (the philosopher) has spend too much
 * time without eating. If she is not in a protected state (i.e. her status is
 * not EATING, but some OTHER activity), watcher prints a death message, sets
 * simulation to false, posts twice on the forks semaphore to avoid any risk of
 * deadlock and posts on the stop_all semaphore to wake up all watcher2 threads
 * that will end all threads throughout all processes and make all child
 * processes return. Watcher holds the print_sem semaphore, to avoid
 * any other messages to be printed after death has occured.
 *)
 */
void	watcher(t_ctrl *ctrl)
{
	t_ms	last_meal;

	while (1)
	{
		last_meal = time_last_meal(ctrl);
		if (((gettime() - last_meal) > ctrl->time_die))
		{
			sem_wait(ctrl->print_sem);
				printf("%u %i died\n", gettime() - ctrl->start, ctrl->index);
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
void	create_watcher_threads(t_ctrl *ctrl)
{
	if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, \
	(void *)ctrl))
		sem_post(ctrl->stop_all);
}

/* philosophers create their watcher threads, set their status to OTHER
 * (i.e. not eating, they may die). Uneven philos sleep for almost 
 * time_eat to avoid deadlock and give them all a fair chance at
 * grabbing forks. Philos enter in a while loop until the simulation
 * parameter is set to 'false'. Philos join their watcher thread,
 * post on all_sated and print_sem semaphores to allow all other
 * threads and processes to return, free their resources and exit.
 */
void	run_philosophers(t_ctrl *ctrl)
{
	create_watcher_threads(ctrl);
	pthread_detach(ctrl->watcher);
	set_last_meal(ctrl, 0);
	if (ctrl->index % 2)
		ph_usleep_check(ctrl, ctrl->time_eat - 10);
	while (1)
	{
		ph_eat(ctrl);
		ph_sleep(ctrl);
		print_action(ctrl, THINK);
	}
}
