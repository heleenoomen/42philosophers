/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/10 18:53:25 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* to avoid double indirection and access philo->ctrl->death faster, a boolean
 * is set check if death occurred at the table.
 * Then, the philosopher waits until controller sets 'run' to true (after all
 * threads are created). Philo's acquire the time of their last meal, which at
 * the start of the simulation is equal to the start time. After having
 * acquiered this parameter, philo sets their free parameter to true and enters
 * the simulation whileloop until death occurs at the table. During simulation,
 * the philosopher takes forks, eats, sleeps and thinkss. In between, death is
 * checked for, philo->free is set to false (after taking forks, i.e. at the
 * start of the meal) and again to free (after waking up from sleeping).
 */
void	run_philosophers(t_philo *philo)
{
	philo->last_meal = philo->ctrl->start;
	if (philo->nbr % 2)
		ph_usleep(philo, philo->ctrl->time_eat);
	while ((death(philo->ctrl, CHECK) == false))
	{
		ph_eat(philo);
		ph_sleep(philo);
		print_action(philo, THINK, gettime());
	}
}

void	run_one_philosopher(t_philo *philo)
{
	philo->last_meal = philo->ctrl->start;
	pthread_mutex_lock(&(philo->left->mutex));
	print_action(philo, FORK, gettime());
	while (death(philo->ctrl, CHECK) == false);
}

/* when the simulation is over, the main thread waits for the other threads to 
 * return befor exiting the program. pthread_join waits for threads to join (=
 * for them to return from their routine)
 */
void	join_threads(t_ctrl *ctrl, int nu_created)
{
	int	i;

	i = 0;
	while (i++ < nu_created)
		pthread_join(ctrl->threads[i], NULL);
}


/* Controller initiates a thread for each philosopher and sends her of to her 
 * routine, with their entry in the philos array of structs as a parameter.
 * If thread creation fails, controller sets death to true so that any threads 
 * created so far will return from the routine immediately. After creating 
 * threads, controller calls watcher to start the simulation, oversee simulation 
 * and stop it as soon as a philosopher dies or max_meals is reached for all 
 * philosophers. Controller then goes to join_threads, to wait for all threads to 
 * return from their routine.
 */
void	init_threads(t_ctrl *ctrl, t_err *error)
{
	int		i;
	void	(*routine)(t_philo *);

	if (nu_philo == 1)
		routine = &run_one_philosopher;
	else
		routine = &run_philosophers;
	i = 0;
	ctrl->start = gettime();
	while (i < nu_philo)
	{
		if (pthread_create(ctrl->threads + i, NULL, (void *)routine, ctrl->philos + i))
		{
			*error = THREAD_ERR;
			death(ctrl, SET);
			break ;
		}
		i++;
	}
	watcher(ctrl, i);
	join_threads(ctrl, i);
}


