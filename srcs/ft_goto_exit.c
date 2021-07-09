#include "minishell.h"

void	ft_goto_exit(t_cmd **cmds, char ***envp, char *line, int *ids)
{
	int		exit_code;

	exit_code = ft_atoi((*cmds)->str);
	ft_free_cmds(cmds - ids[0]);
	ft_free_envp_null_ids(*envp, ids);
	free(line);
	exit(exit_code);
}
