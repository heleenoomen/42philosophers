/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:56:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/22 19:04:46 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_perror(char *s, char *s2, char *s3, int ret)
{
	if (s3 != NULL)
	{
		ft_putstr_fd(s3, 2);
		ft_putstr_fd(": ", 2);
	if (s2 != NULL)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(s, 2);
	write(2, "\n", 1);
	return (ret);
}

int	ph_free_return(pthread_t *philos, pthread_mutex_t *forks, t_ph_philo *philo_structs, int ret)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = philo_structs[0]->parms->num_philos;
	while (i < num_philos)
	{
		pthread_mutex_unlock(forks + i);
		pthread_mutex_destroy(forks + i);
		forks[i] = NULL;
		i++;
	}

