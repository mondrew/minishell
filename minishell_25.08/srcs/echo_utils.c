/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 21:13:52 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/12 01:13:19 by mondrew          ###   ########.fr       */
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

void	ft_cpy_with_whitespaces(char c, int quote, int *i)
{
	if (!quote)
	{
		while (c == ' ')
			(*i)++;
	}
	else
		(*i)++;
}

void	ft_smart_cpy_whitespaces(char *str, char *new, int i, int j)
{
	int		quote;

	quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			new[j] = str[i];
			ft_cpy_with_quotes(str[i], &quote, &i);
		}
		else if (str[i] == ' ')
		{
			new[j] = str[i];
			ft_cpy_with_whitespaces(str[i], quote, &i);
		}
		else
		{
			new[j] = str[i];
			i++;
		}
		j++;
	}
	new[j] = '\0';
}

char	*remove_bad_whitespaces(char *str)
{
	int		i;
	int		j;
	int		quote;
	char	*new;

	i = 0;
	quote = 0;
	ft_parse_quotes_for_spaces(str, i, &j);
	if (!(new = malloc(sizeof(char) * (j + 1))))
		return (ft_free_one_null(str));
	j = 0;
	ft_smart_cpy_whitespaces(str, new, i, j);
	free(str);
	return (new);
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
