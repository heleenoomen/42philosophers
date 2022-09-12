/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/12 19:01:25 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark M */

int	help_message(void)
{
	printf("%s %s\n%s\n", ERR, ARGS, USAGE);
	return (1);
}

int	main(int argc, char **argv)
{
	t_ctrl	*ctrl;
	t_err	error;
	sem_t	**semaphores;

	if (argc < 5 || argc > 6)
		return (help_message());
	error = NULL;
	ctrl = init_controller(argc, argv, &error);
	semaphores = init_semaphores(ctrl, error);
	if (error)
		return (exit_program(controller, &error));
	simulation(ctrl, error);
	return (exit_program(controller, &error));
}

