# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 15:35:03 by hoomen            #+#    #+#              #
#    Updated: 2022/10/13 19:58:55 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH		= src
INCFLAGS	= -I include

CC			= cc
FLAGS		= -Wall -Werror -Wextra -fsanitize=thread

NAME		= philo
HEADER		= include/philo.h
SRC			= actions.c get.c exit_program.c init_structs.c main.c\
			  set.c simulation.c time.c utils.c watcher.c
OBJ			= $(addprefix obj/,$(notdir $(SRC:.c=.o)))

$(NAME) : $(OBJ) 
	@$(CC) $(FLAGS) -o $@ $^ -pthread
	@echo "\033[32;1mphilo is compiled!"

obj/%.o : %.c $(HEADER) | obj
	@$(CC) $(FLAGS) $(INCFLAGS) -c $< -o $@

obj :
	@echo "\033[32;1m\tphilo is compiling..."
	@mkdir obj

all : $(NAME)

clean :
	@rm -rf obj
	@echo "\033[0;33mobject files of philo were removed."

fclean : clean
	@rm -f $(NAME)
	@echo "\033[0;31mphilo was deleted."

start : go make_name

re : fclean all

.PHONY : all clean fclean re bonus
