/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/06 17:38:41 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		start_cd(char *line, char **env, t_cmd **cmds)
{
	int		i;
	int		j;
	char	*str;
	//char	cwd[PATH_MAX]; ///////////////////////////for testing

	i = 0;
	while (line[i] == ' ') // No need, 'cause in cmds->str we already have and string without spaces in the beginning
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] != '\0')
			{
				ft_putstr("-minishell: cd: too many arguments\n");
				ft_set_exit_code(cmds, 1);
				return (0);
			}
		}
		if (line[i] != '\0')
			i++;
	}
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = 0;
	while (line[j] != '\0')
	{
		if (line[j] == ' ')
			j++;
		else
		{
			str[i] = line[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	//printf("Current path: %s\n", getcwd(cwd, sizeof(cwd))); ////////////// for testing
	ft_set_exit_code(cmds, 0);
	if (ft_strlen((line + (skip_whitespace(line)))) == 1 && *(line + (skip_whitespace(line))) == '~')
	{
		chdir(get_line_env(env, "HOME") + 5);
  		//printf("New path (home): %s\n", getcwd(cwd, sizeof(cwd))); ////////////// for testing
	}
	else if (chdir((line + (skip_whitespace(line)))) == -1)
	{
		ft_putstr("-minishell: cd: ");
		ft_putstr(str);
		ft_putstr(": No such file or directory");
		ft_putstr("\n");
		ft_set_exit_code(cmds, 1);
	}
	//printf("New path: %s\n", getcwd(cwd, sizeof(cwd))); ////////////// for testing
	free(str);
	return (0);
}
