/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:15:14 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/14 18:22:05 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!(new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (ft_free_two_null(s1, s2));
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free(s2);
	return (new_str);
}

void	ft_parse_quotes(char *str, int *i, int *single_quote, \
												int *double_quote)
{
	while (str[*i] != '$' && str[*i] != '\0')
	{
		if (str[*i] == '\'')
		{
			if (*single_quote)
				*single_quote = 0;
			else if (*double_quote)
				*single_quote = 2;
			else
				*single_quote = 1;
		}
		else if (str[*i] == '"')
		{
			if (*double_quote)
				*double_quote = 0;
			else if (*single_quote)
				*double_quote = 2;
			else
				*double_quote = 1;
		}
		(*i)++;
	}
}

int		ft_check_all_quotes(char *str, int i, int *quotes)
{
	int		single_quote;
	int		double_quote;

	single_quote = quotes[0];
	double_quote = quotes[1];
	ft_parse_quotes(str, &i, &single_quote, &double_quote);
	quotes[0] = single_quote;
	quotes[1] = double_quote;
	return (i);
}

char	*ft_str_to_res(char *str, char *res, int i, int k)
{
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * (i - k + 1))))
		return (ft_free_one_null(res));
	ft_strlcpy(tmp, &str[k], i - k + 1);
	if (!(res = ft_strjoin_free_both(res, tmp)))
		return (NULL);
	return (res);
}

char	*ft_exit_code_or_path(char *str, char *res, int *i, t_cmd **cmds)
{
	char	*tmp;

	if (str[*i] && (str[*i] == '?'))
	{
		if (!(tmp = ft_itoa(ft_get_exit_code(cmds))))
			return (ft_free_one_null(res));
	}
	else if (!(tmp = get_path_name(&str[*i])))
		return (ft_free_one_null(res));
	return (tmp);
}
