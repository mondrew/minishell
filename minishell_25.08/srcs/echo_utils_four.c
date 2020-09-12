/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils_four.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:16:29 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/12 16:53:30 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_smart_double_quotes(char *new_str, char c, int *j, int *quote)
{
	if (quote[0] == 1)
	{
		*new_str = c;
		(*j)++;
	}
	else if (quote[1] == 1)
		quote[1] = 0;
	else
		quote[1] = 1;
}

void	ft_cpy_set_null_backslash(char *new_str, char c, int *j, int *backslash)
{
	new_str[*j] = c;
	(*j)++;
	*backslash = 0;
}

void	ft_smart_cpy(char *str, char *new_str, int backslash, int *quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
			ft_smart_single_quotes(&(new_str[j]), str[i], &j, quote);
		else if (str[i] == '"' && str[i - 1] != '\\')
			ft_smart_double_quotes(&(new_str[j]), str[i], &j, quote);
		else if (str[i] == '\\')
		{
			if (str[i + 1] == '\\' && backslash == 0)
				backslash = 1;
			else if (str[i - 1] == '\\' && backslash == 1)
				ft_cpy_set_null_backslash(&(new_str[j]), str[i], &j,
				&backslash);
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
}

char	*remove_bad_quotes(char *str)
{
	char	*new_str;
	int		backslash;
	int		quote[2];

	backslash = 0;
	quote[0] = 0;
	quote[1] = 0;
	if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (ft_free_one_null(str));
	ft_smart_cpy(str, new_str, backslash, quote);
	return (new_str);
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
