/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:30:44 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 09:21:18 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line_env(char **env, char *param)
{
	char	*res;

	while (*env)
	{
		if (start_with_nospace(*env, param))
		{
			if (!(res = ft_strdup(*env)))
			{
				ft_putstr("Error: cannot allocate memory\n");
				return (NULL);
			}
			return (res);
		}
		env++;
	}
	return (NULL);
}

int		ft_putstr(char *s)
{
	if (s != NULL)
		return (write(1, s, ft_strlen(s)));
	return (0);
}

int		skip_whitespace(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int		skip_non_printable(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}
