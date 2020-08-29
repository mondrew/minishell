/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:22:07 by gjessica          #+#    #+#             */
/*   Updated: 2020/08/28 13:27:07 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_line()
{
	char *line;

	get_next_line(0, &line);
	return (line);
}

void print_pre_command()
{
	ft_putstr("\x1b[1;4;32m");
	ft_putstr("minishell:");
	ft_putstr("\x1b[0m");
	ft_putstr("\x1b[1;36m");
	ft_putstr(get_cur_path());
	ft_putstr("$ "); // приглашение - это знак доллара (из книги Танненбаума)
	ft_putstr("\x1b[0m");
}

int launch_commands(char *line, char **envp) // mkdir cd --- ???
{
	t_cmd	**cmds; // Why pointer to pointer? May be t_cmd *cmds is enough? (mondrew)
	int		i;
	int		status;

	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];

	i = 0;
	status = 0;
	cmds = parse_cmd(line);

	// TEST
	// Print commands
	int t = 0;
	while (cmds[t])
	{
		printf("[%d] %s <%d>\n", cmds[t]->cmd, cmds[t]->str, cmds[t]->status);
		t++;
	}
	// END TEST


	// возвращает массив команд на исполнение
	// все что ниже надо переделывать (mondrew)
	// этот if нужно вынести в отдельную функцию, которая будет проверять -
	// - мы собираемся выполнить built-in программу или нет

	// все что ниже - это отдельная функция на проверку и запуск встроенных команд

	if (cmds) // version 24/08/2020 (mondrew)
	{
		while ((*cmds)->cmd != END)
		{
			if (!(cmds = ft_execute(cmds, envp)))
				return (0);
		}
	}
	ft_free_cmds(cmds);
	/*
	if (cmds)
	{
		while (cmds[i] && cmds[i]->cmd != END)
		{
			if (cmds[i]->cmd == PWD)
				start_pwd(cmds[i]->str); // complete
			else if (cmds[i]->cmd == UNKNOWN)
				start_unknown_cmd(cmds[i]->str, envp); // complete // not really
			else if (cmds[i]->cmd == ECHO)
				start_echo(cmds[i]->str, envp); // Add '' "" $ // done by mondrew - should be checked by gjessica!
			else if (cmds[i]->cmd == CD)
				start_cd(cmds[i]->str, envp);
			else if (cmds[i]->cmd == EXPORT)
				start_export(cmds[i]->str, envp);
			else if (cmds[i]->cmd == UNSET) // done by mondrew - should be checked by gjessica!
				start_unset(cmds[i]->str, &envp);
			else if (cmds[i]->cmd == ENV)// complete
				start_env(cmds[i]->str, envp);
			else if (cmds[i]->cmd == EXIT)// complete
				status = -1;
			free(cmds[i]->str);
			free(cmds[i]);
			i++;
			if (status == -1)
			{
				free(cmds);
				return (-1);
			}
		}
		free(cmds); // на стр 70 уже есть free, если он сработает, этот
					// уже не нужен. Может тут условие поставить, а
					// верхний cmds обнулить после free?
		cmds = NULL;
	}
	*/
	return(0);
}

int minishell(char **envp)
{
	char *line;
	int is_exit;
	int result;

	is_exit = 0;

	while (!is_exit)
	{
		print_pre_command();
		line = read_line();
		result = launch_commands(line, envp);
		if (line)
			free(line);
		if (result == -1)
			is_exit = 1;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	return (minishell(envp));
}
