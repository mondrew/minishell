/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:01:27 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 09:25:04 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_path(void)
{
	char	cwd[PATH_MAX];

	return (getcwd(cwd, sizeof(cwd)));
}

int		start_pwd(char *line, t_cmd **cmds)
{
	char	*path;

	if (line && *(line + skip_whitespace(line)) != '\0')
	{
		ft_putstr("pwd: too many arguments");
		ft_set_exit_code(cmds, 1);
		return (-1);
	}
	else
	{
		if (!(path = get_cur_path()))
		{
			ft_putstr("Error: pwd failed");
			ft_set_exit_code(cmds, 1);
		}
		else
		{
			ft_putstr(path);
		}
	}
	ft_putstr("\n");
	return (0);
}
