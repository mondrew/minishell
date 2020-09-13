/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/13 17:26:11 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_and_show(char **tenvp)
{
	char	**envp;
	int		i;

	if (!(envp = ft_cpyarr(tenvp)))
		return (NULL);
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

char	*get_key(char *line, int *i)
{
	char *key;

	while (line[*i] != '=' && line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(key = malloc(sizeof(char) * (*i + 1))))
		return (NULL);
	ft_strlcpy(key, line, (*i) + 1);
	return (key);
}

char	*get_value(int *i, char *line, char **key)
{
	int		j;
	char	*value;

	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(value = malloc(sizeof(char) * (*i - j + 1))))
	{
		free_key_val_ret(key, NULL, NULL);
		return (NULL);
	}
	ft_strlcpy(value, &(line[j]), *i - j + 1);
	return (value);
}

char	**parse_and_add(char *line, char **envp, t_cmd **cmds)
{
	int		i;
	char	*key;
	char	*value;
	char	**new_envp;

	i = 0;
	value = NULL;
	if (!(key = get_key(line, &i)))
		return (NULL);
	if (line[i] == '=' && !(line[i + 1] == '\0' || line[i + 1] == ' '))
		i++;
	else if ((line[i] == ' ' || line[i] == '\0') ||
	(line[i] == '=' && (line[i + 1] == '\0' || line[i + 1] == ' ')))
	{
		if (!(new_envp = ft_add_or_replace(key,
		(line[i] == ' ' || line[i] == '\0') ? value : "", envp)))
			free(key);
		return (new_envp);
	}
	if (!(value = get_value(&i, line, &key)))
		return (NULL);
	if (!(value = correct_echo_msg(&value, envp, cmds)) ||
			!(new_envp = ft_add_or_replace(key, value, envp)))
		return (free_key_val_ret(&key, &value, NULL));
	return (free_key_val_ret(&key, &value, new_envp));
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
