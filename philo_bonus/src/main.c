/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 11:41:07 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* print help_message and exit program when user enters wrong number of 
 * parameters
 */
int	exit_help_message(void)
{
	printf("%s\n", USAGE);
	exit (EXIT_USER_ERROR);
}

/* check if argc is correct, initialize error to NULL, initialize ctrl struct,
 * start simulation and exit program
 */
int	main(int argc, char **argv)
{
	t_ctrl	*ctrl;
	t_err	error;

	if (argc < 5 || argc > 6)
		exit_help_message();
	error = NULL;
	ctrl = init_ctrl(argc, argv, &error);
	if (error)
		exit_program(ctrl, &error);
	start_simulation(ctrl, &error);
	exit_program(ctrl, &error);
}
