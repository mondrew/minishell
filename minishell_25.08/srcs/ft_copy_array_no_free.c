#include "minishell.h"

char		**ft_copy_array_no_free(char **envp)
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
	return (new_arr);
}
