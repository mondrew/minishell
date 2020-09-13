/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 09:14:22 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/13 17:19:33 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strdup(char *str)
{
	char	*dest;
	char	*temp;

	if (!str)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!temp)
		return (NULL);
	dest = temp;
	while (*str)
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (dest);
}
