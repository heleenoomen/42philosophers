/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/14 14:01:21 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* uneven philosophers wait for time_eat - 10 milliseconds to avoid deadlocks.
 * the, philosophers enter their routine of eat, sleep, think until they die.
 * if they die, they wait for the watcher thread to join, free their resources
 * and exit with exit status DEATH
 */
void	run_philosophers(t_ctrl *ctrl)
{
	set_status(ctrl, OTHER);
	if (ctrl->index % 2)
		ph_usleep_sleep(ctrl);
	while (check_died(ctrl) == false)
	{
		ph_eat(ctrl);
		ph_sleep(ctrl);
		print_action(ctrl, THINK);
	}
	//pthread_join(ctrl->watcher, NULL);
	free_ctrl(ctrl);
	exit(DEATH);
}

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

	while (1)
	{
		last_meal = time_last_meal(ctrl);
		if (check_status(ctrl) == OTHER && ((gettime() - last_meal)
				> ctrl->time_die))
		{
			set_died(ctrl);
			sem_wait(ctrl->print_sem);
			printf("%u %i died\n", gettime() - ctrl->start, ctrl->index);
			sem_post(ctrl->forks);
			sem_post(ctrl->forks);
			break ;
		}
		if (check_sated(ctrl))
			break ;
	}
}

/* calls fork to create child process. When fork fails, sets error and calls
 * exit_program to directly exit the program in a clean way.
 * on success, returns the process id of the newly created child process
 * to the parent process and zero to the child process itself (return value
 * of fork())
 */
int	fork_handle_error(t_ctrl *ctrl, t_err *error)
{
	int	ret;

	ret = fork();
	if (ret == -1)
	{
		*error = FORK;
		exit_program(ctrl, error);
	}
	return (ret);
}

void	unlink_all_sempahores(void)
{
	sem_unlink()
}

/* sets the start time of the simulation, and sets last_meal and last_action to
 * start_time. generates a process for each philosopher, calling
 * fork_handle_error. Saves the process id's of the child processes in the cpids
 * array. In the child process, a watcher thread is created and the main thread
 * is send of to the run_philosophers array. In case thread creation fails, the
 * child process exits immediately. After creation of the threads, big_watcher
 * is called to oversee if child processes have exited (because of error, death
 * or saturation)
 */
void	start_simulation(t_ctrl *ctrl, t_err *error)
{
	int	i;

	i = -1;
	ctrl->start = gettime();
	ctrl->last_meal = ctrl->start;
	ctrl->start_current_action = ctrl->start;
	while (++i < ctrl->nu_philo)
	{
		ctrl->cpids[i] = fork_handle_error(ctrl, error);
		if (*error)
			exit_program(ctrl, error);
		if (ctrl->cpids[i] == 0)
		{
			ctrl->index = i + 1;
			if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, \
			(void *)ctrl))
			{
				sem_wait(ctrl->print_sem);
				free_ctrl(ctrl);
				exit(THREAD_ERR_CHILD);
			}
			pthread_detach(ctrl->watcher);
			run_philosophers(ctrl);
		}
	}
	detach_all_semaphores();
	big_watcher(ctrl, error);
}
