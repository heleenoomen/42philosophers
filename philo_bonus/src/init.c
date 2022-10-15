/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 00:12:12 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* initializes a semaphore with a given name and value. Unlinks first. Sets
 * error if the semaphore was not created successfully
 */
sem_t	*init_semaphore(char *name, int value, t_err *error)
{
	sem_t	*ret;

	sem_unlink(name);
	ret = sem_open(name, O_CREAT | O_EXCL, 0664, value);
	if (ret == SEM_FAILED)
	{
		*error = SEM_ERR;
		perror(name);
	}
	return (ret);
}

/* initialize all semaphores in the control struct. Semaphores are
 * initialized with a value of one (only one thread can get or set the protected
 * info at a time, only one thread can print at a time). The forks semaphore
 * is initialized with the number of philosophers (representing the amount of
 * forks on the table)
 */
void	init_all_semaphores(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		return ;
	ctrl->forks = init_semaphore("/forks", ctrl->nu_philo, error);
	ctrl->print_sem = init_semaphore("/print_sem", 1, error);
	ctrl->last_meal_sem = init_semaphore("/last_meal_sem", 1, error);
	ctrl->sated = init_semaphore("/sated", 0, error);
	ctrl->stop_all = init_semaphore("/stop_all", 0, error);
}

/* convert the parameters in the argument vector to integers calling
 * ph_atoui. Set error in case invalid parameters where entered, in case
 * number of philosophers in zero (no simulation possible) or max_mealse
 * is zero (no simulation needed, all philophers are already sated)
 */
void	fill_in_params(int argc, char **argv, t_ctrl *ctrl, t_err *error)
{
	ctrl->nu_philo = ph_atuoi(argv[1], error, N_PH);
	ctrl->time_die = ph_atuoi(argv[2], error, TIME);
	ctrl->time_eat = ph_atuoi(argv[3], error, TIME);
	ctrl->time_sleep = ph_atuoi(argv[4], error, TIME);
	if (argc == 6)
		ctrl->max_meals = ph_atuoi(argv[5], error, N_MEALS);
	else
		ctrl->max_meals = -1;
	if (*error == NULL && ctrl->nu_philo == 0)
		*error = NO_PH;
	if (*error == NULL && ctrl->max_meals == 0)
		*error = START_SATED;
}

/* initialize all flags and counters in the ctrl struct. Status is set
 * to EATING so that the philosopher cannot die before the simulation
 * starts.
 */
void	set_flags_and_counters(t_ctrl *ctrl)
{
	ctrl->status = EATING;
	ctrl->meals = 0;
}

/* initialize control struct. Allocate memory (malloc_set_err) for ctrl struct,
 * fill in the user parameters, initialize all semaphores and set flags and
 * counters. Return a pointer to the dynamically allocated ctrl struct
 */
t_ctrl	*init_ctrl(int argc, char **argv, t_err *error)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *) malloc_set_err(sizeof(t_ctrl), error);
	if (*error)
		return (NULL);
	fill_in_params(argc, argv, ctrl, error);
	ctrl->cpids = malloc_set_err(sizeof(int) * ctrl->nu_philo, error);
	if (!*error)
		init_all_semaphores(ctrl, error);
	if (!*error)
		set_flags_and_counters(ctrl);
	return (ctrl);
}
