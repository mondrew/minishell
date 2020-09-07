/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:22:07 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/07 22:31:22 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_line()
{
	char *line;
	int res;

	res = 0;
	while ((res  = get_next_line(0, &line)) == 0)
		continue;
	return (line);
}

void print_prompt()
{
	ft_putstr("\x1b[1;4;32m");
	ft_putstr("minishell:");
	ft_putstr("\x1b[0m");
	ft_putstr("\x1b[1;36m");
	ft_putstr(get_cur_path());
	ft_putstr("$ "); // приглашение - это знак доллара (из книги Танненбаума)
	ft_putstr("\x1b[0m");
}

void	ft_set_exit_code(t_cmd **cmds, int exit_code)
{
	int		i;

	i = 0;
	while (cmds && cmds[i]->cmd != END)
		i++;
	cmds[i]->status = exit_code;
}

int		ft_get_exit_code(t_cmd **cmds)
{
	int		i;

	i = 0;
	while (cmds && cmds[i]->cmd != END)
		i++;
	return (cmds[i]->status);
}

int		launch_commands(char *line, char ***envp, int *exit_code) // mkdir cd --- ???
{
	t_cmd	**cmds; // Why pointer to pointer? May be t_cmd *cmds is enough? (mondrew)
	int		i;
	int		status;
	int		j; // new

	i = 0;
	status = 0;
	if (!(cmds = parse_cmd(line))) // возвращает массив команд на исполнение
		return (*exit_code = 1);
	ft_set_exit_code(cmds, *exit_code);
// TEST
	// int	t;

	// t = 0;
	// while (cmds[t]->cmd != END)
	// {
	// 	printf("[%d] %s <%d>\n", cmds[t]->cmd, cmds[t]->str, cmds[t]->status);
	// 	t++;
	// }
//
	while (cmds && ((cmds[i])->cmd != END))
    {
        if ((j = ft_execute(&(cmds[i]), envp)) == -1) // Тут я отправляю указатель не на начало cmds, поэтому освобождать cmds нужно тут!!!
        {
			*exit_code = ft_get_exit_code(cmds); // делаю в ft_execute
			ft_free_cmds(cmds); // added 06/09
			return (-1);
		}
		*exit_code = ft_get_exit_code(cmds);
		i += j;
    }
	// освобождаю все. Но может и не так нужно!!!
	i = 0; // new // ошибка была в этом!!! Я освобождал executed cmds[i] в ft_execute
    while (cmds[i]->cmd != END)
    {
        ft_free_cmd_elem(cmds[i]);
        i++;
    }
	//printf("i: %d\n", i); // test
    free(cmds[i]);
    free(cmds);
	//printf("End of launch_commands\n"); // test
    return (*exit_code);
}

void	sigint()
{
	ft_putstr("\n");
	print_prompt();
}

void	sigquit()
{
	ft_putstr("minishell: quit (core dumped)\n");
}

void	signotactive()
{
	return ;
}

void	sigintexec()
{
	ft_putstr("\n");
}

int		minishell(char **envp)
{
	char	*line;
	int 	is_exit;
	int 	result;
	int		exit_code;

	is_exit = 0;
	exit_code = 0;

	while (!is_exit)
	{
		print_prompt();
		signal(SIGINT, sigint);
		signal(SIGQUIT, signotactive);
		line = read_line();
		signal(SIGINT, sigintexec);
		signal(SIGQUIT, sigquit);
		result = launch_commands(line, &envp, &exit_code);
		if (line)
			free(line);
		if (result == -1)
			is_exit = 1; // это тут не нужно, т.к. если будет exit  - и так выйдет. Использовать для кода возврата
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	return (minishell(envp));
}
