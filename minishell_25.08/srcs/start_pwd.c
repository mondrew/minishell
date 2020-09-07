/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:01:27 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 00:00:17 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_path()
{
	char	cwd[PATH_MAX];

  	return (getcwd(cwd, sizeof(cwd)));
}

int		start_pwd(char *line, t_cmd **cmds)
{
	char	*path;

	if (line && *(line + skip_whitespace(line)) != '\0') // pwd doesn't care about arguments. 
	{													// It works with any number of arguments. (only on Linux)
		ft_putstr("pwd: too many arguments");
		ft_set_exit_code(cmds, 1);
		return (-1);
	}
	else
	{
		if (!(path = get_cur_path()))
		{
			printf("Error: pwd failed");
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
