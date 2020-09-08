/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:03:37 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 10:00:35 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		start_echo(char *line, char **envr, t_cmd **cmds)
{
	char *prt;

	if (!(prt = ft_strdup((line + skip_whitespace(line)))))
	{
		ft_putstr("Error: echo failed\n");
		return (-1);
	}
	if (!(prt = correct_echo_msg(&prt, envr, cmds)))
	{
		free(prt);
		ft_putstr("Error: echo failed\n");
		return (-1);
	}
	if (start_with(prt, "-n"))
		ft_putstr((prt + 2 + skip_whitespace(prt + 2)));
	else
	{
		ft_putstr(prt);
		ft_putstr("\n");
	}
	free(prt);
	return (0);
}
