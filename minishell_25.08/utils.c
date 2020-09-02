/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:30:44 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/02 13:49:24 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_line_env(char **env, char *param) // В отдельный файл. Функция возвращает указатель на строку в env с нужной переменной?
											// т.е. *env = "HOME=/path_to_home_dir/" ? (mondrew)
{
	while (*env)
	{
		if (start_with_nospace(*env, param))
			return (*env);
		env++;
	}
	return (NULL);
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


int skip_non_printable(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

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
	if (str[i] == '=' && (con[i] == ' ' || con[i] == '$' || con[i] == '\0')) // edited by mondrew 01/09/2020 echo eiufh$HOME$HOME
		return (1);
	return (0);
}

/*
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
*/

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


