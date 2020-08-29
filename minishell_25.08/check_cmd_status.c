#include "minishell.h"

int     check_cmd_status(char *line)
{
    int     status;

    status = NONE;
    if (start_with(line, ">>"))
        return (RFWD);
    else if (start_with(line, ">")) // GJ Поменял местами, иначе никогда не определится RFWD
        return (RFWS);
    else if (start_with(line, "<"))
        return (RBWS);
    else if (start_with(line, ";"))
        return (NONE);
    else if (start_with(line, "|"))
        return (PIPE);
    else
        return (NONE);
}
