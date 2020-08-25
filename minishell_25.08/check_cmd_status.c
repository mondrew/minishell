#include "minishell.h"

int     check_cmd_status(char *line)
{
    int     i;
    int     status;

    i = 0;
    status = 0;
    if (start_with(line, ">"))
        return (RFWS);
    else if (start_with(line, ">>"))
        return (RFWD);
    else if (start_with(line, "<"))
        return (RBWS);
    else if (start_with(line, ";"))
        return (NONE);
    else if (start_with(line, "|"))
        return (PIPE);
    else
        return (NONE);
}
