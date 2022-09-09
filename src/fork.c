/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:44:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/09 15:11:50 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* initializes the mutex in the fork struct. Sets init to true when
 * initialization was succesful, and returns true. Sets error, sets init to
 * false and returns false when initialization of the mutex failed.
 */
bool	init_fork(t_fork *fork, t_err *error)
{
	if (pthread_mutex_init(&(fork->mutex), NULL))
	{
		*error = MUTEX_ERR;
		fork->init = false;
		return (false);
	}
	fork->init = true;
	return (true);	
}

/* once the forks array in the ctrl struct is succesfully allocated, the forks
 * are initialized one by one by calling init_fork. If a fork is not initialized
 * succesfully (init_fork returns false), error is set and we return. When all
 * forks in forks array are initialized, the print_lock mutex is initialized.
 */
void	init_forks(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_forks;

	if (*error)
		return ;
	i = 0;
	nu_forks = ctrl->nu_philo;
	while (i < nu_forks)
	{
		if (init_fork(ctrl->forks + i, error) == false)	
			return ;
		ctrl->forks[i].init = true;
		i++;
	}
	if (init_fork(&(ctrl->print_lock), error))
		return ;
}

/* every philosopher has a fork left of them, which is the entry in the forks
 * array with the index of the philosopher's number minus one. Each has a fork
 * to their right, which is the entry in the forks array with their own index.
 * (So, philosopher one has their left fork at ctrl->forks[0] and their right
 * fork at ctrl->forks[1]. Philosopher N has their left fork at ctrl->forks[n -
 * 1] and their right fork at ctrl->forks[0].
 * Philosophers with uneven numbers take their left fork first and then their
 * right fork, philosophers with even numbers take their right fork first and
 * then their left fork. With this strategy, deadlocks are avoided.
 */
void	get_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = (philo->nbr - 1) % philo->controller->nu_philo;
	right = philo->nbr % philo->controller->nu_philo;
	if (philo->controller->nu_philo == 1)
		philo->left = philo->controller->forks;
	else if (philo->nbr % 2)
	{
		philo->left = philo->controller->forks + left;
		philo->right = philo->controller->forks + right;
	}
	else
	{
		philo->left = philo->controller->forks + right;
		philo->right = philo->controller->forks + left;
	}
}

