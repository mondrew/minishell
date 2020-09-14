/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:14:06 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/14 23:09:06 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_env_name(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || \
		(c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

char	*ft_add_env_value(char *str, char *res, char *param, int *i)
{
	if (param)
	{
		if (!(res = ft_strjoin_free_left(res, param + ft_skip_env_key(param))))
			return (ft_free_one_null(param));
		free(param);
		while (ft_is_env_name(str[*i]))
			(*i)++;
	}
	return (res);
}

char	*ft_replace_env(char **help, char **envp, int *i, t_cmd **cmds)
{
	char	*tmp;
	char	*param;

	param = NULL;
	(*i)++;
	if (!(tmp = ft_exit_code_or_path(help[0], help[1], i, cmds)))
		return (NULL);
	if (help[0][*i] && (help[0][*i] == '?'))
	{
		if (!(help[1] = ft_strjoin_free_both(help[1], tmp)))
			return (NULL);
		(*i)++;
	}
	else if (!(param = get_line_env(envp, tmp)))
	{
		if (!(param = ft_strdup("")))
			return (ft_free_two_null(help[1], tmp));
		free(tmp);
	}
	else
		free(tmp);
	if (!(help[1] = ft_add_env_value(help[0], help[1], param, i)))
		return (NULL);
	return (help[1]);
}

int		ft_is_only_dollar_sign(char *str, int i)
{
	if (str[i] && (str[i] == '$') && \
		((str[i + 1] && (str[i + 1] == ' ')) || !str[i + 1]))
		return (1);
	return (0);
}

char	*ft_add_bf_dollar_to_res(char *str, char *res, int *i, int *quotes)
{
	int		k;

	k = *i;
	*i = ft_check_all_quotes(str, *i, quotes);
	if (!(res = ft_str_to_res(str, res, *i, k)))
		return (NULL);
	return (res);
}
