/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_unknown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:04:17 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/29 14:06:38 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char **env)
{
	char *par;

	par = get_line_env(env, "PATH=");
	return (par+6); // мб +5? (mondrew)
}

int file_exists (char *filename) {
  struct stat   buffer;
  return (stat (filename, &buffer) == 0);
}

char **create_params(char *p1, char *p2)
{
	char **res;
	res = malloc(sizeof(res) * 3); // check if NULL (mondrew)
	res[0] = ft_strdup(p1); // check if NULL (mondrew)
	res[1] = ft_strdup(p2); // check if NULL (mondrew)
	res[2] = NULL;
	return res;
}

// pid = fork();
// 	if (pid > 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		execve(cmds[0], params[0], env);
// 		close(fd[1]);
// 		wait(0);

// 	} else {
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		pipe(fd2);
// 		pid = fork();
// 		if (pid > 0)
// 		{
// 			close(fd2[0]);
// 			dup2(fd2[1], STDOUT_FILENO);
// 			execve(cmds[1], params[1], env);
// 			close(fd2[1]);
// 			wait(0);

// 		} else {
// 			close(fd2[1]);
// 			dup2(fd2[0], STDIN_FILENO);
// 			execve(cmds[2], params[2], env);

// 		}
// 	}

void parent(int *fd, char *cmds, char **params, char **env)
{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(cmds, params, env);
		close(fd[1]);
		wait(0);
}

void child(int *fd, char *cmds, char **params, char **env)
{

}

void start_exec(char **env)
{

}

void start_exec3( char **env)
{
	char ***params;
	char **cmds;
	int WRITE_END = 1;
	int READ_END = 0;

	params = malloc(sizeof(params) * 5);
	cmds = malloc(sizeof(cmds) * 5);
	params[0] = create_params("ls", "-l");
	params[1] = create_params("cat", "-e");
	params[2] = create_params("grep", "27");
	params[3] = create_params("wc", "-c");
	params[4] = NULL;
	cmds[0] = ft_strdup("/bin/ls");
	cmds[1] = ft_strdup("/bin/cat");
	cmds[2] = ft_strdup("/usr/bin/grep");
	cmds[3] = ft_strdup("/usr/bin/wc");
	cmds[4] = NULL;

	pid_t pid; // чтобы делать pipe() - нужно 2 fork, соответственно 2 pid (pid и pid2) (mondrew)
	int fd[2] ;

	pipe(fd);
	pid = fork();
	if(pid==0)
	{
		// сначала нужно close(STDOUT_FILENO); // (mondrew)
		dup2(fd[WRITE_END], STDOUT_FILENO); // fd 0 = 1 // что это значит? (mondrew)
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		execve(cmds[0], params[0], env); //
		exit(1);
	}
	else
	{
	//	pipe(fd);
		wait(0);
		pid=fork();
		if(pid==0)
		{
			dup2(fd[READ_END], STDIN_FILENO);// fd 1 = 0(1) // что это значит? (mondrew)
			close(fd[WRITE_END]);
			close(fd[READ_END]);
			execve(cmds[1], params[1], env);//
			exit(1);
		}
		else
		{
				wait(0);
				pid = fork();

				int status;
				close(fd[READ_END]);
				close(fd[WRITE_END]);
				wait(0);

		}
}

}

void start_exec2( char **env)
{
	char ***params;
	char **cmds;

	params = malloc(sizeof(params) * 5);
	cmds = malloc(sizeof(cmds) * 5);
	params[0] = create_params("ls", "-l");
	params[1] = create_params("cat", "-e");
	params[2] = create_params("grep", "27");
	params[3] = create_params("wc", "-c");
	params[4] = NULL;
	cmds[0] = ft_strdup("/bin/ls");
	cmds[1] = ft_strdup("/bin/cat");
	cmds[2] = ft_strdup("/usr/bin/grep");
	cmds[3] = ft_strdup("/usr/bin/wc");
	cmds[4] = NULL;

	pid_t pid;

	int fd[2] ;
	//int fd2[2];
	int fd2 = open("test3.txt", O_RDWR | O_APPEND | O_CREAT);
	fd[0] = fd2;
	int status;
	pipe(fd);
	pid = fork();

	// pid = fork();
	if (pid > 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmds[0], params[0], env);

	} else {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		//pipe(fd);
		pid = fork();
		if (pid > 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve(cmds[1], params[1], env);


		} else {
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			execve(cmds[2], params[2], env);
			exit(1);

		}
		exit(1);
	//  if (pid == 0)
    // {
    //     dup2(fd[1], STDOUT_FILENO);
    //     close(fd[0]);
    //     close(fd[1]);
    //     execve(cmds[1], params[1], env);

    // } else {
    //     pid = fork();
    //     if(pid == 0)
    //     {
    //         dup2(fd[0], STDIN_FILENO);
    //         close(fd[1]);
    //         close(fd[0]);
    //         execve(cmds[2], params[2], env);

    //     }
    //     else
	// 	{
	// 		pid = fork();
	// 		if(pid == 0)
	// 		{
	// 			dup2(fd[1], STDOUT_FILENO);
	// 			close(fd[0]);
	// 			close(fd[1]);
	// 			execve(cmds[0], params[0], env);

	// 		}
	// 		else
	// 		{
	// 			int status;
	// 			close(fd[0]);
	// 			close(fd[1]);
	// 			waitpid(pid, &status, 0);
	// 		}
    //     }
    }
}

void show_arr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

int start_unknown_cmd(char *line, char **env)
{

	char	**param1;
	char	**param2;
	char	**paths;
	char	*fullfilename = ""; // not filename but command with options and parameters (mondrew)
	char	*fullfilename2 = "";
	int		is_exist;
	char	**comands; // commands (mondrew)
	int		i;

	// нужно сразу разделять на 2 массива: parsed и pipedparsed
	// а после парсить pipeparsed еще раз на наличие '|'
	// либо сразу посчитать количество '|' и сделать цикл
	is_exist = 0;
	i = 0;
	comands = ft_split((line + (skip_whitespace(line))), '|'); // if return NULL
	param1 = ft_split(comands[0], ' '); // if return NULL
	param2 = ft_split(comands[1], ' '); // if return NULL
	paths = ft_split(get_path(env), ':'); // if return NULL
	fullfilename = param1[0];

	// ft_free_split(comands); // (mondrew)
	
	while (paths[i])
	{
		if (file_exists(fullfilename))
		{
			is_exist = 1;
			break ;
		}
		fullfilename = ft_strdup(paths[i]);
		fullfilename = ft_strjoin(fullfilename, "/");
		fullfilename = ft_strjoin(fullfilename, param1[0]);
		i++;
	}
	// if (!is_exist)
	// {
	// 	printf("minishell: No such file or directory: %s\n", param1[0]);
	// } else {
	// 	start_exec(fullfilename, param1, env);
	// }

	//free(fullfilename);
	fullfilename2 = param2[0];
	i = 0;
	is_exist = 0;
	while (paths[i])
	{
		if (file_exists(fullfilename2))
		{
			is_exist = 1;
			break ;
		}
		fullfilename2 = ft_strdup(paths[i]);
		fullfilename2 = ft_strjoin(fullfilename2, "/");
		fullfilename2 = ft_strjoin(fullfilename2, param2[0]);
		i++;
	}
	if (!is_exist)
	{
		printf("minishell: No such file or directory: %s\n", param2[0]);
	} else {
		start_exec( env);
	}


	return(0);
}

int start_unknown_cmd2(char *line, char **env)
{
	pid_t pid;
	char **param1;
	char **param2;
	char **paths;
	char *filename;
	char *fullfilename = "";
	char **comands;
	int is_ok;

	is_ok = 0;
	comands = ft_split((line + (skip_whitespace(line))), '|');
	param1 = ft_split(comands[0], ' ');
	if (comands[1])
		param2 = ft_split(comands[1], ' ');
	paths = ft_split(get_path(env), ':'); // if return NULL
	pid = fork();
	if (pid == 0) // child (mondrew)
	{
		is_ok = 0;
		if (execve(param1[0], param1, env) == -1) // это если напрямую, без пути, не получилось?
		{
			fullfilename = ft_strdup(*paths);
			fullfilename = ft_strjoin(fullfilename, "/");
			fullfilename = ft_strjoin(fullfilename, param1[0]);
			while (*paths) // нужен индекс, т.к. под path выделилась память (ft_split),
							// как потом назад вернуться, чтобы ее free()? (mondrew)
			{
				execve(fullfilename, param1, env);
				if (errno == -1)
					printf(":command not found %d\n", errno); // И это будет печататься 
																// каждый раз, пока мы ищем нужный путь? (mondrew)
				paths++;
				fullfilename = ft_strdup(*paths); // предыдущий указатель fullfilename утерян, его нужно было free
				fullfilename = ft_strjoin(fullfilename, "/");
				fullfilename = ft_strjoin(fullfilename, param1[0]);
			}
			kill(pid, 0);
			printf(":command not found %d\n", errno);
		}



	} else if (pid < 0){
		printf("pid < 0 %s \n", param1[0]); // Error forking (mondrew)
	} else
		wait(&pid); // parent waits child to execute (mondrew)
	return (0);
}
