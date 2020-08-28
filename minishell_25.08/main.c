/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:22:07 by gjessica          #+#    #+#             */
/*   Updated: 2020/08/26 13:01:26 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_line()
{
	char *line;

	get_next_line(1, &line);
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

// JUST TEST GIT PULL

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
	cmds = parse_cmd(line); // возвращает массив команд на исполнение

	while (cmds && (cmds[i])->cmd != END)
    {
        if ((i = ft_execute(cmds, envp)) == -1)
            return (-1);
    }
    while (cmds[i]->cmd != END)
    {
        ft_free_cmd_elem(cmds[i]);
        i++;
    }
    free(cmds[i]);
    free(cmds);
    return (0);
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
