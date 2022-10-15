/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 21:49:03 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* initializes the mutex in the fork struct. Sets init to true when
 * initialization was succesful, and returns true. Sets error, sets init to
 * false and returns false when initialization of the mutex failed.
 */
bool	init_mutex(t_mutex *fork, t_err *error)
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
 * are initialized one by one by calling init_mutex. If a fork is not initialized
 * succesfully (init_mutex returns false), error is set and we return. When all
 * forks in forks array are initialized, the print_lock mutex is initialized.
 */
void	init_mutexes_ctrl_struct(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_forks;

	i = -1;
	nu_forks = ctrl->nu_philo;
	while (++i < nu_forks)
		init_mutex(ctrl->forks + i, error);
	init_mutex(&(ctrl->lock_print), error);
	init_mutex(&(ctrl->lock_death), error);
	init_mutex(&(ctrl->lock_sated), error);
	init_mutex(&(ctrl->lock_start), error);
}

/* give each entry in the ctrl->philos array their parameters and initialize
 * their mutexes. 'status' is set to EATING to prevent watcher from declaring
 * the philosopher death before the simulations is started
 */
void	init_philos(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_philo;

	nu_philo = ctrl->nu_philo;
	i = -1;
	while (++i < nu_philo)
	{
		ctrl->philos[i].nbr = i + 1;
		ctrl->philos[i].meals = 0;
		ctrl->philos[i].status = EATING;
		ctrl->philos[i].left = ctrl->forks + ((i) % nu_philo);
		ctrl->philos[i].right = ctrl->forks + ((i + 1) % nu_philo);
		init_mutex(&(ctrl->philos[i].lock_meal), error);
		init_mutex(&(ctrl->philos[i].lock_status), error);
		ctrl->philos[i].ctrl = ctrl;
	}
}

/* calls ph_atoui to convert user parameters to integers. Error will be set by
 * ph_atoui in case of invalid parameters. If the number of philosophers is 0
 * or max_meals is 0, an error code is also set, since it means no simulation
 * is possible (zero philosophers) or no simulation is needed (all philosophers
 * are already sated after zero meals)
 */
void	fill_in_parameters(int argc, char **argv, t_ctrl *ctrl, t_err *error)
{
	ctrl->nu_philo = ph_atoui(argv[1], error, N_PH);
	ctrl->time_die = ph_atoui(argv[2], error, TIME);
	ctrl->time_eat = ph_atoui(argv[3], error, TIME);
	ctrl->time_sleep = ph_atoui(argv[4], error, TIME);
	if (argc == 6)
		ctrl->max_meals = ph_atoui(argv[5], error, N_MEALS);
	else
		ctrl->max_meals = -1;
	if (*error == NULL && ctrl->nu_philo == 0)
		*error = NO_PH;
	if (*error == NULL && ctrl->max_meals == 0)
		*error = START_SATED;
}

/* allocates space for ctrl struct, parses user parameters, allocates
 * space for arrays of threads, mutexes and philos. Initialize mutexes
 * and initializes the philos array. Sets death flag to false.
 * Returns a pointer to the control struct. Sets error in case any
 * system error occurs (malloc, failed to create thread or mutex)
 */
t_ctrl	*init_controller(int argc, char **argv, t_err *error)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *) malloc_set_err(sizeof(t_ctrl), error);
	if (*error)
		return (NULL);
	fill_in_parameters(argc, argv, ctrl, error);
	if (*error)
		return (ctrl);
	ctrl->threads = malloc_set_err(ctrl->nu_philo * sizeof(pthread_t), error);
	ctrl->forks = malloc_set_err(ctrl->nu_philo * sizeof(t_mutex), error);
	ctrl->philos = malloc_set_err(ctrl->nu_philo * sizeof(t_philo), error);
	if (*error)
		return (ctrl);
	init_mutexes_ctrl_struct(ctrl, error);
	init_philos(ctrl, error);
	ctrl->death = false;
	ctrl->nu_sated = 0;
	return (ctrl);
}
