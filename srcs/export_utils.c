#include "minishell.h"

void		show(char **envp)
{
	int i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			ft_putstr(envp[i]);
			ft_putstr("\n");
			i++;
		}
	}
}

char		**ft_free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char		**free_key_val_ret(char **key, char **val, char **ret)
{
	if (key)
		free(*key);
	if (val)
		free(*val);
	return (ret);
}

char		**ft_free_special_array(char **arr, int n)
{
	int i;

	i = 0;
	while (arr[i] && i < n)
	{
		free(arr[i]);
		i++;
	}
	if (i == n)
		i++;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char		**ft_copy_array(char **envp, int *ids)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (envp[i])
		i++;
	if (!(new_arr = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!(new_arr[i] = ft_strdup(envp[i])))
			return (ft_free_array(new_arr));
		i++;
	}
	new_arr[i] = NULL;
	ft_free_envp_null_ids(envp, ids);
	return (new_arr);
}
