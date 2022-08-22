/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:34:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/22 20:09:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include "ph_userinfo.h"

typedef struct s_ph_parms
{
	int					num_philos;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
}						t_ph_parms;

typedef struct s_philo
{
	unsigned long int	time_die;
	unsigned long int	time_eat;
	unsigned long int	time_sleep;
	struct timeval		last_meal;	
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
}						t_philo;

#endif
