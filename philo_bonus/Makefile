# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 11:21:41 by mlongo            #+#    #+#              #
#    Updated: 2023/06/19 16:05:05 by mlongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus

OBJS := Philosophers_bonus.o Processes_bonus.o utils_bonus.o ft_atoi_bonus.o ft_itoa_bonus.o actions_bonus.o

FLAGS := -Wall -Werror -Wextra -g -pthread

#COLORS
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

DEFAULT = \033[0m

all: $(NAME)

%.o : %.c
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME) -fsanitize=address
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@rm -f $(OBJS)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: clean fclean all
