/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:56:52 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 19:21:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

/* error messages */
# define PHILO "philo:"
# define MALLOC_ERR "System error: Failed at allocating memory."
# define THREAD_ERR "System error: Failed at creating thread."
# define MUTEX_ERR "System error: Failed at initializing mutex."
# define USAGE "\033[32;1mUsage: ./philo <nbr_of_philosophers> <time\
_to_die> <time_to_eat> <time_to_sleep> [max meals]\n\
\033[0;m<nbr_of_philosophers>\tthe number of philosophers at the table\n\
<time_to_die>\t\tthe maximum amount of time (in ms) a philosopher can spend\
 without eating\n\
<time_to_eat>\t\tthe time (in ms) a philosopher needs to finish her meal\n\
<time_to_sleep>\t\tthe time (in ms) a philosopher spends sleeping\n\
[max meals]\t\tthe number of times each philosopher must eat (this parameter\
 is optional)"
# define INV_TIME "Error: Please provide time in whole milliseconds."
# define INV_PH "Error: Please provide a valid number of philosophers (max 200)\
."
# define INV_ME "Error: Please provide a valid number of meals; alternatively, \
leave this parameter out."
# define NO_PH "Error: Number of philosophers is 0. No simulation is possible."
# define START_SATED "Max meals is zero. No simulation was started, because the \
philosophers were already sated.\nPlease enter a number bigger than 0 or leave \
this parameter out altogether to start a simulation."

/* colors */
# define GREEN_BOLD "\033[32;1m"
# define RED_BOLD
# define YELLOW_BOLD "\033[33;1m"
# define CYAN_BOLD "\033[36;1m"
# define PURPLE_BOLD "\033[35;1m"
# define BLUE_BOLD "\033[34;1m"
# define DEFAULT_BOLD "\033[0;1m"
# define RESET_COLOR "\033[0;m"

/* log messages */
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

/* alternative log messages: colors and emoji's, slows program down slightly*/
//# define FORK "\033[36;1mhas taken a fork\033[0m \U0001F374"
// # define EAT "\033[33;1mis eating\033[0m \U0001F35D"
// # define SLEEP "\033[35;1mis sleeping\033[0m \U0001F4A4"
// # define THINK "\033[32;1mis thinking\033[0m \U0001F4AD"
// # define DIE "\033[31;1mdied\033[0m \U0001FAA6"

#endif
