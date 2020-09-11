/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:03:20 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/12 01:05:36 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_simple_execute(t_cmd **cmds, char **envp)
{
	pid_t	pid;
	int		wstatus;

	if ((pid = fork()) < 0)
		return (ft_print_set_exit_code(FORKFAIL, cmds));
	if (pid == 0)
	{
		if (!ft_execve_cmd(cmds[0], cmds, envp, pid))
		{
			if (ft_get_exit_code(cmds) == (127))
				exit(127);
			exit(1);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		if (wstatus == 127 * 256)
			ft_print_cmd_not_found(cmds[0]->str);
		ft_set_exit_code(cmds, wstatus / 256);
	}
	return (1);
}

int		ft_check_pipes(t_cmd **cmds, int input_from_file)
{
	int		i;
	int		pipes;

	i = 0;
	pipes = 0;
	if (input_from_file == 1)
		i = 1;
	while (cmds[i + 1]->cmd != END && cmds[i + 1]->status == PIPE)
	{
		pipes++;
		i++;
	}
	return (pipes);
}

int		ft_check_redirection(t_cmd **cmds)
{
	int		i;

	i = 0;
	if (cmds[i + 1]->status == RBWS)
	{
		if (cmds[i + 2]->status == RFWS)
			return (RBWS + RFWS);
		else if (cmds[i + 2]->status == RFWD)
			return (RBWS + RFWD);
		else
			return (RBWS);
	}
	else if (cmds[i + 1]->status == RFWS || cmds[i + 1]->status == RFWD)
		return (cmds[i + 1]->status);
	return (0);
}

int		ft_check_input_from_file(t_cmd **cmds)
{
	int		i;

	i = 0;
	if (cmds[i + 1]->cmd != END && cmds[i + 1]->status == RBWS)
		return (1);
	return (0);
}

void	ft_input_from_file(t_cmd **cmds, int input_file, int j)
{
	int		fd;

	if (input_file == 1)
	{
		if ((fd = open(cmds[j + 1]->str, O_RDONLY)) == -1)
		{
			ft_putstr("-minishell: open failed\n");
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
}
