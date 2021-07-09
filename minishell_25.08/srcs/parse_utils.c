#include "minishell.h"

int			skip_status(char *str)
{
	int i;

	i = 0;
	while (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
		i++;
	return (i);
}

int			ft_get_quote(char *line, int i, int quote)
{
	if (line[i] == '\'' && !quote)
		return (1);
	else if (line[i] == '"' && !quote)
		return (2);
	else if ((line[i] == '\'' && quote == 1) || (line[i] == '"' &&
			quote == 2))
		return (0);
	return (quote);
}

t_cmd		**free_cmds2(int cmd_i, t_cmd **cmds)
{
	while (cmd_i)
	{
		cmd_i--;
		ft_free_cmd_elem(cmds[cmd_i]);
	}
	free(cmds);
	return (NULL);
}
