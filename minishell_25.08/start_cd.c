/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/08/31 08:15:31 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int start_cd(char *line, char **env)
{
	if (ft_strlen((line + (skip_whitespace(line)))) == 1 && *(line + (skip_whitespace(line))) == '~')
		chdir(get_line_env(env, "HOME=") + 5);
	else if (chdir((line + (skip_whitespace(line)))) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr((line + (skip_whitespace(line))));
		ft_putstr("\n");
	}
	return(0);
}
