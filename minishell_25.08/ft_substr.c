/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:40:51 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 17:17:42 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_len_to_char(char *str, char end)
{
	int count;

	count = 0;
	while(str && *str)
	{
		if (*str == end)
			return count;
		count++;
		str++;
	}
	return count;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	size_res;

	if (s == NULL)
		return (NULL);
	if (ft_strlen((char *)s) < start)
		return (ft_strdup(""));
	size_res = ft_strlen((char*)s + start);
	if (len > size_res)
		len = size_res;
	i = 0;
	res = malloc(len * (sizeof(char)) + sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
