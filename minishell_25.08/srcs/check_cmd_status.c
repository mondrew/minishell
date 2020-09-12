/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 13:49:42 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/12 17:26:09 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_cmd_status(char *line)
{
	if (start_with_special(line, ">>"))
		return (RFWD);
	else if (start_with_special(line, ">"))
		return (RFWS);
	else if (start_with_special(line, "<"))
		return (RBWS);
	else if (start_with_special(line, ";"))
		return (NONE);
	else if (start_with_special(line, "|"))
		return (PIPE);
	else
		return (NONE);
}
