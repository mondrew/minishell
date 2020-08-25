/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:41:28 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 22:34:16 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1t;
	unsigned char	*s2t;

	if (s1 == NULL || s2 == NULL)
		return (0);
	s1t = (unsigned char*)s1;
	s2t = (unsigned char*)s2;
	i = 0;
	while (s1t[i] || s2t[i])
	{
		if (s1t[i] == '\0' && s2t[i] == '\0')
			return (0);
		if (s1t[i] != s2t[i])
			return (s1t[i] - s2t[i]);
		i++;
	}
	return (0);
}
