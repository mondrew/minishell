/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:20:12 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/06 23:51:46 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return str from start position to any char of set position
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

char	*ft_strsdup(char *str, char *set) // mondrew // fixed problem with whitespaces after the last echo argument
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	*new;

	i = skip_non_printable(str);
	j = i;
	k = 0;
	quote = 0;
	while (str[j])
	{
		if (str[j] == '"' || str[j] == '\'')
		{
			if (str[j] == '\'' && !quote)
				quote = 1;
			else if (str[j] == '"' && !quote)
				quote = 2;
			else if ((str[j] == '\'' && quote == 1) || (str[j] == '"' && quote == 2))
				quote = 0;
			j++;
		}
		else if (is_contains_in_set(str[j], set) && !quote)
			break ;
		else
			j++;
	}
	while (str[j - 1] == ' ') // added 04.09 назад на пробелы |lala_|_|_|\0
		j--;
	k = j - i;
	if (!(new = malloc(sizeof(char) * (k + 1))))
		return (NULL);
	j = 0;
	while (j < k)
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

/*
char	*ft_strsdup(char *str, char *set)
{
	char	*dest;
	char	*temp;

	if (!(temp = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	dest = temp;
	while (*str && !is_contains_in_set(*str, set))
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (dest);
}
*/