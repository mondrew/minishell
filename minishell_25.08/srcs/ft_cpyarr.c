/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:00:50 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/13 21:27:01 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_cpyarr(char **arr)
{
	char	**res;
	int		i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
		i++;
	if (!(res = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (arr[i])
	{
		if (!(res[i] = arr[i]))
			return (ft_free_split_null(res));
		i++;
	}
	res[i] = NULL;
	return (res);
}
