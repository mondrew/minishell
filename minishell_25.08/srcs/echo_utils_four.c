/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils_four.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:16:29 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/12 01:17:53 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_smart_double_quotes(char *new, char c, int *j, int *quote)
{
	if (quote[0] == 1)
	{
		*new = c;
		(*j)++;
	}
	else if (quote[1] == 1)
		quote[1] = 0;
	else
		quote[1] = 1;
}

void	ft_cpy_set_null_backslash(char *new, char c, int *j, int *backslash)
{
	new[*j] = c;
	(*j)++;
	*backslash = 0;
}

void	ft_smart_cpy(char *str, char *new, int backslash, int *quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
			ft_smart_single_quotes(&(new[j]), str[i], &j, quote);
		else if (str[i] == '"' && str[i - 1] != '\\')
			ft_smart_double_quotes(&(new[j]), str[i], &j, quote);
		else if (str[i] == '\\')
		{
			if (str[i + 1] == '\\' && backslash == 0)
				backslash = 1;
			else if (str[i - 1] == '\\' && backslash == 1)
				ft_cpy_set_null_backslash(&(new[j]), str[i], &j, &backslash);
		}
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
}

char	*remove_bad_quotes(char *str)
{
	char	*new;
	int		backslash;
	int		quote[2];

	backslash = 0;
	quote[0] = 0;
	quote[1] = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (ft_free_one_null(str));
	ft_smart_cpy(str, new, backslash, quote);
	return (new);
}

char	*get_path_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] != ' ' && str[i] != '"' && str[i] != '\'' && str[i] != '\0')
		i++;
	if (!(var = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != '"' && str[i] != '\'' && str[i] != '\0')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}