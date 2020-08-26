/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/28 16:46:03 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_strswap(char **strs, int i1, int i2)
{
	char		*tmp;

	tmp = strs[i1];
	strs[i1] = strs[i2];
	strs[i2] = tmp;

}

void sort_and_show(char **envp)
{
	int is_sort;
	int i;

	is_sort = 0;
	i = 0;
	while(envp[i] && envp[i + 1]) // можно было каждый раз начинать сначала, чтобы обойтись без рекурсии (mondrew)
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
		{
			ft_strswap(envp, i, i + 1);
			is_sort = 1;
		}
		i++;
	}
	if (is_sort)
		sort_and_show(envp);
	else
	{
		while (*envp)
		{
			ft_putstr(*envp);
			ft_putstr("\n");
			envp++;
		}
	}
}

/*

void remove_key(char *key, char **envp)
{
	//эту я написал кажется (mondrew)
}

void add_or_replace(char *key, char *value, char **envp) // и эту тоже написал (mondrew)
{
	// envp = //выглядит так
	// 	PATH=ghjghjg
	// 	KEY=kkljklj
	// 	PATH_1=jkljlk
	// 	KEY2=jknjkn
	// key = z // если в списке envp нет такого ключа, тогда
	// value = 123 // ему через равно без пробелов присвоить значение и добавить в конец envp
	// key = PATH // если есть, то значение ключа поменять на value
	
}
*/

int parse_and_add(char *line, char **envp)
{
	int i;
	int start_key;
	int start_val;
	int end_key;
	int end_val;

	i = 0; // лишняя, можно убрать (mondrew)
	start_key = -1;
	start_val = -1;
	end_key = -1;
	end_val = -1;
	i = skip_whitespace(line);
	//printf("%s %d\n", line, i);
	while (line[i])
	{
		if (start_key == -1 && line[i] != '=')
			start_key = i;
		else if (end_key == -1 && (line[i] == '=')  && i > 0)
			end_key = i;
		else if (start_key != -1 && end_key != -1 && start_val == -1 && i > 0 && line[i - 1] == '=')
			start_val = i;
		else if (start_key != -1 && end_key != -1 && start_val != -1 && line[i] == ' ')
			end_val = i;
		else if (start_key > -1 && end_key == -1 && line[i] == ' ') // а если эту переменную определили до вызова export? (mondrew) ??
		{
			printf ("minishell: bad assignment\n");
			start_key = -1;
			start_val = -1;
			end_key = -1;
			end_val = -1;
		}
		i++;
	//	printf("%d, %d, %d, %d\n",start_key, end_key, start_val, end_val);
		if (start_key > -1 && end_key > -1 && start_val > -1 && end_val > -1)
		{

		//	printf("NEW_PARAM\n");
			printf("%s = %s\n", ft_substr((line), start_key, end_key-start_key), ft_substr(line, start_val, end_val - start_val));
			// substr выделяет память с помощью malloc (mondrew)
			start_key = -1;
			start_val = -1;
			end_key = -1;
			end_val = -1;
			i += skip_whitespace(line + i);
		}
	}
	if (start_key > -1 && end_key > -1 && start_val > -1 && end_val == -1)
	{
		end_val = i;
		printf("%s = %s\n", ft_substr((line), start_key, end_key-start_key), ft_substr(line, start_val, end_val - start_val));
		// substr выделяет память с помощью malloc (mondrew)
	}
	// Функция недописана (mondrew)
	// В parse_and_add - в envp должна добавиться новая переменная окружения
	// parse_and_end будет выделать память под новую переменную - соответственно в случае ошибки при вызове malloc
	// нужно вернуть 0, чтобы в start_export отследить этот момент!
	return (1);
}

int start_export(char *line, char **envp)
{
	if (!line || !line[skip_whitespace(line)])
	{
		sort_and_show(envp);
	}
	else
	{
		if (!(parse_and_add(line, envp)))
			return (0);
	}

	// Непонятно, дописана ли эта функция
	// В parse_and_add мы используем malloc - соответственно, 
	// должны вернуть 0 в случае ошибки



	return(1);
}
