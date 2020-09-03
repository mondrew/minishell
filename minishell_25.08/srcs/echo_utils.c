/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <mondrew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 21:13:52 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/03 18:44:26 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_bad_quotes(char *str) // version made by mondrew. Seems it works
{
	char	*new;
	int		single_quote;
	int		double_quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
		{
			if (double_quote == 1)
				new[j++] = str[i];
			else if (single_quote == 1)
				single_quote = 0;
			else
				single_quote = 1;
		}
		else if (str[i] == '"' && str[i - 1] != '\\')
		{
			if (single_quote == 1)
				new[j++] = str[i];
			else if (double_quote == 1)
				double_quote = 0;
			else
				double_quote = 1;
		}
		else if (str[i] == '\\')
		{
			if (str[i - 1] == '\\')
				new[j++] = str[i];
		}
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

/*
char *remove_bad_quotes(char *str) // I've done my version (mondrew)
{
	char *res;
	int count; // why is it here? (mondrew)
	int i;
	int j;
	int open_quote;

	res = malloc(ft_strlen(str) + 1); // you've forgotten to check malloc!!! (mondrew)
	count = 0; // why is it here? (mondrew)
	i = 0;
	j = 0;
	open_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			count++; // why is it here? (mondrew)
		else if (str[i] == '"' && !open_quote && (!str[i + 1] || str[i + 1] != '$'))
			count++; // why is it here? (mondrew)
		else if (str[i] == '"' && open_quote == 1)
		{
				str[j] = str[i]; // may be res[j] = str[i] (mondrew)
				j++;
				open_quote = 0;
		}
		else if (str[i] == '"' && str[i+1] && str[i + 1] == '$')
		{
				str[j] = str[i]; // may be res[j] = str[i] (mondrew)
				j++;
				open_quote = 1;
		}
		else
		{
			str[j] = str[i]; // may be res[j] = str[i] (mondrew)
				j++;
		}
		i++;
	}
	str[j] = '\0'; // may be res[j] = '\0' (mondrew)
	return (str); // may be return (res) (mondrew)
}
*/

char	*get_path_name(char *str) // version made by mondrew // edited 01/09/2020
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	if (!(var = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	{
		var[i] = str[i];
		i++;
	}	
	var[i] = '\0';
	return (var); // should be free !
}

/*
char *get_path_name(char *str) // что она делает? возвращает путь или возвращает ИМЯ переменной среды (например HOME)?
{
	int i;

	i = 0;
	while (str[i] && str[i] != '"') // why it should end with '"'? Bad quotes has been deleted. (mondrew)
		i++;
	return ft_substr(str, 1, i - 1); // you didn't check return on NULL (mondrew)
}
*/

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s2);
	return (new);
}

char	*change_envs(char *str, char **envr) // mondrew 01.09.2020 // done
{
	int		i;
	int		j;
	int		k;
	int		single_quote;
	int		double_quote;
	char	*res;
	char	*tmp;
	char	*param;

	// На Linux если пишешь echo $fiuehf, где fiuehf - несуществующая переменная среды,
	// печатается пустая строка, т.е. str = "". Как на маке - не знаю

	// изначатьно res = strdup("");
	// цикл :
	// алгоритм: посчитать знаки $, выделить память под то, что до
	// В param поместить значение переменной окружения или пустую строку ""
	// strjoin_free_left
	// пропускаем $environname
	// повторяем цикл

	i = 0;
	single_quote = 0;
	double_quote = 0;
	if (!(res = ft_strdup("")))
	{
		printf("Malloc failed\n");
		return (NULL);
	}
	while (str[i] != '\0')
	{
		k = i;
		while (str[i] != '$' && str[i] != '\0')
		{
			// It can be one variable "quotes"
			if (str[i] == '\'')
			{
				if (single_quote)
					single_quote = 0;
				else if (double_quote)
					single_quote = 2; // "dsfds '$HOME' efewf"
				else
					single_quote = 1;
			}
			else if (str[i] == '"')
			{
				if (double_quote)
					double_quote = 0;
				else if (single_quote)
					double_quote = 2; // 'dsfds "$HOME" efewf'
				else
					double_quote = 1;
			}
			i++;
		}
		if (!(tmp = malloc(sizeof(char) * (i + 1))))
		{
			printf("Malloc failed\n");
			free(res);
			return (NULL);
		}
		//tmp = ft_strlcpy(tmp, &str[k], i);
		j = 0;
		while (str[k] != '$' && str[k] != '\0')
		{
			tmp[j] = str[k];
			j++;
			k++;
		}
		tmp[j] = '\0';
		if (!(res = ft_strjoin_free_both(res, tmp)))
			return (NULL);
		if (str[i] == '$' && (double_quote == 1 || (!double_quote && !single_quote)))
		{
			i++;
			if (!(tmp = get_path_name(&str[i])))
			{
				free(res);
				return (NULL);
			}
			if (!(param = get_line_env(envr, tmp)))
			{
				if (!(param = ft_strdup("")))
				{
					printf("Malloc failed\n");
					free(res);
					free(tmp);
					return (NULL);
				}
				free(tmp);
			}
			if (!(res = ft_strjoin_free_left(res, param + 5)))
				return (NULL);
			while ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || \
					(str[i] >= '0' && str[i] <= '9') || str[i] == '_')
				i++;
		}
		else
		{
			if (!(res = ft_strjoin_free_left(res, "$")))
			{
				printf("Malloc failed\n");
				return (NULL);
			}
			i++;
		}
	}
	return (res);
}

/*
char *change_envs(char *str, char **envr) // эта функция заменяет (например) $HOME на /path_to_home_dir/ ?
{
	int i;
	char *res;
	char *param;

	i = 0;
	res = ft_strdup(""); // you should check if malloc return NULL (mondrew)
	while (str[i])
	{
		if (str[i] == '"' && str[i + 1] && str[i + 1] == '$') // why str[i] == '"" ? (mondrew) -- for '$HOME'
		{
			param = get_line_env(envr, get_path_name(str + 1)); // get_path_name - возвращает указатель на выделенную malloc память
																// эту память нужно освободить. var = get_path_name(str + 1)
			printf("param %s\n", param); // is it here for debug? (mondrew)
			if (param != NULL)
				res = ft_strjoin(res, param + ft_strlen(get_path_name(str + 1))); // you should check if malloc return NULL (mondrew)
																				// вместо get_path_name использовать var (см. выше).
																				// кажется предыдущий res потерян. нужно free в strjoin
		}
		else if (str[i] != '"') // почему тут должны быть двойные кавычки " ?
			res[ft_strlen(res)] = str[i]; // мы до этого выделили под res память (ft_strdup) - здесь мы теряем этот указатель
											// в чем вообще смысл этого else if ?
		i++;
	}
	res[i] = '\0'; // зачем? ft_strjoin нуль-терминирует строку
	return res;
}
*/

char	*correct_echo_msg(char **str, char **envr)
{
	char *res;
	
	//if ()
	if (!(res = change_envs(*str, envr))) // if you do so => you should free previous res
	{
		free(*str);
		return (NULL);
	}
	if (!(res = remove_bad_quotes(res))) // you need to check if return value is not NULL (because of malloc in remove_bad_quotes) (mondrew)
	{
		free(*str);
		return (NULL);
	}
	free(*str);
	*str = res;
	return (res);
}
