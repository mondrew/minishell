/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 15:19:27 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int start_env(char *line, char **envp)
{
	while (envp && *envp)
	{
		ft_putstr(*envp);
		ft_putstr("\n");
		envp++;
	}
	return(0);
}
