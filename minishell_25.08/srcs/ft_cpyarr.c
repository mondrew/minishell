/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:00:50 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/06 22:52:46 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_cpyarr(char **arr)
{
	char **res;
	int i;
	int count;

	i = 0;
	if (!arr)
		return (NULL);

	while (arr[count])
		count++;
	if (!(res = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (arr[i])
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = malloc(1);
	res[i] = NULL;
	return res;
}
