/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 13:38:05 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* mark M */

int	help_message(void)
{
	printf("%s\n", USAGE);
	return (1);
}

int	main(int argc, char **argv)
{
	t_ctrl	*ctrl;
	t_err	error;

	if (argc < 5 || argc > 6)
		return (help_message());
	error = NULL;
	ctrl = init_ctrl(argc, argv, &error);
	if (error)
		return (exit_program(ctrl, &error));
	start_simulation(ctrl, &error);
	return (exit_program(ctrl, &error));
}
