/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:29:11 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 20:32:53 by hoomen           ###   ########.fr       */
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

	while (simulation(ctrl))
	{
		last_meal = time_last_meal(ctrl);
		if (check_status(ctrl) == OTHER && ((gettime() - last_meal)
				> ctrl->time_die))
		{
			sem_wait(ctrl->print_sem);
			if (simulation(ctrl))
				printf("%u %i died\n", gettime() - ctrl->start, ctrl->index);
			end_simulation(ctrl);
			sem_post(ctrl->forks);
			sem_post(ctrl->forks);
			sem_post(ctrl->forks);
			sem_post(ctrl->forks);
			sem_post(ctrl->stop_all);
			sem_post(ctrl->stop_all);
			return ;
		}
	}
}

/* merely wait until the stop_all semaphore is posted upon, in which case 
 * watcher2 set the simulation parameter to 'false' and posts itself twice
 * on the stop_all semaphore. This will cause all other watcher2 threads in
 * all other processes to do the same (in a domino effect), which will make
 * all threads throughout all processes return so that all child processes
 * can exit safely after joining them
 */
void	watcher2(void *parm)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *)parm;
	sem_wait(ctrl->stop_all);
	end_simulation(ctrl);
	sem_post(ctrl->stop_all);
	sem_post(ctrl->stop_all);
}

/* create two watcher threads. In case of failure, post on semaphores
 * and join any existing threads, free up resoursec and exit with a
 * status that indicates thread error to parent process
 */
void	create_watcher_threads(t_ctrl *ctrl)
{
	if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, \
	(void *)ctrl))
	{
		sem_post(ctrl->stop_all);
		sem_post(ctrl->stop_all);
		free_ctrl(ctrl);
		exit(THREAD_ERR_CHILD);
	}
	if (pthread_create(&(ctrl->watcher2), NULL, (void *) &watcher2, \
	(void *)ctrl))
	{
		sem_post(ctrl->all_sated);
		sem_post(ctrl->stop_all);
		sem_post(ctrl->stop_all);
		end_simulation(ctrl);
		pthread_join(ctrl->watcher, NULL);
		free_ctrl(ctrl);
		exit(THREAD_ERR_CHILD);
	}
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
	set_status(ctrl, OTHER);
	if (ctrl->index % 2)
		ph_usleep_check(ctrl, ctrl->time_eat - 10);
	while (simulation(ctrl))
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
