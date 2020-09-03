/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 13:49:42 by mondrew           #+#    #+#             */
/*   Updated: 2020/09/03 13:49:42 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_cmd_status(char *line)
{
    int     status;

    status = NONE;
    if (start_with(line, ">>"))
        return (RFWD);
    else if (start_with(line, ">")) // GJ Поменял местами, иначе никогда не определится RFWD
        return (RFWS);
    else if (start_with(line, "<"))
        return (RBWS);
    else if (start_with(line, ";"))
        return (NONE);
    else if (start_with(line, "|"))
        return (PIPE);
    else
        return (NONE);
}
