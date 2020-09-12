/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:56:53 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/12 16:46:46 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_middle_pipe(int *pipefd, t_cmd **cmds, int j, char **envp)
{
	pid_t	pid;
	int		pipes;
	int		i;

	i = 2;
	pipes = ft_check_pipes(cmds, ft_check_input_from_file(cmds));
	while (pipes > 1)
	{
		if (pipe(pipefd + i) < 0)
			return (ft_print_set_exit_code(PIPEFAIL, cmds));
		if ((pid = fork()) < 0)
			return (ft_print_set_exit_code(FORKFAIL, cmds));
		if (pid == 0)
		{
			ft_change_child_fd_pipe(pipefd, i, MIDDLEPIPE);
			ft_goto_execve(cmds[j], cmds, envp, pid);
		}
		else
		{
			i = ft_close_fds_in_parent_pipe(pipefd, i);
			j = ft_parent_wait(pid, cmds, j);
			pipes--;
		}
	}
	return (j);
}

void	ft_open_failed_and_exit(void)
{
	ft_putstr("-minishell: open failed\n");
	exit(1);
}

void	ft_redirection_to_file(t_cmd **cmds, int j)
{
	int		fd;

	fd = 0;
	if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || \
		cmds[j + 1]->status == RFWD))
	{
		if (cmds[j + 1]->status == RFWS)
		{
			if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_TRUNC | O_CREAT, \
				S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
				ft_open_failed_and_exit();
		}
		else if (cmds[j + 1]->status == RFWD)
		{
			if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_APPEND | O_CREAT, \
				S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
				ft_open_failed_and_exit();
		}
		dup2(fd, 1);
		close(fd);
	}
}

int		ft_last_pipe(int *pipefd, t_cmd **cmds, int j, char **envp)
{
	pid_t	pid;
	int		i;

	i = (ft_check_pipes(cmds, ft_check_input_from_file(cmds))) * 2;
	if ((pid = fork()) < 0)
		return (ft_print_set_exit_code(FORKFAIL, cmds));
	if (pid == 0)
	{
		ft_redirection_to_file(cmds, j);
		ft_change_child_fd_pipe(pipefd, i, LASTPIPE);
		ft_goto_execve(cmds[j], cmds, envp, pid);
	}
	else
	{
		if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || \
			cmds[j + 1]->status == RFWD))
			j++;
		ft_close_fds_in_parent_pipe(pipefd, i);
		j = ft_parent_wait(pid, cmds, j);
	}
	return (j);
}

int		ft_execute_pipes(t_cmd **cmds, int pipes, int input_file, char **envp)
{
	int		pipefd[pipes * 2];
	int		i;
	int		j;

	i = 2;
	j = 0;
	if ((j = ft_first_pipe(pipefd, cmds, input_file, envp)) == -1)
		return (-1);
	if ((j = ft_middle_pipe(pipefd, cmds, j, envp)) == -1)
		return (-1);
	if ((j = ft_last_pipe(pipefd, cmds, j, envp)) == -1)
		return (-1);
	return (j);
}
