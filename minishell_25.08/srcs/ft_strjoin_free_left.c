/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 09:15:21 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/05 21:29:10 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strjoin_free_left(char *s1, char *s2)
{
	char		*str;
	char		*res;
	size_t		len1;
	size_t		len2;

	if (!s1 && !s2)
		return (NULL);
	if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	res = str;
	while (*s1)
		*str++ = *s1++;
	free(s1 - len1);
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (res);
}
