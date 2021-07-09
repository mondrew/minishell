NAME = minishell
SRCS = 	./srcs/check_cmd_status.c \
		./srcs/echo_utils.c \
		./srcs/echo_utils_one.c \
		./srcs/echo_utils_two.c \
		./srcs/echo_utils_three.c \
		./srcs/echo_utils_four.c \
		./srcs/echo_utils_five.c \
		./srcs/export_utils.c \
		./srcs/ft_add_or_replace.c \
		./srcs/ft_atoi.c \
		./srcs/ft_copy_array_no_free.c \
		./srcs/ft_cpyarr.c \
		./srcs/ft_execute.c \
		./srcs/ft_execute_one.c \
		./srcs/ft_execute_two.c \
		./srcs/ft_execute_three.c \
		./srcs/ft_execute_four.c \
		./srcs/ft_execute_five.c \
		./srcs/ft_execute_six.c \
		./srcs/ft_execute_seven.c \
		./srcs/ft_exit_code.c \
		./srcs/ft_free_envp_null_ids.c \
		./srcs/ft_goto_exit.c \
		./srcs/ft_itoa.c \
		./srcs/ft_launch.c \
		./srcs/ft_split.c \
		./srcs/ft_start_with.c \
		./srcs/ft_strcdup.c \
		./srcs/ft_strchr.c \
		./srcs/ft_strcmp.c \
		./srcs/ft_strdup.c \
		./srcs/ft_strjoin_free_left.c \
		./srcs/ft_strjoin.c \
		./srcs/ft_strlcpy.c \
		./srcs/ft_strlen.c \
		./srcs/ft_strncmp.c \
		./srcs/ft_strsdup.c \
		./srcs/ft_strswap.c \
		./srcs/ft_strtrim.c \
		./srcs/ft_substr.c \
		./srcs/get_next_line_utils.c \
		./srcs/get_next_line.c \
		./srcs/main.c \
		./srcs/parce_cmds.c \
		./srcs/parse_utils.c \
		./srcs/remove_key.c \
		./srcs/signals.c \
		./srcs/start_cd.c \
		./srcs/start_echo.c \
		./srcs/start_env.c \
		./srcs/start_export.c \
		./srcs/start_pwd.c \
		./srcs/start_unset.c \
		./srcs/utils.c

INCLUDES = ./includes

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

%.o: %.c
	@gcc $(FLAGS) -I$(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(OBJS) -o $(NAME)
	@echo "Compilation successfully done!"

clean:
	@echo "Cleaning object files ..."
	@/bin/rm -f $(OBJS)
	@echo "Object files has been removed!"

fclean: clean
	@echo "Cleaning all ..."
	@/bin/rm -f $(NAME)
	@echo "Everything has been removed!"

re: fclean all
