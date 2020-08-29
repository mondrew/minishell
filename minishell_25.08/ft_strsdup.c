/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:20:12 by gjessica          #+#    #+#             */
/*   Updated: 2020/08/28 09:28:49 by gjessica         ###   ########.fr       */
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

char *ft_strsdup(char *str, char *set)
{
	char			*dest;
	char			*temp;

	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!temp)
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
