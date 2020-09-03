/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:32:59 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 17:36:13 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_split_size(char const *s, size_t i, char c)
{
	size_t	size;

	size = 0;
	while (s[size + i] != '\0' && s[size + i] != c)
		size++;
	return (size);
}

static size_t	skip_contains_char(char const *s, size_t i, char c)
{
	while (s[i] && (char)s[i] == c)
		i++;
	return (i);
}

static int		free_result(char **result, size_t res_i)
{
	size_t i;

	i = 0;
	while (i < res_i)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static int		splits_words(char const *s, char c, char **result)
{
	size_t	i;
	size_t	split_size;
	size_t	res_i;
	size_t	j;

	i = 0;
	res_i = 0;
	while (s[i = skip_contains_char(s, i, c)] != '\0')
	{
		split_size = get_split_size(s, i, c);
		result[res_i] = (char*)malloc(split_size * sizeof(char) + sizeof(char));
		if (result[res_i] == NULL)
			return (free_result(result, res_i));
		j = 0;
		while (j < split_size)
		{
			result[res_i][j] = s[i];
			i++;
			j++;
		}
		result[res_i][j] = '\0';
		res_i++;
	}
	result[res_i] = NULL;
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	count_word;
	size_t	i;

	i = 0;
	count_word = 1;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			count_word++;
		}
	}
	result = (char**)malloc(count_word * sizeof(char*));
	if (result == NULL)
		return (NULL);
	if (!splits_words(s, c, result))
		return (NULL);
	return (result);
}
