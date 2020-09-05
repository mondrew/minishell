/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:29:34 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/05 20:42:34 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_status(char *str)
{
	int i;

	i = 0;
	while (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
		i++;
	return (i);
}

int count_cmd(char *line) // What if there is pipe | or redirection > >> < between commands? (mondrew)
							// Функция считает количество комманд, разделенных ';'
{
	int i;
	int count;

	if (!line)
		return (0);
	i = 0;
	count = 1;

	while(line[i])
	{
		if ((line[i] == '>' && line[i + 1] && line[i + 1] == '>' ))
		{
			count++;
			i++;
		}
		else if (line[i] == ';' || line[i] == '>' || line[i] == '<' || line[i] == '|') // добавил все остальные случаи-разделители команд
			count++;
		i++;
	}
	return (count);
}

int		set_param(t_cmd **cmds, char *str, int cmd_id, int status)
{
	int		i;

	i = 0;
	(*cmds)->cmd = cmd_id;
	if (!((*cmds)->str = ft_strsdup(str, "><|;")))
		return (-1); // add treatment to the parse_cmd
	(*cmds)->status = status;
	i = skip_non_printable(str);
	//return(ft_strlen((*cmds)->str) > 0)? ft_strlen((*cmds)->str)-1 : 0;
	return (i + ft_strlen((*cmds)->str) - 1);
}

t_cmd	**parse_cmd(char *line)
{
	int		i;
	int		cmd_i;
	int		status;
	t_cmd	**cmds;

	// ls -l | cat -e >> test.txt
	i = 0;
	cmd_i = 0;
	status = NONE; // GJ change from 0 to NONE
	if (!(cmds = malloc(sizeof(t_cmd) * (count_cmd(line) + 1))))
		return (NULL);
	if (!(cmds[0] = malloc(sizeof(t_cmd))))
	{
		free(cmds);
		return (NULL);
	}
	while (line[i])
	{
		i += skip_non_printable(line + i);
		if (line[i])
			status = check_cmd_status(line + i); // (mondrew!)
		if (line[i])
			i += skip_status(line + i); // (mondrew!)
		if (line[i])
			i += skip_non_printable(line + i);
		if (!line[i]) // (mondrew!)
			break ; // case if we reach end of the line (mondrew!)
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
		status = NONE; // new GJ change to NONE // эта строчка не нужна
		if (!(cmds[cmd_i] = malloc(sizeof(t_cmd))))
		{
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

	//printf("cmd_i: %d\n", cmd_i);

	// Пояснение:
	// Получили 2-мерный массив с указателем на указатели на структуры
	// cmds[0]
	// cmds[1]
	// cmds[2]
	// могли бы сделать одинарный указатель - может переделать?
	// В каждой структуре: тип команды (int cmd), если это built-in команда, либо UNKNOWN, если внешняя
	// Если built-in команда, то в str находится аргумент, если это внешняя команда,
	// то в str - команда с аргументами
	// Также у каждой команды есть статус - показатель того, первая ли это команда на исполнение,
	// либо это команда после '|', '>', '<', '>>'. Если перед командой был ';' - то она считается снова первой
	return (cmds);
}
