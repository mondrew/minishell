#include "minishell.h"

static int			count_cmd(char *line)
{
	int		i;
	int		count;
	int		quote;

	i = 0;
	count = 1;
	quote = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			quote = ft_get_quote(line, i, quote);
		else if ((line[i] == '>' && line[i + 1] && line[i + 1] == '>'
		&& !quote))
		{
			count++;
			i++;
		}
		else if ((line[i] == ';' || line[i] == '>' || line[i] == '<' ||
		line[i] == '|') && !quote)
			count++;
		i++;
	}
	return (count);
}

static int			set_param(t_cmd **cmds, char *str, int cmd_id, int status)
{
	int		i;

	i = 0;
	(*cmds)->cmd = cmd_id;
	if (!((*cmds)->str = ft_strsdup(str, "><|;")))
		return (-1);
	(*cmds)->status = status;
	i = skip_non_printable(str);
	return (i + ft_strlen((*cmds)->str) - 1);
}

static int			host_parse(char *line, t_cmd **cmds, int cmd_i, int status)
{
	int		i;

	i = 0;
	if (start_with(line, "echo"))
		i = set_param(&cmds[cmd_i], line + 4, ECHO, status) + 4;
	else if (start_with(line, "cd"))
		i = set_param(&cmds[cmd_i], line + 2, CD, status) + 2;
	else if (start_with(line, "pwd"))
		i = set_param(&cmds[cmd_i], line + 3, PWD, status) + 3;
	else if (start_with(line, "export"))
		i = set_param(&cmds[cmd_i], line + 6, EXPORT, status) + 6;
	else if (start_with(line, "unset"))
		i = set_param(&cmds[cmd_i], line + 5, UNSET, status) + 5;
	else if (start_with(line, "env"))
		i = set_param(&cmds[cmd_i], line + 3, ENV, status) + 3;
	else if (start_with(line, "exit"))
		i = set_param(&cmds[cmd_i], line + 4, EXIT, status) + 4;
	else
		i = set_param(&cmds[cmd_i], line, UNKNOWN, status);
	return (i);
}

static int			pre_parse(char *line, int *i, int *status)
{
	*i += skip_non_printable(line + *i);
	if (line[*i])
		*status = check_cmd_status(line + *i);
	if (line[*i])
		*i += skip_status(line + *i);
	if (line[*i])
		*i += skip_non_printable(line + *i);
	if (!line[*i])
		return (0);
	return (1);
}

t_cmd				**parse_cmd(char *line)
{
	int		i;
	int		res;
	int		cmd_i;
	int		status;
	t_cmd	**cmds;

	i = 0;
	cmd_i = 0;
	status = NONE;
	if (!(cmds = malloc(sizeof(t_cmd) * (count_cmd(line) + 1))))
		return (NULL);
	if (!(cmds[0] = malloc(sizeof(t_cmd))))
		return (free_cmds2(0, cmds));
	while (line[i])
	{
		if (!(pre_parse(line, &i, &status)))
			break ;
		if ((res = host_parse(line + i, cmds, cmd_i++, status)) == -1)
			return (free_cmds2(cmd_i, cmds));
		i = i + res + 1;
		if (!(cmds[cmd_i] = malloc(sizeof(t_cmd))))
			return (free_cmds2(cmd_i, cmds));
	}
	cmds[cmd_i]->cmd = END;
	return (cmds);
}
