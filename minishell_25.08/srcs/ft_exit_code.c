/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:28:58 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 19:45:18 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_set_exit_code(t_cmd **cmds, int exit_code)
{
	int		i;

	i = 0;
	while (cmds && cmds[i]->cmd != END)
		i++;
	cmds[i]->status = exit_code;
}

int			ft_get_exit_code(t_cmd **cmds)
{
	int		i;

	i = 0;
	while (cmds && cmds[i]->cmd != END)
		i++;
	return (cmds[i]->status);
}
