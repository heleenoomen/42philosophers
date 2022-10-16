/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:56:52 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 10:26:24 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

/* messages at exit of program */
# define PHILO "philo:"
# define MALLOC_ERR "System error: Failed to allocate memory."
# define THREAD_ERR "System error: Failed to create thread."
# define THREAD_ERR_CHILD "System error Failed to create thread in child \
process. Aborting."
# define SEM_ERR "System error: Failed to open semaphores."
# define FORK_ERR "System error: Failed to create child process."
# define UNDEF_CHILD_PROC "Abort: Undefined error in child process"
# define ARGS "Error: Invalid arguments."
# define USAGE "Usage: ./philo <nbr_of_philosophers> <time\
_to_die> <time_to_eat> <time_to_sleep> [max meals]"
# define INV_TIME "Error: Please provide time in whole milliseconds."
# define INV_PH "Error: Please provide a valid number of philosophers (max 200)\
."
# define INV_ME "Error: Please provide a valid number of meals; alternatively, \
leave this parameter out."
# define NO_PH "Error: Number of philosophers is 0. No simulation is possible."
# define START_SATED "Max meals is 0: No simulation was started: Philosophers \
were already sated.\nPlease enter a number bigger than 0 or leave this parameter out \
altogether to start a simulation"

/* messages for program logs */
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

#endif
