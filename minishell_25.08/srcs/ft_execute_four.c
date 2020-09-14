/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_four.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:04:38 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/14 21:47:00 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmd_nf(char *command, t_cmd **cmds, char **array, pid_t pid)
{
	if (pid)
	{
		ft_putstr("-minishell: ");
		ft_putstr(command);
		ft_putstr(": command not found\n");
	}
	ft_set_exit_code(cmds, 127);
	return (ft_free_split(array));
}

int		ft_treat_array(char **array, char **envp, t_cmd **cmds_big, pid_t pid)
{
	char	*com;
	char	**paths;
	int		i;

	i = 0;
	com = array[0];
	if (!(paths = ft_make_paths_array(envp, array[0])))
		return (ft_cmd_nf(com, cmds_big, array, pid));
	while (paths[i] != NULL)
	{
		array[0] = paths[i];
		if (execve(array[0], array, envp) == -1)
			i++;
		else
			break ;
	}
	array[0] = com;
	if (paths[i] == NULL)
	{
		ft_free_split(paths);
		return (ft_cmd_nf(com, cmds_big, array, pid));
	}
	ft_free_split(paths);
	return (1);
}

int		ft_execve_unknown(t_cmd *cmds, t_cmd **cmds_big, char **envp, pid_t pid)
{
	char	**array;

	if (!(array = ft_split(cmds->str, ' ')))
		return (0);
	if (!(array = ft_remove_quotes_in_args(array)))
		return (0);
	if (execve(array[0], array, envp) == -1)
	{
		if (!(ft_treat_array(array, envp, cmds_big, pid)))
			return (0);
	}
	ft_free_split(array);
	return (1);
}

int		ft_execve_cmd(t_cmd *cmds, t_cmd **cmds_big, char **envp, pid_t pid)
{
	int		ids[2];

	ids[0] = 0;
	ids[1] = 0;
	if (ft_is_buildin_first(cmds->cmd))
		return (ft_execve_buildins_one(cmds, cmds_big, envp));
	else if (ft_is_buildin_second(cmds->cmd))
		return (ft_execve_buildins_two(cmds, cmds_big, envp, ids));
	else if (cmds->cmd == UNKNOWN)
	{
		if (!(ft_execve_unknown(cmds, cmds_big, envp, pid)))
			return (0);
	}
	return (1);
}

void	ft_print_cmd_not_found(char *str)
{
	ft_putstr(str);
	ft_putstr(": command not found\n");
}
