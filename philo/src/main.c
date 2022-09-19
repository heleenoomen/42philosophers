/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/19 18:27:27 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark M */

int	help_message(void)
{
	printf("%s\n", USAGE);
	return (1);
}

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

