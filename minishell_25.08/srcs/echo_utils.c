/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 21:13:52 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/13 19:34:12 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cpy_with_quotes(char c, int *quote, int *i)
{
	if (c == '\'' && !(*quote))
		*quote = 1;
	else if (c == '"' && !(*quote))
		*quote = 2;
	else if ((c == '\'' && *quote == 1) || (c == '"' && *quote == 2))
		*quote = 0;
	(*i)++;
}

void	ft_cpy_with_whitespaces(char *str, int quote, int *i)
{
	if (!quote)
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	else
		(*i)++;
}

void	ft_smart_cpy_whitespaces(char *str, char *new_str, int i, int j)
{
	int		quote;

	quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			new_str[j] = str[i];
			ft_cpy_with_quotes(str[i], &quote, &i);
		}
		else if (str[i] == ' ')
		{
			new_str[j] = str[i];
			ft_cpy_with_whitespaces(str, quote, &i);
		}
		else
		{
			new_str[j] = str[i];
			i++;
		}
		j++;
	}
	new_str[j] = '\0';
}

char	*remove_bad_whitespaces(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	ft_parse_quotes_for_spaces(str, i, &j);
	if (!(new_str = malloc(sizeof(char) * (j + 1))))
		return (ft_free_one_null(str));
	j = 0;
	ft_smart_cpy_whitespaces(str, new_str, i, j);
	free(str);
	return (new_str);
}

char	*correct_echo_msg(char **str, char **envr, t_cmd **cmds)
{
	char	*res;

	if (!(res = change_envs(*str, envr, cmds)))
		return (NULL);
	if (!(res = remove_bad_whitespaces(res)))
		return (NULL);
	if (!(res = remove_bad_quotes(res)))
		return (NULL);
	*str = res;
	return (res);
}
