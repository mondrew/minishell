/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 11:59:12 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 11:59:45 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(void)
{
	ft_putstr("\n");
	print_prompt();
}

void	sigquit(void)
{
	ft_putstr("minishell: quit (core dumped)\n");
}

void	signotactive(void)
{
	return ;
}

void	sigintexec(void)
{
	ft_putstr("\n");
}
