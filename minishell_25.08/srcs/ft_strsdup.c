/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:20:12 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/03 18:25:52 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return str from start position to any char of set position
static int	is_contains_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return 1;
		set++;
	}
	return (0);
}

char	*ft_strsdup(char *str, char *set) // mondrew
{
	int		i;
	int		j;
	char	*new;

	i = skip_non_printable(str);
	j = i;
	while (str[j] && !is_contains_in_set(str[j], set))
		j++;
	if (!(new = malloc(sizeof(char) * ((j - i) + 1))))
		return (NULL);
	j = 0;
	while (str[i] && !is_contains_in_set(str[i], set))
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[i] = '\0';
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