/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/01 13:43:13 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int start_cd(char *line, char **env)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			ft_putstr("-minishell: cd: too many arguments\n");
			return (0);
		}
	}
	// Add "-bash: cd: too many arguments\n"
	if (ft_strlen((line + (skip_whitespace(line)))) == 1 && *(line + (skip_whitespace(line))) == '~')
		chdir(get_line_env(env, "HOME") + 5);
	else if (chdir((line + (skip_whitespace(line)))) == -1)
	{
		ft_putstr("-minishell: cd: ");
		ft_putstr((line + (skip_whitespace(line))));
		ft_putstr(": No such file or directory");
		ft_putstr("\n");
	}
	return(0);
}
