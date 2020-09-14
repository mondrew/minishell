/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goto_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 23:27:51 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/14 23:28:03 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_goto_exit(t_cmd **cmds, char ***envp, char *line, int *ids)
{
	int		exit_code;

	exit_code = ft_atoi((*cmds)->str);
	ft_free_cmds(cmds - ids[0]);
	ft_free_envp_null_ids(*envp, ids);
	free(line);
	exit(exit_code);
}
