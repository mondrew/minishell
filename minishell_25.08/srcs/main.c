/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:22:07 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/05 22:11:39 by mondrew          ###   ########.fr       */
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

int		launch_commands(char *line, char ***envp) // mkdir cd --- ???
{
	t_cmd	**cmds; // Why pointer to pointer? May be t_cmd *cmds is enough? (mondrew)
	int		i;
	int		status;
	int		j; // new

	// pid_t	pid1;
	// pid_t	pid2;
	// int		pipefd[2];

	i = 0;
	status = 0;
	if (!(cmds = parse_cmd(line))) // возвращает массив команд на исполнение
		return (-1); // выставить ошибку! Не (-1), а недостаточно памяти! Шелл продолжает работать

// TEST
	// Print commands
	int t = 0;
	while (cmds[t]->cmd != END)
	{
		printf("[%d] %s <%d>\n", cmds[t]->cmd, cmds[t]->str, cmds[t]->status);
		t++;
	}
	// END TEST
	while (cmds && ((cmds[i])->cmd != END))
    {
        if ((j = ft_execute(&(cmds[i]), envp)) == -1) // Тут я отправляю указатель не на начало cmds, поэтому освобождать cmds нужно тут!!!
            return (-1);
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
		result = launch_commands(line, &envp);
		if (line)
			free(line);
		if (result == -1)
			is_exit = 1; // это тут не нужно, т.к. если будет exit  - и так выйдет. Использовать для кода возврата
	}
	return (0);
}

// CTRL + D -- works bad - infinite loop - FIX IT
int main(int argc, char **argv, char **envp)
{
	return (minishell(envp));
}
