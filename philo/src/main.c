/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 16:55:33 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	help_message(void)
{
	printf("%s\n", USAGE);
	return (1);
}

/* check if number of arguments is correct, if not, return EXIT_FAILURE with
 * help message. Initialize error to NULL, initialize controller struct,
 * initialize threads to start simulation. Call exit_program to return cleanly
 * (using exit() is forbidden in the mandatory part of this project)
 */
int	main(int argc, char **argv)
{
	t_ctrl	*controller;
	t_err	error;

	if (argc < 5 || argc > 6)
		return (help_message());
	error = NULL;
	controller = init_controller(argc, argv, &error);
	if (error)
		return (exit_program(controller, &error));
	init_threads(controller, &error);
	return (exit_program(controller, &error));
}
