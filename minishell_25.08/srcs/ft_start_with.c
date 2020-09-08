/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_with.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 09:19:59 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 19:44:48 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		start_with_nospace(char *str, char *con)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return (0);
		i++;
	}
	if (str[i] == '=' && (con[i] == ' ' || con[i] == '$' || con[i] == '\0'))
		return (1);
	return (0);
}

int		start_with(char *str, char *con)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return (0);
		i++;
	}
	if (!con[i] && (!str[i] || str[i] == ' ' || str[i] == ';' || \
		str[i] == '>' || str[i] == '<' || str[i] == '|'))
		return (1);
	return (0);
}

int		start_with_special(char *str, char *con)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return (0);
		i++;
	}
	if (!con[i])
		return (1);
	return (0);
}
