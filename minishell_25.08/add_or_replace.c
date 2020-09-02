/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_or_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 10:07:51 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/02 12:34:22 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**ft_free_special_array(char **arr, int n)
{
	int i;

	i = 0;
	while (arr[i] && i < n)
	{
		free(arr[i]);
		i++;
	}
	if (i == n)
		i++;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char **ft_copy_array(char **envp)
{
	int i;
	char **new_arr;

	i = 0;
	while (envp[i])
		i++;
	if (!(new_arr = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!(new_arr[i] = ft_strdup(envp[i])))
			return (ft_free_array(new_arr));
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

static char	**ft_replace_value(char **envp, char *value, int i)
{
	char **new_arr;
	int j;

	j = 0;
	if (!(new_arr = ft_copy_array(envp)))
		return (NULL);
	free(new_arr[i]);
	while (envp[i][j] != '=')
		j++;
	if (!(new_arr[i] = malloc(sizeof(char) * (j + 1 + ft_strlen(value) + 1))))
		return (ft_free_special_array(new_arr, i));
	j = 0;
	while (envp[i][j] != '=')
	{
		new_arr[i][j] = envp[i][j];
		j++;
	}
	new_arr[i][j] = envp[i][j];
	j++;
	while (*value)
		new_arr[i][j++] = *(value++);
	new_arr[i][j] = '\0';
	return (new_arr);
}

static char	**ft_add_value(char *key, char *value, char **envp)
{
	int i;
	char **new_arr;
	char *temp;

	i = 0;
	while (envp[i])
		i++;
	if (!(new_arr = malloc(sizeof(char *) * (i + 1 + 1))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!(new_arr[i] = ft_strdup(envp[i])))
			return (ft_free_array(new_arr));
		i++;
	}
	if (value == NULL)
	{
		if (!(new_arr[i] = ft_strdup(key)))
			return (ft_free_array(new_arr));
	}
	else // add here strjoin_free_left (my version)
	{
		if (value[0] != '"')
		{
			if (!(temp = ft_strjoin(key, "=\"")))
				return (ft_free_array(new_arr));
		}
		else if (!(temp = ft_strjoin(key, "=")))
			return (ft_free_array(new_arr));
		if (!(new_arr[i] = ft_strjoin(temp, value)))
		{
			free(temp);
			return (ft_free_array(new_arr));
		}
		free(temp);
		if (value[0] != '"')
		{
			temp = new_arr[i];
			if (!(new_arr[i] = ft_strjoin(temp, "\"")))
			{
				free(temp);
				return (ft_free_array(new_arr));
			}
			free(temp);
		}
	}
	i++;
	new_arr[i] = NULL;
	return (new_arr);
}

char	**add_or_replace(char *key, char *value, char **envp)
{
	int i;
	int j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '\0' && envp[i][j] != '=' && key[j] != '\0')
		{
			if (envp[i][j] == key[j])
				j++;
			else
				break ;
		}
		if (envp[i][j] == '=' && key[j] == '\0')
		{
			if (!ft_strncmp(value, &envp[i][j + 1], ft_strlen(value) + 1))
				return (ft_copy_array(envp)); // ну это точно не нужно делать, просто вернем NULL
			else
				return (ft_replace_value(envp, value, i));
		}
		i++;
	}
	return (ft_add_value(key, value, envp));
}
