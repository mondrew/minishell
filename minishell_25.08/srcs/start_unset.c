/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:07:51 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:15 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free_arr(char **arr, int j) // made by mondrew
{
	// эту ф-цию можно использовать для всей программы
	int		i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_new_env_arr(char ***old, int i) // made by mondrew
{
	char	**new;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (*old == NULL)
		return (NULL);
	while ((*old)[j] != NULL)
		j++;
	j--;
	if (!(new = malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	j = 0;
	while ((*old)[k] != NULL)
	{
		if (k != i)
		{
			if (!(new[j] = ft_strdup((*old)[k])))
				return (ft_free_arr(new, j));
			j++;
		}
		k++;
	}
	new[j] = NULL;
	//ft_free_arr(*old, k); // I should not free envp
	return (new);
}

int		start_unset(char *line, char ***envp) // made by mondrew
{
	int		i;
	char	**new;

	i = 0;
	if (!(*line))
		return (1);
	while ((*envp)[i] != NULL)
	{
		if (!ft_strncmp(line, (*envp)[i], ft_strlen(line)) && ((*envp)[i][ft_strlen(line)] == '=')) // correct GJ
			break ;
		i++;
	}
	if ((*envp)[i] != NULL)
	{
		if (!(new = ft_new_env_arr(envp, i)))
			return (0);
		*envp = new;
	}
	return (1);
}
