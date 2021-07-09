#include "minishell.h"

int		ft_free_split(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

char	**ft_free_split_null(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	*ft_copy_without_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'')
		i++;
	if (!(new_str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**ft_remove_quotes_in_args(char **array)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (array && array[i])
		i++;
	if (!(new_arr = malloc(sizeof(char *) * (i + 1))))
	{
		ft_free_split(array);
		return (NULL);
	}
	i = 0;
	while (array[i])
	{
		if (!(new_arr[i] = ft_copy_without_quotes(array[i])))
		{
			ft_free_split(new_arr);
			ft_free_split(array);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	ft_free_split(array);
	return (new_arr);
}

char	*get_path(char **env)
{
	char	*par;

	if (!(par = get_line_env_mod(env, "PATH")))
		return (NULL);
	return (par + 5);
}
