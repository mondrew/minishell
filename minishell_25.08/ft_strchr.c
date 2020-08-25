/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:01:42 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 17:33:02 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	unsigned int	i;

	ch = (unsigned char)c;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == ch)
			return (char*)(s + i);
		i++;
	}
	if (ch == '\0' && s[i] == '\0')
		return (char*)(s + i);
	return (NULL);
}
