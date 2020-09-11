/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:28:29 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/11 09:05:33 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**remove_str(char **envp, int del)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (envp[i])
		i++;
	if (!(new_arr = malloc(sizeof(char *) * i)))
		return (NULL);
	i = 0;
	while (envp[i] && i != del)
	{
		if (!(new_arr[i] = ft_strdup(envp[i])))
			return (ft_free_array(new_arr));
		i++;
	}
	i++;
	while (envp[i])
	{
		if (!(new_arr[i - 1] = ft_strdup(envp[i])))
			return (ft_free_array(new_arr));
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

char			**remove_key(char *key, char **envp)
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
			return (remove_str(envp, i));
		i++;
	}
	return (ft_copy_array(envp));
}
