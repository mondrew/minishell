/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:07:51 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/12 16:44:51 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_and_redirect(t_cmd **cmds, int j, int type)
{
	int		fd;

	fd = -1;
	if (type == RBWS)
		fd = open(cmds[j + 1]->str, O_RDONLY);
	else if (type == RFWS)
		fd = open(cmds[j + 1]->str, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | \
				S_IRGRP | S_IWUSR | S_IWGRP);
	else if (type == RFWD)
		fd = open(cmds[j + 1]->str, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | \
				S_IRGRP | S_IWUSR | S_IWGRP);
	if (fd == -1)
	{
		ft_putstr("-minishell: ");
		ft_putstr(cmds[j + 1]->str);
		ft_putstr(": open failed\n");
		exit(1);
	}
	if (type == RBWS)
		dup2(fd, 0);
	else if ((type == RFWS) || (type == RFWD))
		dup2(fd, 1);
	close(fd);
}

void	ft_goto_redirection(t_cmd **cmds, int j)
{
	if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RBWS)
	{
		ft_open_and_redirect(cmds, j, RBWS);
		j++;
	}
	if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RFWS)
		ft_open_and_redirect(cmds, j, RFWS);
	else if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RFWD)
		ft_open_and_redirect(cmds, j, RFWD);
}

int		ft_execute_with_redir(t_cmd **cmds, char **envp)
{
	int		j;
	pid_t	pid;
	int		wstatus;

	j = 0;
	if ((pid = fork()) < 0)
		return (ft_print_set_exit_code(FORKFAIL, cmds));
	if (pid == 0)
	{
		ft_goto_redirection(cmds, j);
		ft_goto_execve(cmds[0], cmds, envp, pid);
	}
	else
	{
		if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RBWS)
			j++;
		if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || \
			cmds[j + 1]->status == RFWD))
			j++;
		waitpid(pid, &wstatus, 0);
		ft_set_exit_code(cmds, wstatus / 256);
	}
	return (j + 1);
}

int		ft_is_single_parent_function(t_cmd **cmds)
{
	int		i;

	i = 0;
	if ((cmds[i] && cmds[i + 1]) && (cmds[i]->cmd == CD || \
		cmds[i]->cmd == EXPORT || cmds[i]->cmd == UNSET || \
		cmds[i]->cmd == EXIT) && ((cmds[i + 1]->cmd == END) || \
		(cmds[i + 1]->cmd == NONE)))
		return (1);
	return (0);
}

int		ft_execute(t_cmd **cmds, char ***envp)
{
	int		i;
	int		pipes;
	int		input_file;

	i = 0;
	input_file = ft_check_input_from_file(cmds);
	if (ft_is_single_parent_function(cmds))
	{
		if ((i = ft_execute_in_parent(cmds, envp)) == -1)
			return (-1);
	}
	else if ((pipes = ft_check_pipes(cmds, input_file)) > 0)
	{
		if ((i = ft_execute_pipes(cmds, pipes, input_file, *envp)) == -1)
			return (-1);
	}
	else if (ft_check_redirection(cmds))
	{
		if ((i = ft_execute_with_redir(cmds, *envp)) == -1)
			return (-1);
	}
	else if ((i = ft_simple_execute(cmds, *envp)) == -1)
		return (-1);
	return (i);
}
