# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 11:21:41 by mlongo            #+#    #+#              #
#    Updated: 2023/06/14 16:55:42 by mlongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

NAME_BONUS := philo_bonus

OBJS := Philosophers.o threads.o utils.o ft_atoi.o actions.o

OBJS_BONUS :=

FLAGS := -Wall -Werror -Wextra -g -pthread

#COLORS
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

DEFAULT = \033[0m

all: $(NAME)

bonus: $(NAME_BONUS)

%.o : %.c
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME) -fsanitize=address
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

$(NAME_BONUS): $(OBJS_BONUS)
	@cc $(OBJS_BONUS) -o $(NAME_BONUS) -fsanitize=address
	@echo "$(GREEN)$(NAME_BONUS) created!$(DEFAULT)"

clean:
	@rm -f $(OBJS) ${OBJS_BONUS}
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: clean fclean all
