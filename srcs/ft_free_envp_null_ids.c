#include "minishell.h"

void			ft_free_envp_null_ids(char **envp, int *ids)
{
	if (ids[1])
	{
		ft_free_split(envp);
		ids[1] = 0;
	}
}
