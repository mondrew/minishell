#include "minishell.h"

char	*ft_add_dollar_to_res(char *res, int *i)
{
	if (!(res = ft_strjoin_free_left(res, "$")))
		return (NULL);
	(*i)++;
	return (res);
}

char	*ft_envvar_changer(char **help, char **envp, int *quotes, t_cmd **cmds)
{
	int		i;

	i = 0;
	while (help[0][i] != '\0')
	{
		if (!(help[1] = ft_add_bf_dollar_to_res(help[0], help[1], &i, quotes)))
			return (NULL);
		if (ft_is_only_dollar_sign(help[0], i))
		{
			if (!(help[1] = ft_add_dollar_to_res(help[1], &i)))
				return (NULL);
		}
		else if (help[0][i] && (help[0][i] == '$') && ((quotes[1] == 1) || \
											(!(quotes[0]) && (!(quotes[1])))))
		{
			if (!(help[1] = ft_replace_env(help, envp, &i, cmds)))
				return (NULL);
		}
		else if (help[0][i] && (help[0][i] == '$'))
		{
			if (!(help[1] = ft_add_dollar_to_res(help[1], &i)))
				return (NULL);
		}
	}
	return (help[1]);
}

char	*change_envs(char *str, char **envr, t_cmd **cmds)
{
	int		quotes[2];
	char	*res;
	char	**help;

	if (!(help = malloc(sizeof(char *) * 2)))
		return (ft_free_one_null(str));
	quotes[0] = 0;
	quotes[1] = 0;
	if (!(res = ft_strdup("")))
	{
		free(str);
		free(help);
		return (NULL);
	}
	help[0] = str;
	help[1] = res;
	if (!(res = ft_envvar_changer(help, envr, quotes, cmds)))
	{
		free(str);
		free(help);
		return (NULL);
	}
	free(str);
	free(help);
	return (res);
}

void	ft_skip_spaces(char *str, int *i, int quote)
{
	if (!quote)
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	else
		(*i)++;
}

void	ft_parse_quotes_for_spaces(char *str, int i, int *j)
{
	int		quote;

	quote = 0;
	*j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '\'' && !quote)
				quote = 1;
			else if (str[i] == '"' && !quote)
				quote = 2;
			else if ((str[i] == '\'' && quote == 1) ||
							(str[i] == '"' && quote == 2))
				quote = 0;
			i++;
		}
		else if (str[i] == ' ')
			ft_skip_spaces(str, &i, quote);
		else
			i++;
		(*j)++;
	}
}
