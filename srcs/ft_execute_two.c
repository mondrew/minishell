#include "minishell.h"

void	ft_goto_execve(t_cmd *cmds, t_cmd **cmds_big, char **envp, pid_t pid)
{
	if (!ft_execve_cmd(cmds, cmds_big, envp, pid))
	{
		if (ft_get_exit_code(cmds_big) == 127)
			exit(127);
		exit(1);
	}
	exit(0);
}

int		ft_parent_wait(int pid, t_cmd **cmds, int j)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	if (wstatus == 127 * 256)
	{
		ft_putstr(cmds[j]->str);
		ft_putstr(": command not found\n");
	}
	ft_set_exit_code(cmds, wstatus / 256);
	j++;
	return (j);
}

int		ft_first_pipe(int *pipefd, t_cmd **cmds, int input_file, char **envp)
{
	pid_t	pid;
	int		j;

	j = 0;
	if (pipe(pipefd) < 0)
		return (ft_print_set_exit_code(PIPEFAIL, cmds));
	if ((pid = fork()) < 0)
		return (ft_print_set_exit_code(FORKFAIL, cmds));
	if (pid == 0)
	{
		ft_input_from_file(cmds, input_file, j);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_goto_execve(cmds[j], cmds, envp, pid);
	}
	else
	{
		j = ft_parent_wait(pid, cmds, j);
		if (input_file == 1)
			j++;
	}
	return (j);
}

void	ft_change_child_fd_pipe(int *pipefd, int i, int id)
{
	close(pipefd[i - 1]);
	dup2(pipefd[i - 2], STDIN_FILENO);
	close(pipefd[i - 2]);
	if (id == MIDDLEPIPE)
	{
		close(pipefd[i]);
		dup2(pipefd[i + 1], STDOUT_FILENO);
		close(pipefd[i + 1]);
	}
}

int		ft_close_fds_in_parent_pipe(int *pipefd, int i)
{
	close(pipefd[i - 2]);
	close(pipefd[i - 1]);
	i += 2;
	return (i);
}
