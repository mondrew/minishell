/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:07:51 by mondrew           #+#    #+#             */
/*   Updated: 2020/08/27 21:35:56 by mondrew          ###   ########.fr       */
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

/*
int		start_with_nospace(char *str, char *con)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && con[i])
	{
		if (str[i] != con[i])
			return (0);
		i++;
	}
	if (str[i] == '=' && con[i] == '\0')
		return (1);
	return (0);
}

char *get_line_env(char **env, char *param) // В отдельный файл
{
	while (*env)
	{
		if (start_with_nospace(*env, param))
			return (*env);
		env++;
	}
	return NULL;
}
*/

char *get_path(char **env)
{
	char *par;

	par = get_line_env(env, "PATH");
	return (par + 5);
}

char    **ft_make_paths_array(char **envp, char *command)
{
    char    **paths;
    char    *str;
    int     i;
    int     j;
    int     k;

    i = 0;
    if (!(paths = ft_split(get_path(envp), ':')))
        return (NULL);
    while (paths[i] != NULL)
    {
        j = 0;
        k = 0;
        if (!(str = malloc(sizeof(char) * (ft_strlen(paths[i]) + 1 + ft_strlen(command) + 1))))
        {
            ft_free_split(paths);
            return (NULL);
        }
        while (paths[i][j] != '\0')
        {
            str[j] = paths[i][j];
            j++;
        }
        if (paths[i][j - 1] != '/')
        {
            str[j] = '/';
            j++;
        }
        while (command[k] != '\0')
        {
            str[j] = command[k];
            j++;
            k++;
        }
        str[j] = '\0';
        free(paths[i]);
        paths[i] = str;
        str = NULL;
        i++;
    }
    return (paths);
}

t_cmd    **ft_free_cmds(t_cmd **cmds)
{
    int     i;

    i = 0;
    if (!cmds || !cmds[i])
        return (NULL);
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

int     ft_execute_in_parent(t_cmd **cmds, char ***envp)
{
	if ((*cmds)->cmd == CD)
    {
		if ((start_cd((*cmds)->str, *envp)) == -1)
            return (0);
    }
	else if ((*cmds)->cmd == EXPORT)
    {
		if ((start_export((*cmds)->str, envp)) == -1) // not finished! // done
            return (0);
    }
	else if ((*cmds)->cmd == UNSET) // done
    {
		if (!(start_unset((*cmds)->str, envp)))
            return (0);
    }
    else if ((*cmds)->cmd == EXIT)
    {
        ft_free_cmds(cmds);
        exit(0);
    }
    return (1);
}

int     ft_execve_cmd(t_cmd *cmds, t_cmd **cmds_big, char **envp)
{
    char    **array; // array for execve
    char    **paths; // paths from envp PATH
    char    *command; // current command
    int     i;

    i = 0;
    if (cmds->cmd == PWD)
    {
        start_pwd(cmds->str);
    }
	else if (cmds->cmd == ECHO)
    {
		if ((start_echo(cmds->str, envp)) == -1)
            return (0);
    }
	else if (cmds->cmd == CD)
		start_cd(cmds->str, envp);
	else if (cmds->cmd == EXPORT)
    {
		if (!(start_export(cmds->str, &envp))) // not finished!
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
    {
        ft_free_cmds(cmds_big);
        exit(0);
    }
    else if (cmds->cmd == UNKNOWN)
	{
        if (!(array = ft_split(cmds->str, ' ')))
            return (0);
        if (execve(array[0], array, envp) == -1) // нужно ли это вообще и когда это сработает? Для обычных executable?
        {
            command = array[0]; // save array[0]
            if (!(paths = ft_make_paths_array(envp, array[0])))
                return (ft_free_split(array));
            while (paths[i] != NULL)
            {
                array[0] = paths[i];
                if (execve(array[0], array, envp) == -1)
                {
                    i++;
                }
                else
                {
                    array[0] = command; // recover array[0]
                    break ;
                }
            }
            if (paths[i] == NULL)
            {
                // Command not found
                printf("%s: command not found\n", command); // add name of the error
                array[0] = command; // Recovet array[0]
                ft_free_split(paths);
                return (ft_free_split(array));
            }
            ft_free_split(paths);
        }
        ft_free_split(array);
    }
    return (1);
}

int     ft_simple_execute(t_cmd **cmds, char **envp)
{
    pid_t   pid;

    if ((pid = fork()) < 0)
    {
        printf("Error: fork failed\n");
        ft_free_cmds(cmds);
        return (-1);
    }
    if (pid == 0)
    {
        if (!ft_execve_cmd(cmds[0], cmds, envp))
        {
            //printf("Error: execution failed\n");
            ft_free_cmds(cmds);
            return (-1);
        }
        exit(0);
    }
    else
    {
        ft_free_cmd_elem(cmds[0]);
        waitpid(pid, 0, 0);
        return (1);
    }
    return (1);
}

int     ft_execute_with_pipes(t_cmd **cmds, int pipes, int input_from_file, char **envp)
{
    int     pipefd[pipes * 2];
    // int pipefd[pipes][2] // can change to that type - it is clearer
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
        ft_free_cmds(cmds);
        return (-1);
    }
    if ((pid = fork()) < 0)
    {
        printf("Error: fork failed\n");
        ft_free_cmds(cmds);
        return (-1);
    }
    if (pid == 0)
    {
        // Child
        if (input_from_file == 1) // can be separate function (to save place)
        {
            if ((fd = open(cmds[j + 1]->str, O_RDONLY)) == -1)
            {
                printf("Error: open failed\n");
                ft_free_cmds(cmds);
                return (-1); // Нужно послать сигнал в Parent (kill?), чтобы в parent-e проверить и сделать free, если нужно
            }
            dup2(fd, 0); // now input is from the file
            close(fd);
        }
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        if (!ft_execve_cmd(cmds[j], cmds, envp)) // if execve returns NULL .. Был !
        {
            ft_free_cmds(cmds);
            return (-1); // Нужно послать сигнал в Parent (kill?), чтобы в parent-e проверить и сделать free, если нужно
        }
        exit(0); // 
    }
    else
    {
        waitpid(pid, 0, 0); // &wstatus
        // Parent
        j++;
        if (input_from_file == 1) // to skip the second argument ("< filename")
        {
            close(fd); // это здесь не нужно.
            j++;
        }
    }
    // other pipes
    while (pipes > 1 && pid != 0) // pid != 0 guarantees us that all processes inside this "while" will proceed in Parent
    {
        if (pipe(pipefd + i) < 0)
        {
            printf("Error: pipe failed\n");
            ft_free_cmds(cmds);
            return (-1);
        }
        if ((pid = fork()) < 0)
        {
            printf("Error: fork failed\n");
            ft_free_cmds(cmds);
            return (-1);
        }
        if (pid == 0)
        {
            // Child
            close(pipefd[i - 1]); // close previous pipe write end
            dup2(pipefd[i - 2], STDIN_FILENO);
            close(pipefd[i - 2]);
            close(pipefd[i]); // close new pipe read end
            dup2(pipefd[i + 1], STDOUT_FILENO); // copy new pipe write end
            close(pipefd[i + 1]);
            if (!ft_execve_cmd(cmds[j], cmds, envp)) // был !
            {
                ft_free_cmds(cmds); // освободится лишь в child-е. Может в этом нет смысла?
                return (-1);
            }
            exit(0); // до сюда при успешном execve даже не дойдет. Проблема 100% в ft_execve_cmd, т.к. он должен посылать сигнал
                    // о завершении работы.
        }
        else
        {
            // Parent
            close(pipefd[i - 2]);
            close(pipefd[i - 1]);
            // close(pipefd[0]);
            // close(pipefd[1]);
            waitpid(pid, 0, 0); // &wstatus
            j++;
            i += 2;
            pipes--;   
        }
    }
    // This is the last after-pipe
    if (pid != 0) // to proceed in the Parent
    {
        if ((pid = fork()) < 0)
        {
            printf("Error: fork failed\n");
            ft_free_cmds(cmds);
            return (-1);
        }
        if (pid == 0)
        {
            // Child
            if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || cmds[j + 1]->status == RFWD))
            {
                if (cmds[j + 1]->status == RFWS) // for >
                {
                    if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
                    {
                        printf("Error: open failed\n");
                        ft_free_cmds(cmds);
                        return (-1);
                    }
                }
                else if (cmds[j + 1]->status == RFWD) // for >>
                {
                    if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
                    {
                        printf("Error: open failed\n");
                        ft_free_cmds(cmds);
                        return (-1);
                    }
                }
                dup2(fd, 1);
                close(fd);
            }
            close(pipefd[i - 1]); // close last pipe OUT
            dup2(pipefd[i - 2], STDIN_FILENO); // reads from last pipe read end
            close(pipefd[i - 2]);
            if (!ft_execve_cmd(cmds[j], cmds, envp)) // должен делать exit(0) в случае успеха
            {
                ft_free_cmds(cmds); // Нужно подать сигнал о неудаче родителю!
                return (-1);
            }
            exit(0); // exit(1) в случае неудачи
        }
        else
        {
            if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || cmds[j + 1]->status == RFWD))
                j++;
            close(pipefd[i - 2]);
            close(pipefd[i - 1]);
            waitpid(pid, 0, 0); // This is VERY important! Firstly close fds then wait for child // &wstatus
            i = j; // save j index
            while (j >= 0)
            {
                ft_free_cmd_elem(cmds[j]);
                j--;
            }
            return (i + 1);
        }
    }
    return (0);
}

int     ft_execute_with_redir(t_cmd **cmds, char **envp)
{
    int     fd;
    int     i;
    int     j; // for cmds indexing
    pid_t   pid;

    j = 0;
    if ((pid = fork()) < 0)
    {
        printf("Error: fork failed\n");
        ft_free_cmds(cmds);
        return (-1);
    }
    if (pid == 0)
    {
        // Child
        if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RBWS)
        {
            if ((fd = open(cmds[j + 1]->str, O_RDONLY)) == -1)
            {
                printf("Error: open failed\n");
                ft_free_cmds(cmds);
                return (-1);
            }
            dup2(fd, 0);
            close(fd);
            j++;
        }
        if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RFWS)
        {
            if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
            {
                ft_free_cmds(cmds);
                return (-1);
            }
            dup2(fd, 1);
            close(fd);
            j++; // there is no scense in doing it here
        }
        else if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RFWD)
        {
            if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
            {
                printf("Error: open failed\n");
                ft_free_cmds(cmds);
                return (-1);
            }
            dup2(fd, 1);
            close(fd);
            j++; // there is no scense in doing it here
        }
        if (!(ft_execve_cmd(cmds[0], cmds, envp)))
        {
            printf("Error: execution failed\n");
            ft_free_cmds(cmds);
            return (-1);
        }
        exit(0);
    }
    else
    {
        if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RBWS)
            j++;
        if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || cmds[j + 1]->status == RFWD))
            j++;
        waitpid(pid, 0, 0);
        i = j; // save i position
        while (j >= 0)
        {
            ft_free_cmd_elem(cmds[j]);
            j--;
        }
        return (i + 1);
    }
    return (0);
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

int     ft_execute(t_cmd **cmds, char **envp) // executes some cmds, frees executed cmds and moves the cmd pointer
{
    int     i;
    int     pipes;
    int     input_from_file;
    // Last one: $? <---- add it!

    i = 0;
    input_from_file = 0;
    if (cmds[i + 1]->cmd != END && cmds[i + 1]->status == RBWS) // check for the case "cmd < file | cmd ..."
        input_from_file = 1;
    // If there are pipes with CD command -> Just go to the ft_execute_with_pipes and it does nothing
    // If there is redirection with CD command -> Do "cd ~" in Parent and create empty file (> or >>) or do nothing (<)
    if ((cmds[i]->cmd == CD || cmds[i]->cmd == EXPORT || cmds[i]->cmd == UNSET 
        ||cmds[i]->cmd == EXIT) && (cmds[i + 1]->cmd == END))
    {
        if ((i = ft_execute_in_parent(cmds, &envp)) == -1)
            return (-1);
    }
    else if ((pipes = ft_check_pipes(cmds, input_from_file)) > 0)
    {
        if ((i = ft_execute_with_pipes(cmds, pipes, input_from_file, envp)) == -1)
            return (-1);
    }
    else if (ft_check_redirection(cmds))
    {
        if ((i = ft_execute_with_redir(cmds, envp)) == -1)
            return (-1);
    }
    else
    {
        if ((i = ft_simple_execute(cmds, envp)) == -1)
            return (-1);
    }
    return (i);
}

/*
char    *ft_strdup(char *str) // for testing
{
    char    *new;
    int     i;

    i = 0;
    while (str[i] != '\0')
        i++;
    if (!(new = malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = 0;
    while (str[i] != '\0')
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

int     main(int argc, char **argv, char **envp) // for testing
{
    t_cmd   **cmds;
    int     i;
    // grep test < newtest | cat -e
    // ls | cat -e | cat -e | cat -e
    // grep test < newtest | cat -e > file

    i = 0; // cmds counter;
    cmds = malloc(sizeof(t_cmd *) * 2);
    cmds[0] = malloc(sizeof(t_cmd) * 1);
    cmds[1] = malloc(sizeof(t_cmd) * 1);
    // cmds[2] = malloc(sizeof(t_cmd) * 1);
    // cmds[3] = malloc(sizeof(t_cmd) * 1);
    // cmds[4] = malloc(sizeof(t_cmd) * 1);
    // cmds[5] = malloc(sizeof(t_cmd) * 1);

    // 1. Command not found - treats not right! - double free or corruption (fasttop) !!!! FIX IT // done
    // 2. If "Command not found" - I should not do pipes??? check
    // 2.1 If command not found > redirection - I create empty file and print "Command not found" at the STDOUT
    // 3. CD, EXPORT, UNSET & EXIT нужно сделать в parent

    // cmds[0]->cmd = CD;
    // cmds[0]->status = NONE;
    // cmds[0]->str = ft_strdup("~");

    cmds[0]->cmd = UNSET;
    cmds[0]->status = NONE;
    // cmds[0]->str = ft_strdup("LOLO");
    cmds[0]->str = ft_strdup("HOME");

    //printf("RES: %s\n", cmds[0]->str);

    // cmds[1]->cmd = UNKNOWN;
    // cmds[1]->status = RBWS;
    // cmds[1]->str = ft_strdup("newtest");

    // cmds[1]->cmd = UNKNOWN;
    // cmds[1]->status = PIPE;
    // cmds[1]->str = ft_strdup("cat -e");

    // cmds[2]->cmd = UNKNOWN;
    // cmds[2]->status = PIPE;
    // cmds[2]->str = ft_strdup("cat -e");

    // cmds[3]->cmd = UNKNOWN;
    // cmds[3]->status = PIPE;
    // cmds[3]->str = ft_strdup("cat -e");

    // cmds[2]->cmd = UNKNOWN;
    // cmds[2]->status = RFWD;
    // cmds[2]->str = ft_strdup("file");

    cmds[1]->cmd = END;

    while ((cmds[i])->cmd != END)
    {
        if ((i = ft_execute(cmds, envp)) == -1)
        {
            return (-1);
        }
    }
    while (cmds[i]->cmd != END)
    {
        ft_free_cmd_elem(cmds[i]);
        i++;
    }
    free(cmds[i]);
    free(cmds);
    return (0);
}
*/