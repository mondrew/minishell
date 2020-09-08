/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:29:34 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/08 11:57:46 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			skip_status(char *str)
{
	int i;

	i = 0;
	while (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
		i++;
	return (i);
}

int			count_cmd(char *line)
{
	int		i;
	int		count;
	int		quote;

	i = 0;
	count = 1;
	quote = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (line[i] == '\'' && !quote)
				quote = 1;
			else if (line[i] == '"' && !quote)
				quote = 2;
			else if ((line[i] == '\'' && quote == 1) || (line[i] == '"' &&
			quote == 2))
				quote = 0;
		}
		else if ((line[i] == '>' && line[i + 1] && line[i + 1] == '>'
		&& !quote))
		{
			count++;
			i++;
		}
		else if ((line[i] == ';' || line[i] == '>' || line[i] == '<' ||
		line[i] == '|') \
					&& !quote)
			count++;
		i++;
	}
	return (count);
}

int			set_param(t_cmd **cmds, char *str, int cmd_id, int status)
{
	int		i;

	i = 0;
	(*cmds)->cmd = cmd_id;
	if (!((*cmds)->str = ft_strsdup(str, "><|;")))
		return (-1);
	(*cmds)->status = status;
	i = skip_non_printable(str);
	return (i + ft_strlen((*cmds)->str) - 1);
}

t_cmd		**parse_cmd(char *line)
{
	int		i;
	int		cmd_i;
	int		status;
	t_cmd	**cmds;

	i = 0;
	cmd_i = 0;
	status = NONE;
	if (!(cmds = malloc(sizeof(t_cmd) * (count_cmd(line) + 1))))
	{
		printf("Error: cannot allocate memory\n");
		return (NULL);
	}
	if (!(cmds[0] = malloc(sizeof(t_cmd))))
	{
		printf("Error: cannot allocate memory\n");
		free(cmds);
		return (NULL);
	}
	while (line[i])
	{
		i += skip_non_printable(line + i);
		if (line[i])
			status = check_cmd_status(line + i);
		if (line[i])
			i += skip_status(line + i);
		if (line[i])
			i += skip_non_printable(line + i);
		if (!line[i])
			break ;
		if (start_with(line + i, "echo"))
			i += set_param(&cmds[cmd_i], line + i + 4, ECHO, status) + 4;
		else if (start_with(line + i, "cd"))
			i += set_param(&cmds[cmd_i], line + i + 2, CD, status) + 2;
		else if (start_with(line + i, "pwd"))
			i += set_param(&cmds[cmd_i], line + i + 3, PWD, status) + 3;
		else if (start_with(line + i, "export"))
			i += set_param(&cmds[cmd_i], line + i + 6, EXPORT, status) + 6;
		else if (start_with(line + i, "unset"))
			i += set_param(&cmds[cmd_i], line + i + 5, UNSET, status) + 5;
		else if (start_with(line + i, "env"))
			i += set_param(&cmds[cmd_i], line + i + 3, ENV, status) + 3;
		else if (start_with(line + i, "exit"))
			i += set_param(&cmds[cmd_i], line + i + 4, EXIT, status) + 4;
		else
			i += set_param(&cmds[cmd_i], line + i, UNKNOWN, status);
		cmd_i++;
		i++;
		status = NONE;
		if (!(cmds[cmd_i] = malloc(sizeof(t_cmd))))
		{
			printf("Error: cannot allocate memory\n");
			while (cmd_i)
			{
				cmd_i--;
				ft_free_cmd_elem(cmds[cmd_i]);
			}
			free(cmds);
			return (NULL);
		}
	}
	cmds[cmd_i]->cmd = END;
	return (cmds);
}
