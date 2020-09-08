/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 19:48:51 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strswap(char **strs, int i1, int i2)
{
	char		*tmp;

	tmp = strs[i1];
	strs[i1] = strs[i2];
	strs[i2] = tmp;
}

void	show(char **envp)
{
	int i;

	i = 0;
	if (envp)
		while (envp[i])
		{
			ft_putstr(envp[i]);
			ft_putstr("\n");
			i++;
		}
}

char	**sort_and_show(char **tenvp)
{
	char	**envp;
	int		is_sort;
	int		i;

	envp = ft_cpyarr(tenvp);
	is_sort = 0;
	i = 0;
	while (envp && envp[i] && envp[i + 1])
	{
		while (envp[i + 1])
		{
			if (ft_strcmp(envp[i], envp[i + 1]) <= 0)
				i++;
			else
			{
				ft_strswap(envp, i, i + 1);
				break ;
			}
		}
		if (!envp[i + 1])
			break ;
		i = 0;
	}
	show(envp);
	return (envp);
}

char	**parse_and_add(char *line, char **envp, t_cmd **cmds)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	char	**new_envp;

	i = 0;
	j = 0;
	value = NULL;
	while (line[i] != '=' && line[i] != ' ' && line[i] != '\0')
		i++;
	if (!(key = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strlcpy(key, line, i + 1);
	if (line[i] == ' ' || line[i] == '\0')
	{
		new_envp = ft_add_or_replace(key, value, envp);
		if (!new_envp)
			free(key);
		return (new_envp);
	}
	else if (line[i] == '=' && (line[i + 1] == '\0' || line[i + 1] == ' '))
	{
		new_envp = ft_add_or_replace(key, "", envp);
		if (!new_envp)
			free(key);
		return (new_envp);
	}
	else if (line[i] == '=')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (!(value = malloc(sizeof(char) * (i - j + 1))))
	{
		free(key);
		return (NULL);
	}
	ft_strlcpy(value, &(line[j]), i - j + 1);
	if (!(value = correct_echo_msg(&value, envp, cmds)))
	{
		free(value);
		free(key);
		ft_putstr("Error: export failed\n");
		return (NULL);
	}
	if (!(new_envp = ft_add_or_replace(key, value, envp)))
	{
		free(key);
		free(value);
		return (NULL);
	}
	free(key);
	free(value);
	return (new_envp);
}

int		start_export(char *line, char ***envp, t_cmd **cmds)
{
	char	**new_envp;

	new_envp = NULL;
	if (!line || !line[skip_whitespace(line)])
	{
		if (!(new_envp = sort_and_show(*envp)))
			return (-1);
		free(new_envp);
		return (1);
	}
	else
	{
		if (!(new_envp = parse_and_add(line, *envp, cmds)))
			return (-1);
	}
	*envp = new_envp;
	return (1);
}
