/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:07:51 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/24 16:00:56 by mondrew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_free_split(char **array)
{
    int     i;

    i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
    return (0);
}

t_cmd    **ft_free_cmds(t_cmd **cmds) //GJ return 1/0? int
{
    int     i;

    i = 0;
    while (cmds[i]->cmd != END)
    {
        free(cmds[i]->str);
        free(cmds[i]);
        i++;
    }
    free(cmds[i]);
    free(cmds);
    return (NULL);
}

void    ft_free_cmd_elem(t_cmd *cmds)
{
    free(cmds->str);
    free(cmds);
}

int     ft_execve_cmd(t_cmd *cmds, char **envp)
{
    char    **array;

    array = NULL;
    if (cmds->cmd == PWD)
		start_pwd(cmds->str);
	else if (cmds->cmd == ECHO)
		start_echo(cmds->str, envp);
	else if (cmds->cmd == CD)
		start_cd(cmds->str, envp);
	else if (cmds->cmd == EXPORT)
    {
		if (!(start_export(cmds->str, envp))) // not finished!
            return (0);
    }
	else if (cmds->cmd == UNSET)
    {
		if (!(start_unset(cmds->str, &envp)))
            return (0);
    }
	else if (cmds->cmd == ENV)
		start_env(cmds->str, envp);
	else if (cmds->cmd == EXIT)
		return (-1);
    else if (cmds->cmd == UNKNOWN)
	{
        if (!(array = ft_split(cmds->str, ' ')))
            return (0);
        if (!(execve(array[0], array, envp)))// return -1
        {
            ft_free_split(array);
            return (0);
        }
        ft_free_split(array);
    }
    return (1);
}

t_cmd     **ft_simple_execute(t_cmd **cmds, char **envp)
{
    pid_t   pid;
    int     i;
    int     ret;

    if ((pid = fork()) < 0)
    {
        printf("Error: fork failed\n");
        return (ft_free_cmds(cmds));
    }
    if (pid == 0)
    {
        ret = ft_execve_cmd(cmds[0], envp);
        if (!ret)
        {
            printf("Error: execution failed\n");
            return (ft_free_cmds(cmds));
        }
        else if (ret == -1)
        {
            ft_free_cmds(cmds);
            exit(0); // I'm not sure it's correct. Check it! (mondrew)
        }
    }
    ft_free_cmd_elem(cmds[0]);
    waitpid(pid, 0, 0);
    return (&cmds[1]);
}

t_cmd   **ft_execute_with_pipes(t_cmd **cmds, int pipes, int input_from_file, char **envp)
{
    // Check input from file in the first pipe
    // Check output to the file (> or >>) after the last pipe
    int     pipefd[pipes * 2];
// !!!!!!!!!!! GJ int pipefd[pipes][2]
    pid_t   pid;
    int     i; // for pipefd indexing
    int     j; // for cmds indexing
    int     fd;

    i = 2;
    j = 0;
    // first pipe
    if (pipe(pipefd) < 0)
    {
        printf("Error: pipe failed\n");
        return (ft_free_cmds(cmds));
    }
    if ((pid = fork()) < 0)
    {
        printf("Error: fork failed\n");
        return (ft_free_cmds(cmds));
    }
    if (pid == 0)
    {
        // Child
        if (input_from_file == 1) // can be separate function (to save place)
        {
            if ((fd = open(cmds[j + 1]->str, O_RDONLY)) == -1) // I suppose that str contains only string - path to filename
            {
                printf("Error: open failed\n");
                return (ft_free_cmds(cmds));
            }
            dup2(fd, 0); // now input is from the file
            if (close(fd) == -1)
            {
                // may be it is NOT nessecary!!!
                //GJ думаю не надо
                printf("Error: close failed\n");
                return (ft_free_cmds(cmds));
            }
        }
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        if (!ft_execve_cmd(cmds[j], envp)) // if execve returns NULL check -1
            return (ft_free_cmds(cmds));
        j++;
        if (input_from_file == 1) // to skip the second argument ("< filename")
        {
            if (close(fd) == -1)
            {
                // may be it is NOT nessecary!!!
                printf("Error: close failed\n");
                return (ft_free_cmds(cmds));
            }
            j++;
        }
        // execve();
    }
    while (pipes > 1)
    {
        if (pipe(pipefd + i) < 0)
        {
            printf("Error: pipe failed\n");
            return (ft_free_cmds(cmds));
        }
        if ((pid = fork()) < 0)
        {
            printf("Error: fork failed\n");
            return (ft_free_cmds(cmds));
        }
        if (pid == 0)
        {
            close(pipefd[i - 1]); // close previous pipe write end
            dup2(pipefd[i - 2], STDIN_FILENO);
            close(pipefd[i - 2]);
            close(pipefd[i]); // close new pipe read end
            dup2(pipefd[i + 1], STDOUT_FILENO); // copy new pipe write end
            close(pipefd[i + 1]);
            if (!ft_execve_cmd(cmds[j], envp))
                return (ft_free_cmds(cmds));
            j++;
            // execve();
        }
        i += 2;
        pipes--;
    }
    // This is the last after-pipe
    // I should check whether next cmds[j] is REDIRECTION or not !!!
    if ((pid = fork()) < 0)
    {
        printf("Error: fork failed\n");
        return (ft_free_cmds(cmds));
    }
    if (pid == 0)
    {
        // Child
        if (cmds[j + 1]->status == RFWS || cmds[j + 1]->status == RFWD)
        {
            if (cmds[j + 1]->status == RFWS) // for >
            {
                if ((fd = open(cmds[j + 1]->str, O_CREAT | O_WRONLY | O_TRUNC | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
                {
                    printf("Error: open failed\n");
                    return (ft_free_cmds(cmds));
                }
            }
            else if (cmds[j + 1]->status == RFWD) // for >>
            {
                if ((fd = open(cmds[j + 1]->str, O_CREAT | O_WRONLY | O_APPEND | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
                {
                    printf("Error: open failed\n");
                    return (ft_free_cmds(cmds));
                }
            }
            dup2(fd, 1);
            if (close(fd) == -1) // may be it is NOT nessecary!!!
            {
                printf("Error: close failed\n");
                return (ft_free_cmds(cmds));
            }
        }
        close(pipefd[i - 1]); // close last pipe OUT
        dup2(pipefd[i - 2], STDIN_FILENO); // reads from last pipe read end
        close(pipefd[i - 2]);
        if (!ft_execve_cmd(cmds[j], envp))
            return (ft_free_cmds(cmds));
        if (cmds[j + 1]->status == RFWS || cmds[j + 1]->status == RFWD)
            j++;
        // free all that has been execed

        // execve();
    }
    //here I close all pipefds in parent
    i--; // вернул индекс на последний элемент масссива pipefd[]
    while (i >= 0)
    {
        close(pipefd[i]);
        i--;
    }
    waitpid(-1, 0, 0); // parent waits for all childs
    i = j; // save j index
    while (j >= 0)
    {
        ft_free_cmd_elem(cmds[j]);
        j--;
    }
    return (&cmds[i + 1]);
}

t_cmd   **ft_execute_with_redir(t_cmd **cmds, char **envp)
{
    int     fd;
    int     i;
    int     j;
    pid_t   pid;

    i = 0;
    if ((pid = fork()) < 0)
    {
        printf("Error: fork failed\n");
        return (ft_free_cmds(cmds));
    }
    if (pid == 0)
    {
        // Child
        if (cmds[i + 1]->status == RBWS)
        {
            if ((fd = open(cmds[i + 1]->str, O_RDONLY)) == -1)
            {
                // may be check on -1 is not necessary
                printf("Error: open failed\n");
                return (ft_free_cmds(cmds));
            }
            dup2(fd, 0);
            if (close(fd) == -1)
            {
                printf("Error: close failed\n");
                return (ft_free_cmds(cmds));
            }
            i++;
        }
        if (cmds[i + 1]->status == RFWS)
        {
            if ((fd = open(cmds[i + 1]->str, O_CREAT | O_TRUNC | O_WRONLY | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
            {
                printf("Error: open failed\n");
                return (ft_free_cmds(cmds));
            }
            dup2(fd, 1);
            if (close(fd) == -1)
            {
                printf("Error: close failed\n");
                return (ft_free_cmds(cmds));
            }
            i++;
        }
        else if (cmds[i + 1]->status == RFWD)
        {
            if ((fd = open(cmds[i + 1]->str, O_CREAT | O_APPEND | O_WRONLY | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
            {
                printf("Error: open failed\n");
                return (ft_free_cmds(cmds));
            }
            dup2(fd, 1);
            if (close(fd) == -1)
            {
                printf("Error: close failed\n");
                return (ft_free_cmds(cmds));
            }
            i++;
        }
        if (!(ft_execve_cmd(cmds[0], envp)))
        {
            printf("Error: execution failed\n");
            return (ft_free_cmds(cmds));
        }
    }
    waitpid(pid, 0, 0);
    j = i; // save i position
    while (i >= 0)
    {
        ft_free_cmd_elem(cmds[i]);
        i--;
    }
    return (&cmds[j + 1]);
}

int     ft_check_pipes(t_cmd **cmds, int input_from_file)
{
    int     i;
    int     pipes;

    i = 0;
    pipes = 0;
    if (input_from_file == 1)
        i = 1;
    while (cmds[i + 1]->cmd != END && cmds[i + 1]->status == PIPE)
    {
        pipes++;
        i++;
    }
    return (pipes);
}

int     ft_check_redirection(t_cmd **cmds)
{
    int     i;

    i = 0;
    if (cmds[i + 1]->status == RBWS)
    {
        if (cmds[i + 2]->status == RFWS) // cmd < file1 > file2
            return (RBWS + RFWS);
        else if (cmds[i + 2]->status == RFWD) // cmd < file1 >> file2
            return (RBWS + RFWD);
        else
            return (RBWS); // cmd < file1
    }
    else if (cmds[i + 1]->status == RFWS || cmds[i + 1]->status == RFWD)
        return (cmds[i + 1]->status); // cmd > file || cmd >> file
    return (0);
}

t_cmd    **ft_execute(t_cmd **cmds, char **envp) // executes some cmds, frees executed cmds and moves the cmd pointer
{
    int     i;
    int     pipes;
    int     input_from_file;

    i = 0;
    input_from_file = 0;
    if (cmds[i + 1]->status == RBWS) // check for the case "cmd < file | cmd ..."
        input_from_file = 1;
    if ((pipes = ft_check_pipes(cmds, input_from_file)) > 0)
    {
        if (!(cmds = ft_execute_with_pipes(cmds, pipes, input_from_file, envp)))
            return (NULL);
        return (cmds);
    }
    else if (ft_check_redirection(cmds))
    {
        if (!(cmds = ft_execute_with_redir(cmds, envp)))
            return (NULL);
        return (cmds);
    }
    else
    {
        if (!(cmds = ft_simple_execute(cmds, envp)))
            return (NULL);
        return (cmds);
    }
    return (cmds);
}
