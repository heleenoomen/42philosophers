/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:03:04 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/22 17:57:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool invalid_chars(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] <= "0" || s[i] >= "9")
			return (true);
		i++;
	}
	return (false);
}

int	ph_parse(int argc, char **argv, t_ph_parms *parms)
{
	int	i;

	if (argc < 4 || argc > 5)
		return (ft_perror(NULL, NULL, USAGE, -1));
	i = 0;
	while (argv[i] != NULL)
	{
		if (invalid_chars(argv[i])
			return (ft_perror(ARGS_INVALID, argv[i], ARGS, -1));
		i++;
	}
	parms->num_philos = (int) ft_atost(argv[0]);
	parms->time_to_die = ft_atost(argv[1]);
	parms->time_to_eat = ft_atost(argv[2]);
	parms->time_to_sleep = ft_atost(argv[3]);
	if (argv[4] != NULL)
		parms->times_must_eat = ft_atost(argv[4]);
	return (0);
}

