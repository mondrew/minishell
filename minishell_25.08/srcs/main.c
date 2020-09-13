/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:22:07 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/13 16:45:32 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line(void)
{
	char	*line;
	int		res;

	res = 0;
	while ((res = get_next_line(0, &line)) == 0)
		continue;
	if (res == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

void		print_prompt(void)
{
	char *str;

	str = get_cur_path();
	ft_putstr("\x1b[1;4;32m");
	ft_putstr("minishell:");
	ft_putstr("\x1b[0m");
	ft_putstr("\x1b[1;36m");
	ft_putstr(str);
	ft_putstr("$ ");
	ft_putstr("\x1b[0m");
	if (str)
		free(str);
}

static int	minishell(char **envp)
{
	char	*line;
	int		is_exit;
	int		result;
	int		exit_code;

	is_exit = 0;
	exit_code = 0;
	while (!is_exit)
	{
		print_prompt();
		signal(SIGINT, sigint);
		signal(SIGQUIT, signotactive);
		if (!(line = read_line()))
			return (1);
		signal(SIGINT, sigintexec);
		signal(SIGQUIT, sigquit);
		result = launch_commands(line, &envp, &exit_code);
		if (line)
			free(line);
		if (result == -1)
			is_exit = 1;
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	return (minishell(envp));
}
