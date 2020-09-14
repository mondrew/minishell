/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_six.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:07:04 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/14 23:10:31 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_command_to_paths(char **paths, char *command, int i, int j)
{
	int		k;
	char	*str;

	while (paths[i] != NULL)
	{
		j = 0;
		k = 0;
		if (!(str = malloc(sizeof(char) * \
			(ft_strlen(paths[i]) + 1 + ft_strlen(command) + 1))))
			return (ft_free_split_null(paths));
		while (paths[i][j] != '\0')
		{
			str[j] = paths[i][j];
			j++;
		}
		if (paths[i][j - 1] != '/')
			str[j++] = '/';
		while (command[k] != '\0')
			str[j++] = command[k++];
		str[j] = '\0';
		free(paths[i]);
		paths[i] = str;
		i++;
	}
	return (paths);
}

char	**ft_make_paths_array(char **envp, char *command)
{
	char	**paths;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(paths = ft_split(get_path(envp), ':')))
		return (NULL);
	paths = ft_add_command_to_paths(paths, command, i, j);
	return (paths);
}

t_cmd	**ft_free_cmds(t_cmd **cmds)
{
	int		i;

	i = 0;
	if (!cmds || !cmds[i])
		return (NULL);
	while (cmds[i]->cmd != END)
	{
		free(cmds[i]->str);
		free(cmds[i]);
		i++;
	}
	free(cmds[i]);
	free(cmds);
	return (NULL);
}

void	ft_free_cmd_elem(t_cmd *cmds)
{
	free(cmds->str);
	free(cmds);
}

int		ft_print_set_exit_code(int error, t_cmd **cmds)
{
	if (error == MALLOCFAIL)
		ft_putstr("Error: cannot allocate memory\n");
	else if (error == FORKFAIL)
		ft_putstr("Error: fork failed\n");
	else if (error == FORKFAIL)
		ft_putstr("Error: pipe failed\n");
	ft_set_exit_code(cmds, 1);
	return (-1);
}
