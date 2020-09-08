/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:37:28 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 19:44:56 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			launch_commands(char *line, char ***envp, int *exit_code)
{
	t_cmd	**cmds;
	int		i;
	int		status;
	int		j;

	i = 0;
	status = 0;
	if (!(cmds = parse_cmd(line)))
		return (*exit_code = 1);
	ft_set_exit_code(cmds, *exit_code);
	while (cmds && ((cmds[i])->cmd != END))
	{
		if ((j = ft_execute(&(cmds[i]), envp)) == -1)
		{
			*exit_code = ft_get_exit_code(cmds);
			ft_free_cmds(cmds);
			return (-1);
		}
		*exit_code = ft_get_exit_code(cmds);
		i += j;
	}
	i = 0;
	while (cmds[i]->cmd != END)
	{
		ft_free_cmd_elem(cmds[i]);
		i++;
	}
	free(cmds[i]);
	free(cmds);
	return (*exit_code);
}
