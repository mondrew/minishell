/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:20:12 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/13 14:56:55 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_contains_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_new(char *str, int j, int i)
{
	int		k;
	char	*new_str;

	k = 0;
	while (str[j - 1] == ' ')
		j--;
	k = j - i;
	if (!(new_str = malloc(sizeof(char) * (k + 1))))
		return (NULL);
	j = 0;
	while (j < k)
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char		*ft_strsdup(char *str, char *set)
{
	int		i;
	int		j;
	int		quote;

	i = skip_non_printable(str);
	j = i;
	quote = 0;
	while (str[j])
	{
		if (str[j] == '"' || str[j] == '\'')
		{
			if (str[j] == '\'' && !quote)
				quote = 1;
			else if (str[j] == '"' && !quote)
				quote = 2;
			else if ((str[j] == '\'' && quote == 1) ||
			(str[j] == '"' && quote == 2))
				quote = 0;
			j++;
		}
		else if (is_contains_in_set(str[j], set) && !quote)
			break ;
		else
			j++;
	}
	return (ft_new(str, j, i));
}
