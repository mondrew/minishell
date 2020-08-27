/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:30:44 by gjessica          #+#    #+#             */
/*   Updated: 2020/08/27 09:32:10 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_line_env(char **env, char *param) // В отдельный файл. Функция возвращает указатель на строку в env с нужной переменной?
											// т.е. *env = "HOME=/path_to_home_dir/" ? (mondrew)
{
	while (*env)
	{
	//	printf("%s\n", *env);
		if (start_with_nospace(*env, param))
			return (*env);
		env++;
	}
	return NULL;
}

int ft_putstr(char *s)
{
	if (s != NULL)
		return write(1, s, ft_strlen(s));
	return (0);
}

int skip_whitespace(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}
int skip_status(char *str)
{
	int i;

	i = 0;
	while (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
		i++;
	return (i);
}

int skip_non_printable(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

/*
int		start_with_nospace(char *str, char *con) // made by mondrew
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return (0);
		i++;
	}
	if (str[i] == '=' && con[i] == '\0') // I guess it is important
		return (1);
	return (0);
}
*/

int start_with_nospace(char *str, char *con) // it is strncmp (mondrew) | что делает эта функция??
												// проверяет, совпадает ли имя переменной со списком переменных?
												// Тогда совпадение будет, когда в строке из списка переменных будет '=',
												// а в проверяемой строке - '\0'
{
	int i;

	i = 0;
	if (!str)
		return(0);
	while (str[i] && con[i]) // Эта ситуация может возникнуть, когда str = "HOME=/usr/path/", а con = "HOM"
	{
		if (str[i] != con[i])
			return(0);
		i++;
	}
	return (1);
}


int start_with(char *str, char *con) // it is strncmp, isn't it? (mondrew)
{
	int i;

	i = 0;
	if (!str)
		return(0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return(0);
		i++;
	}
	if (!con[i] && (!str[i] || str[i] == ' '))
		return (1);
	return (0);
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
		if ((line[i] == '>' && line[i+1] && line[i+1] == '>' ))
		{
			count++;
			i++;
		}
		if (line[i] == ';' || line[i] == '>' || line[i] == '<' || line[i] == '|') // добавил все остальные случаи-разделители команд
			count++;
		i++;
	}
	return (count);
}

char *ft_strcdup(char *str, char c)
{
	char			*dest;
	char			*temp;

	temp = (char *)malloc(sizeof(*dest) * (ft_strlen(str) + 1)); // sizeof(char) is the same (mondrew)
	if (!temp)
		return (NULL);
	dest = temp;
	while (*str && *str != c)
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (dest);
}

int set_param(t_cmd **cmd, char *str, int cmd_id, int status)
// int execve(const char *filename, char *const argv[], char *const envp[])
// argv должен содержать строки с параметрами, а первой строкой - путь.
{
	(*cmd)->cmd = cmd_id;
	// Можно посчитать кол-во символов до > >> < | ; и сделать ft_substr(str, start, len)
	(*cmd)->str = ft_strcdup(str, ';'); // CHANGE !!! ADD '>' '>>' '<' '|'//GJ DOIT
	//printf("%d: %s\n", (*cmd)->cmd, (*cmd)->str);
	(*cmd)->status = status;
	return(ft_strlen((*cmd)->str));
}

t_cmd **parse_cmd(char *line) // Считаю, что парсинг неправильный, т.к. команды могут разделяться не только ';'
								// но и '>' , '>>', '<' и '|'
								// edited
{
	int		i;
	int		cmd_i;
	int		status; // new
	t_cmd	**cmds; // Why pointer to pointer? May be t_cmd *cmds is enough? (mondrew)
					// Здесь сделан большой массив, т.к. cmds указывает на наборы команды, разделенные ';'
					// edited
	i = 0;
	cmd_i = 0;
	status = 0;
	if (!(cmds = malloc(sizeof(t_cmd*) * (count_cmd(line) + 1))))
		return (NULL);
	cmds[0] = malloc(sizeof(t_cmd)); // выделение памяти под первый набор команд (до первого ';', если он есть)
									// edited
	while (line[i])
	{
		i += skip_non_printable(line + i);
		status = check_cmd_status(line + i); // (mondrew!)
		i += skip_status(line + i); // (mondrew!)
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
		status = 0; // new
		cmds[cmd_i] = malloc(sizeof(t_cmd));
	}
	cmds[cmd_i]->cmd = END;
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
	return cmds;
}
