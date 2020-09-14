/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_envp_null_ids.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 23:16:33 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/14 23:17:28 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_free_envp_null_ids(char **envp, int *ids)
{
	if (ids[1])
	{
		ft_free_split(envp);
		ids[1] = 0;
	}
}
