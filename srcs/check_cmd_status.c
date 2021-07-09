#include "minishell.h"

int		check_cmd_status(char *line)
{
	if (start_with_special(line, ">>"))
		return (RFWD);
	else if (start_with_special(line, ">"))
		return (RFWS);
	else if (start_with_special(line, "<"))
		return (RBWS);
	else if (start_with_special(line, ";"))
		return (NONE);
	else if (start_with_special(line, "|"))
		return (PIPE);
	else
		return (NONE);
}
