/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:03:37 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/29 08:36:50 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int start_echo(char *line, char **envr)
{
	char *prt;

	prt = ft_strdup((line + skip_whitespace(line)));
	correct_echo_msg(&prt, envr);
	if (start_with(prt, "-n"))
		ft_putstr((prt + 2 + skip_whitespace(prt)));
	else
	{
		ft_putstr((prt + skip_whitespace(prt)));
		ft_putstr("\n");
	}
	free(prt);
	return (0);
}
