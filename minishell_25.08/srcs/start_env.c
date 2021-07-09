#include "minishell.h"

int		start_env(char *line, char **envp)
{
	(void)line;
	while (envp && *envp)
	{
		ft_putstr(*envp);
		ft_putstr("\n");
		envp++;
	}
	return (0);
}
