# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjessica <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/10 02:15:42 by mondrew           #+#    #+#              #
#    Updated: 2020/09/12 16:42:10 by gjessica         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = 	./srcs/*.c

INCLUDES = ./includes

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

# %.o: %.c
# 	@gcc $(FLAGS) $(SRCS) -I$(INCLUDES) -c $< -o $@
# 	@echo "Compiling... Please wait..."

all: $(NAME)

$(NAME): $(SRCS)
	@echo "Compiling ... Please wait..."
	@gcc $(FLAGS) $(SRCS) -I $(INCLUDES) -o $(NAME)
	@echo "Compilation successfully done!"
# $(NAME): $(OBJS)
# 	@echo "Compiling ... Please wait..."
# 	@gcc $(OBJS) -o $(NAME)
# 	@echo "Compilation successfully done!"

clean:
	@echo "Cleaning object files ..."
	@/bin/rm -f $(OBJS)
	@echo "Object files has been removed!"

fclean: clean
	@echo "Cleaning all ..."
	@/bin/rm -f $(NAME)
	@echo "Everything has been removed!"

re: fclean all
