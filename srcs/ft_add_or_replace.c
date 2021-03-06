#include "minishell.h"

static char		**ft_replace_value(char **envp, char *value, int i, int *ids)
{
	char	**new_arr;
	int		j;

	j = 0;
	if (!(new_arr = ft_copy_array_no_free(envp)))
		return (NULL);
	free(new_arr[i]);
	while ((envp[i][j] != '=') && (envp[i][j]))
		j++;
	if (!(new_arr[i] = malloc(sizeof(char) * (j + 1 + ft_strlen(value) + 1))))
		return (ft_free_special_array(new_arr, i));
	j = 0;
	while (envp[i][j] != '=' && envp[i][j])
	{
		new_arr[i][j] = envp[i][j];
		j++;
	}
	new_arr[i][j] = '=';
	j++;
	while (*value)
		new_arr[i][j++] = *(value++);
	new_arr[i][j] = '\0';
	ft_free_envp_null_ids(envp, ids);
	return (new_arr);
}

static int		get_size_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

static char		**get_elem(char *value, char **new_arr, int i, char *key)
{
	char	*temp;

	new_arr[i] = NULL;
	if (value == NULL)
	{
		if (!(new_arr[i] = ft_strdup(key)))
			return (ft_free_array(new_arr));
	}
	else
	{
		if (!(temp = ft_strjoin(key, "=")))
			return (ft_free_array(new_arr));
		if (!(new_arr[i] = ft_strjoin(temp, value)))
		{
			free(temp);
			return (ft_free_array(new_arr));
		}
		free(temp);
	}
	return (new_arr);
}

static char		**ft_add_value(char *key, char *value, char **envp, int *ids)
{
	int		i;
	char	**new_arr;

	i = 0;
	if (!(new_arr = malloc(sizeof(char *) * (get_size_array(envp) + 2))))
		return (NULL);
	while (envp[i])
	{
		if (!(new_arr[i] = ft_strdup(envp[i])))
			return (ft_free_array(new_arr));
		i++;
	}
	if (!get_elem(value, new_arr, i, key))
		return (NULL);
	i++;
	new_arr[i] = NULL;
	ft_free_envp_null_ids(envp, ids);
	return (new_arr);
}

char			**ft_add_or_replace(char *key, char *value, char **envp, \
																	int *ids)
{
	int i;
	int j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '\0' && envp[i][j] != '=' && key[j] != '\0')
			if (envp[i][j] == key[j])
				j++;
			else
				break ;
		if ((envp[i][j] == '=' || envp[i][j] == '\0') && key[j] == '\0')
		{
			if (!value)
				return (ft_copy_array(envp, ids));
			else if (envp[i][j + 1] && !ft_strncmp(value, &envp[i][j + 1],
						ft_strlen(value) + 1))
				return (ft_copy_array(envp, ids));
			else
				return (ft_replace_value(envp, value, i, ids));
		}
		i++;
	}
	return (ft_add_value(key, value, envp, ids));
}
