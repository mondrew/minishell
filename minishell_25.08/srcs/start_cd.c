/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 11:44:39 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir(int i, char *line, t_cmd **cmds, char **env)
{
	char	*str;
	int		j;

	j = 0;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = 0;
	while (line[j] != '\0')
		if (line[j] == ' ')
			j++;
		else
			str[i++] = line[j++];
	str[i] = '\0';
	if (ft_strlen((line + (skip_whitespace(line)))) == 1 &&
		*(line + (skip_whitespace(line))) == '~')
		chdir(get_line_env(env, "HOME") + 5);
	else if (chdir((line + (skip_whitespace(line)))) == -1)
	{
		ft_putstr("-minishell: cd: ");
		ft_putstr(str);
		ft_putstr(": No such file or directory\n");
		ft_set_exit_code(cmds, 1);
	}
	free(str);
	return (0);
}

int			start_cd(char *line, char **env, t_cmd **cmds)
{
	int		i;
	int		j;

	i = skip_whitespace(line);
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && (i += skip_whitespace(line + i)) >= 0)
			if (line[i] != '\0')
			{
				ft_putstr("-minishell: cd: too many arguments\n");
				ft_set_exit_code(cmds, 1);
				return (0);
			}
		if (line[i] != '\0' && i++)
			j++;
	}
	ft_set_exit_code(cmds, 0);
	if (!j)
	{
		chdir(get_line_env(env, "HOME") + 5);
		return (0);
	}
	return (ft_chdir(i, line, cmds, env));
}
