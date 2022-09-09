/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/09 11:42:57 by hoomen           ###   ########.fr       */
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
	bool		*death;

	death = &(philo->controller->death);
	while ((philo->controller->run) == false);
	philo->last_meal = philo->controller->start;
	philo->last_action = philo->controller->start;
	philo->free = true;
	while (!(*death))
	{
		take_forks(philo);
		philo->free = false;
		eat(philo);
		if (philo->meals == philo->controller->max_meals)
			philo->sated = true;
		if (*death)
			return ;	
		philo_sleep(philo);
		philo->free = true;
		if (*death)
			return ;
		think(philo);
	}
}

void	run_one_philosopher(t_philo *philo)
{
	while ((philo->controller->run) == false);	
	philo->last_meal = philo->controller->start;
	philo->free = true;
	pthread_mutex_lock(&(philo->one->mutex));
	print_action(philo, FORK, gettime());
	while (!(philo->controller->death));
	pthread_mutex_unlock(&(philo->one->mutex));
}

/* when the simulation is over, the main thread waits for the other threads to 
 * return befor exiting the program. pthread_join waits for threads to join (=
 * for them to return from their routine)
 */
void	join_threads(t_ctrl *ctrl)
{
	int	i;
	int	nu_philo;

	nu_philo = ctrl->nu_philo;
	i = 0;
	while (i++ < nu_philo)
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
	int		nu_philo;
	void	(*routine)(t_philo *);

	nu_philo = ctrl->nu_philo;
	if (nu_philo == 1)
		routine = &run_one_philosopher;
	else
		routine = &run_philosophers;
	i = 0;
	while (i < nu_philo)
	{
		if (pthread_create(ctrl->threads + i, NULL, (void *)routine, ctrl->philos + i))
		{
			*error = THREAD_ERR;
			ctrl->death = true;
			break ;
		}
		i++;
	}
	watcher(ctrl);
	join_threads(ctrl);
}


