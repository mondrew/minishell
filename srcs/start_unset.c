#include "minishell.h"

char	**ft_free_arr(char **arr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_new_env_arr(char ***old, int i)
{
	char	**new;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (*old == NULL)
		return (NULL);
	while ((*old)[j] != NULL)
		j++;
	if (!(new = malloc(sizeof(char *) * j)))
		return (NULL);
	j = 0;
	while ((*old)[k] != NULL)
	{
		if (k != i)
		{
			if (!(new[j] = ft_strdup((*old)[k])))
				return (ft_free_arr(new, j));
			j++;
		}
		k++;
	}
	new[j] = NULL;
	return (new);
}

int		start_unset(char *line, char ***envp, int *ids)
{
	int		i;
	char	**new;

	i = 0;
	if (!(*line))
		return (1);
	while ((*envp)[i] != NULL)
	{
		if (!ft_strncmp(line, (*envp)[i], ft_strlen(line)) && \
							(!((*envp)[i][ft_strlen(line)]) || \
							((*envp)[i][ft_strlen(line)] == '=')))
			break ;
		i++;
	}
	if ((*envp)[i] != NULL)
	{
		if (!(new = ft_new_env_arr(envp, i)))
			return (0);
		ft_free_envp_null_ids(*envp, ids);
		ids[1] = 1;
		*envp = new;
	}
	return (1);
}
