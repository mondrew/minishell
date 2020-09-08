/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:22:07 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 18:36:29 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*read_line(void)
{
	char	*line;
	int		res;

	res = 0;
	while ((res = get_next_line(0, &line)) == 0)
		continue;
	return (line);
}

void		print_prompt(void)
{
	ft_putstr("\x1b[1;4;32m");
	ft_putstr("minishell:");
	ft_putstr("\x1b[0m");
	ft_putstr("\x1b[1;36m");
	ft_putstr(get_cur_path());
	ft_putstr("$ ");
	ft_putstr("\x1b[0m");
}

int			minishell(char **envp)
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
		signal(SIGINT, sigint());
		signal(SIGQUIT, signotactive());
		line = read_line();
		signal(SIGINT, sigintexec());
		signal(SIGQUIT, sigquit());
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
	return (minishell(envp));
}
