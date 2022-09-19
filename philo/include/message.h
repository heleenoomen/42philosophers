/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:56:52 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/19 18:39:48 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

/* mark E */

# define ERR "Error:"
# define MALLOC_ERR "Failed at allocating memory."
# define THREAD_ERR "Failed at creating thread."
# define MUTEX_ERR "Failed at initializing mutex."
# define ARGS "Invalid arguments."
# define USAGE "Usage: ./philo <nbr_of_philosophers> <time\
_to_die> <time_to_eat> <time_to_sleep> [max meals]\n\
<nbr_of_philosophers>\tthe number of philosophers at the table\n\
<time_to_die>\t\tthe maximum amount of time (in ms) a philosopher can spend\
 without eating\n\
<time_to_eat>\t\tthe time a philosopher needs to finish her meal\n\
<time_to_sleep>\t\tthe time a philosopher spends sleeping\n\
[max meals]\t\tthe number of times each philosopher must eat (this parameter\
 is optional)"
# define INV_TIME "Please provide time in whole milliseconds (max UINT_MAX,\n\
But please note that 3 million milliseconds is about 1 hour!)."
# define INV_PH "Please provide a valid number of philosophers (max 200)."
# define INV_ME "Number of meals invalid. Please provide a valid number (max INT_MAX);\n\
Hint: if you're not sure what INT_MAX is, just enter a not to big number.\n\
Alternatively, you can leave this parameter out altogether."
# define NO_PH "Number of philosophers is 0. No simulation is possible."

//# define FORK "\033[36;1mhas taken a fork\033[0m \U0001F374"
// # define EAT "\033[33;1mis eating\033[0m \U0001F35D"
// # define SLEEP "\033[35;1mis sleeping\033[0m \U0001F4A4"
// # define THINK "\033[32;1mis thinking\033[0m \U0001F4AD"
// # define DIE "\033[31;1mdied\033[0m \U0001FAA6"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

#endif

