/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:01:27 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/12 21:40:11 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_path(void)
{
	return (getcwd(NULL, PATH_MAX));
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
			free(path);
		}
	}
	ft_putstr("\n");
	return (0);
}
