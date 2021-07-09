#include "minishell.h"

void		ft_set_exit_code(t_cmd **cmds, int exit_code)
{
	int		i;

	i = 0;
	while (cmds && cmds[i]->cmd != END)
		i++;
	cmds[i]->status = exit_code;
}

int			ft_get_exit_code(t_cmd **cmds)
{
	int		i;

	i = 0;
	while (cmds && cmds[i]->cmd != END)
		i++;
	return (cmds[i]->status);
}
