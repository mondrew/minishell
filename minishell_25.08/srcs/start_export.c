/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:05:30 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/06 22:55:25 by gjessica         ###   ########.fr       */
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

void	sort_and_show(char **tenvp) // надо переписать. Она не должна менять порядок в envp, а только отображать его в алфавитном порядке!
									// env;export;env - первый и последний результат дб одинаковыми!!!
{
	char **envp;
	int is_sort;
	int i;

	envp = ft_cpyarr(tenvp);

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
		if (!envp[i + 1] && is_sort)
		{
			is_sort = 0;
			i = 0;
		}
	}
	i = 0;
	while (envp[i])
	{
		ft_putstr(envp[i]);
		ft_putstr("\n");
		i++;
	}
}

char	**parse_and_add(char *line, char **envp) // думаю тут нужно отправлять указатель на envp -> &envp
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	char	**new_envp;

	i = 0;
	j = 0;
	value = NULL;
	while (line[i] != '=' && line[i] != ' ' && line[i] != '\0')
		i++;
	if (!(key = malloc(sizeof(char) * (i + 1))))
	{
		printf("Error: cannot allocate memory\n");
		return (NULL);
	}
	ft_strlcpy(key, line, i + 1);
	if (line[i] == ' ' || line[i] == '\0')
	{
		if (!(new_envp = ft_add_or_replace(key, value, envp))) // have to return NULL
		{
			printf("Error: cannot allocate memory\n");
			free(key);
			return (NULL);
		}
		return (new_envp);
	}
	else if (line[i] == '=' && (line[i + 1] == '\0' || line[i + 1] == ' '))
	{
		if (!(new_envp = ft_add_or_replace(key, "", envp)))
		{
			printf("Error: cannot allocate memory\n");
			free(key);
			return (NULL);
		}
		return (new_envp);
	}
	else if (line[i] == '=')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (!(value = malloc(sizeof(char) * (i - j + 1))))
	{
		printf("Error: cannot allocate memory\n");
		free(key);
		return (NULL);
	}
	ft_strlcpy(value, &(line[j]), i - j + 1);
	if (!(new_envp = ft_add_or_replace(key, value, envp)))
	{
		printf("Error: cannot allocate memory\n");
		free(key);
		free(value);
		return (NULL);
	}
	free(key);
	free(value);
	return (new_envp);
}

/*
int		parse_and_add(char *line, char **envp)
{
	int i;
	int start_key;
	int start_val;
	int end_key;
	int end_val;

	i = 0;
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
*/

int		start_export(char *line, char ***envp)
{
	char	**new_envp;

	new_envp = NULL;
	if (!line || !line[skip_whitespace(line)])
	{
		sort_and_show(*envp);
		return (1);
	}
	else
	{
		if (!(new_envp = parse_and_add(line, *envp)))
			return (-1);
	}
	//ft_free_split(*envp); // It seems like envp from main is not allocated and can't be freed
	*envp = new_envp;
	return (1);
}
