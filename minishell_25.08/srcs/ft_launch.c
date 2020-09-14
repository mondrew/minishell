/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:37:28 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/15 00:09:21 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_cmds(t_cmd **cmds)
{
	int i;

	i = 0;
	while (cmds[i]->cmd != END)
	{
		ft_free_cmd_elem(cmds[i]);
		i++;
	}
	free(cmds[i]);
	free(cmds);
}

int			launch_commands(char *line, char ***envp, int *exit_code, int *ids)
{
	t_cmd	**cmds;
	int		i;
	int		j;

	i = 0;
	if (!(cmds = parse_cmd(line)))
		return (*exit_code = 1);
	ft_set_exit_code(cmds, *exit_code);
	while (cmds && ((cmds[i])->cmd != END))
	{
		ids[0] = i;
		if ((j = ft_execute(&(cmds[i]), envp, line, ids)) == -1)
		{
			*exit_code = ft_get_exit_code(cmds);
			ft_free_cmds(cmds);
			return (-1);
		}
		*exit_code = ft_get_exit_code(cmds);
		i += j;
	}
	free_cmds(cmds);
	return (*exit_code);
}
