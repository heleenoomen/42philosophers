/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/03 19:10:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include "message.h"

/* represent time in milliseconds */
typedef unsigned int	t_ms;

typedef char			*t_err;

typedef struct s_ctrl
{
	int				nu_philo;
	t_ms			time_eat;
	t_ms			time_sleep;
	t_ms			time_die;
	int				max_meals;
	t_ms			start;
	bool			death;
	pthread_t		*threads;
	ptread_mutex_t	*forks;
	struct s_philo	*philos;
}

typedef struct s_philo;
{
	t_ms			last_action;
	t_ms			last_meal;
	t_ctrl			*controller;
}					t_philo;

#endif

