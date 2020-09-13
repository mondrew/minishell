/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:06:02 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/13 11:21:46 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execute_in_parent(t_cmd **cmds, char ***envp, char *line)
{
	int		exit_code;

	if ((*cmds)->cmd == CD)
	{
		if ((start_cd((*cmds)->str, *envp, cmds)) == -1)
			return (ft_print_set_exit_code(MALLOCFAIL, cmds));
	}
	else if ((*cmds)->cmd == EXPORT)
	{
		if ((start_export((*cmds)->str, envp, cmds)) == -1)
			return (ft_print_set_exit_code(MALLOCFAIL, cmds));
	}
	else if ((*cmds)->cmd == UNSET)
	{
		if (!(start_unset((*cmds)->str, envp)))
			return (ft_print_set_exit_code(MALLOCFAIL, cmds));
	}
	else if ((*cmds)->cmd == EXIT)
	{
		exit_code = ft_atoi((*cmds)->str);
		ft_free_cmds(cmds);
		free(line);
		exit(exit_code);
	}
	return (1);
}

int		ft_is_buildin_first(int cmd)
{
	if ((cmd == PWD) || (cmd == ECHO) || \
		(cmd == CD) || (cmd == ENV))
		return (1);
	return (0);
}

int		ft_is_buildin_second(int cmd)
{
	if ((cmd == EXPORT) || (cmd == UNSET) || \
		(cmd == EXIT))
		return (1);
	return (0);
}

int		ft_execve_buildins_one(t_cmd *cmds, t_cmd **cmds_big, char **envp)
{
	if (cmds->cmd == PWD)
	{
		if ((start_pwd(cmds->str, cmds_big)) == -1)
			return (0);
	}
	else if (cmds->cmd == ECHO)
	{
		if ((start_echo(cmds->str, envp, cmds_big)) == -1)
			return (0);
	}
	else if (cmds->cmd == CD)
	{
		if ((start_cd(cmds->str, envp, cmds_big)) == -1)
			return (0);
	}
	else if (cmds->cmd == ENV)
		start_env(cmds->str, envp);
	return (1);
}

int		ft_execve_buildins_two(t_cmd *cmds, t_cmd **cmds_big, char **envp)
{
	int		exit_code;

	if (cmds->cmd == EXPORT)
	{
		if (!(start_export(cmds->str, &envp, cmds_big)))
			return (0);
	}
	else if (cmds->cmd == UNSET)
	{
		if (!(start_unset(cmds->str, &envp)))
			return (0);
	}
	else if (cmds->cmd == EXIT)
	{
		exit_code = ft_atoi(cmds->str);
		exit(exit_code);
	}
	return (1);
}
