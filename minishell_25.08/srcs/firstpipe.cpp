

void	ft_cpy_with_quotes(char c, int *quote, int *i)
{
	if (c == '\'' && !(*quote))
		*quote = 1;
	else if (c == '"' && !(*quote))
		*quote = 2;
	else if ((c == '\'' && *quote == 1) || (c == '"' && *quote == 2))
		*quote = 0;
	(*i)++;
}

void	ft_cpy_with_whitespaces(char c, int quote, int *i)
{
	if (!quote)
	{
		while (c == ' ')
			(*i)++;
	}
	else
		(*i)++;
}

void	ft_smart_cpy_whitespaces(char *str, char *new, int i, int j)
{
	int		quote;

	quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			new[j] = str[i];
			ft_cpy_with_quotes(str[i], &quote, &i);
		}
		else if (str[i] == ' ')
		{
			new[j] = str[i];
			ft_cpy_with_whitespaces(str[i], quote, &i);
		}
		else
		{
			new[j] = str[i];
			i++;
		}
		j++;
	}
	new[j] = '\0';
}
















/////////////////////////////////////////////////////////////
void	ft_skip_spaces(char *str, int *i, int quote)
{
	if (!quote)
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	else
		(*i)++;
}

void	ft_parse_quotes_for_spaces(char *str, int i, int *j, int *quote)
{
	*j = 0;
	*quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == '\'' && !(*quote))
				*quote = 1;
			else if (str[i] == '"' && !(*quote))
				*quote = 2;
			else if ((str[i] == '\'' && *quote == 1) || \
							(str[i] == '"' && *quote == 2))
				*quote = 0;
			i++;
		}
		else if (str[i] == ' ')
			ft_skip_spaces(str, &i, *quote);
		else
			i++;
		(*j)++;
	}
}
























/////////////////////////////////////////////////////////////////
void	ft_smart_single_quotes(char *new, char c, int *j, int *quote)
{
	if (quote[1] == 1)
	{
		*new = c;
		(*j)++;
	}
	else if (quote[0] == 1)
		quote[0] = 0;
	else
		quote[0] = 1;
}

void	ft_smart_double_quotes(char *new, char c, int *j, int *quote)
{
	if (quote[0] == 1)
	{
		*new = c;
		(*j)++;
	}
	else if (quote[1] == 1)
		quote[1] = 0;
	else
		quote[1] = 1;
}

void	ft_cpy_set_null_backslash(char *new, char c, int *j, int *backslash)
{
	new[*j] = c;
	(*j)++;
	*backslash = 0;
}

void	ft_smart_cpy(char *str, char *new, int backslash, int *quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
			ft_smart_single_quotes(&(new[j]), str[i], &j, quote);
		else if (str[i] == '"' && str[i - 1] != '\\')
			ft_smart_double_quotes(&(new[j]), str[i], &j, quote);
		else if (str[i] == '\\')
		{
			if (str[i + 1] == '\\' && backslash == 0)
				backslash = 1;
			else if (str[i - 1] == '\\' && backslash == 1)
				ft_cpy_set_null_backslash(&(new[j]), str[i], &j, &backslash);
		}
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
}


////////////////////////////////////////////////////////////////
char	*ft_free_two_null(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*ft_free_one_null(char *str)
{
	free(str);
	return (NULL);
}

int		ft_check_all_quotes(char *str, int i, int *quotes)
{
	int		single_quote;
	int		double_quote;

	single_quote = 0;
	double_quote = 0;
	while (str[i] != '$' && str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (single_quote)
				single_quote = 0;
			else if (double_quote)
				single_quote = 2;
			else
				single_quote = 1;
		}
		else if (str[i] == '"')
		{
			if (double_quote)
				double_quote = 0;
			else if (single_quote)
				double_quote = 2;
			else
				double_quote = 1;
		}
		i++;
	}
	if ((double_quote == 1) || (!double_quote && !single_quote))
		*quotes = 1;
	else
		*quotes = 0;
	return (i);
}

char	*ft_str_to_res(char *str, char *res, int i, int k)
{
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * (i - k + 1))))
		return (ft_free_one_null(res));
	tmp = ft_strlcpy(tmp, &str[k], i - k + 1);
	if (!(res = ft_strjoin_free_both(res, tmp)))
		return (NULL);
	return (res);
}

char	*ft_exit_code_or_path(char *str, char *res, int *i, t_cmd **cmds)
{
	char	*tmp;

	if (str[*i] && (str[*i] == '?'))
	{
		if (!(tmp = ft_itoa(ft_get_exit_code(cmds))))
			return (ft_free_one_null(res));
	}
	else if (!(tmp = get_path_name(&str[*i])))
		return (ft_free_one_null(res));
	return (tmp);
}

int		ft_is_env_name(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || \
		(c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

char	*ft_add_env_value(char *str, char *res, char *param, int *i)
{
	if (param)
	{
		if (!(res = ft_strjoin_free_left(res, param + ft_skip_env_key(param))))
			return (NULL);
		free(param);
		while (ft_is_env_name(str[*i]))
			(*i)++;
	}
	return (res);
}

char	*ft_replace_env(char *str, char *res, int *i, t_cmd **cmds)
{
	char	*tmp;
	char	*param;

	param = NULL;
	(*i)++;
	if (!(tmp = ft_exit_code_or_path(str, res, i, cmds)))
		return (NULL);
	if (str[*i] && (str[*i] == '?'))
	{
		if (!(res = ft_strjoin_free_both(res, tmp)))
			return (NULL);
		(*i)++;
	}
	else if (!(param = get_line_env(envr, tmp)))
	{
		if (!(param = ft_strdup("")))
			return (ft_free_two_null(res, tmp));
		free(tmp);
	}
	if (!(res = ft_add_env_value(str, res, param, i)))
		return (NULL);
	return (res);
}

int		ft_is_only_dollar_sign(char *str, int i)
{
	if (str[i] && (str[i] == '$') && \
		((str[i + 1] && (str[i + 1] == ' ')) || !str[i + 1]))
		return (1);
	return (0);
}

char	*ft_add_bf_dollar_to_res(char *str, char *res, int *i, int *quotes)
{
	int		k;

	k = *i;
	*i = ft_check_all_quotes(str, *i, quotes);
	if (!(res = ft_str_to_res(str, res, *i, k)))
		return (NULL);
	return (res);
}

char	*ft_add_dollar_to_res(char *res, int *i)
{
	if (!(res = ft_strjoin_free_left(res, "$")))
		return (NULL);
	(*i)++;
	return (res);
}

char	*ft_envvar_changer(char *str, char *res, int *quotes, t_cmd **cmds)
{
	int		i;
	int		k;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(res = ft_add_bf_dollar_to_res(str, res, &i, quotes)))
			return (NULL);
		if (ft_is_only_dollar_sign(str, i))
		{
			if (!(res = ft_add_dollar_to_res(res, &i)))
				return (NULL);
		}
		else if (str[i] && (str[i] == '$') && (*quotes))
		{
			if (!(res = ft_replace_env(str, res, &i, cmds)))
				return (NULL);
		}
		else if (str[i] && (str[i] == '$'))
		{
			if (!(res = ft_add_dollar_to_res(res, &i)))
				return (NULL);
		}
	}
	return (res);
}






































ft_execute
////////////////////////////////////////////////////////////////
int		ft_cmd_nf(char *command, t_cmd **cmds, char **array, pid_t pid)
{
	if (pid) // в первом случае (для ft_make_paths_array) этого не было
	{
		ft_putchar("-minishell: ");
		ft_putchar(command);
		ft_putchar(": command not found\n");
	}
	ft_set_exit_code(cmds, 127);
	return (ft_free_split(array));
}

int		ft_treat_array(char **array, char **envp, t_cmd **cmds_big, pid_t pid)
{
	char	*com;
	char	**path;
	int		i;

	i = 0;
	com = array[0];
	if (!(paths = ft_make_paths_array(envp, array[0])))
		return (ft_cmd_nf(com, cmds_big, array, pid));
	while (paths[i] != NULL)
	{
		array[0] = paths[i];
		if (execve(array[0], array, envp) == -1)
			i++;
		else
			break ;
	}
	array[0] = com;
	if (paths[i] == NULL)
	{
		ft_free_split(paths);
		return (ft_cmd_nf(com, cmds_big, array, pid));
	}
	return (1);
}

int		ft_execve_unknown(t_cmd *cmds, t_cmd **cmds_big, char **envp, pid_t pid)
{
	char	**array;

	if (!(array = ft_split(cmds->str, ' ')))
		return (0);
	if (!(array = ft_remove_quotes_in_args(array)))
		return (0);
	if (execve(array[0], array, envp) == -1)
	{
		if (!(ft_treat_array(array, envp, cmds_big, pid)))
			return (0);
		ft_free_split(paths);
	}
	ft_free_split(array);
	return (1);
}























///////////////////////////////////////////////////
if (ft_is_buildin_first(cmds->cmd))
	return (ft_execve_buildins_one(cmds, cmds_big, envp));
else if (ft_is_bildin_second(cmds->cmd))
	return (ft_execve_buildins_two(cmds, cmds_big, envp));

int		ft_is_buildin_first(int cmd)
{
	if ((cmds->cmd == PWD) || (cmds->cmd == ECHO) || \
		(cmds->cmd == CD) || (cmds->cmd == ENV))
		return (1);
	return (0);
}
int		ft_is_buildin_second(int cmd)
{
	if ((cmds->cmd == EXPORT) || (cmds->cmd == UNSET) || \
		(cmds->cmd == EXIT))
		return (1);
	return (0);
}

int		ft_execve_buildins_one(t_cmd *cmds, t_cmd **cmds_big, char **envp)
{
	if (cmds->cmd == PWD)
	{
		if ((start_pwd(cmds->str, cmds_big)) == -1)
			return (0);
	}
	else if (cmds->cmd == ECHO)
	{
		if ((start_echo(cmds->str, envp, cmds_big)) == -1)
			return (0);
	}
	else if (cmds->cmd == CD)
	{
		if ((start_cd(cmds->str, envp, cmds_big)) == -1)
			return (0);
	}
	else if (cmds->cmd == ENV)
		start_env(cmds->str, envp);
	return (1);
}

int		ft_execve_buildins_two(t_cmd *cmds, t_cmd **cmds_big, char **envp)
{
	int		exit_code;

	if (cmds->cmd == EXPORT)
	{
		if (!(start_export(cmds->str, &envp, cmds_big)))
			return (0);
	}
	else if (cmds->cmd == UNSET)
	{
		if (!(start_unset(cmds->str, &envp)))
			return (0);
	}
	else if (cmds->cmd == EXIT)
	{
		exit_code = ft_atoi(cmds->str);
		exit(exit_code);
	}
	return (1);
}















////////////////////////////////////////////////////
void	ft_open_and_redirect(t_cmd **cmds, int j, int type)
{
	int		fd;

	if (type == RBWS)
		fd = open(cmds[j + 1]->str, O_RDONLY);
	else if (type == RFWS)
		fd = open(cmds[j + 1]->str, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |\
				 S_IRGRP | S_IWUSR | S_IWGRP);
	else if (type == RFWD)
		fd = open(cmds[j + 1]->str, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |\
				 S_IRGRP | S_IWUSR | S_IWGRP);
	if (fd == -1)
	{
		ft_putstr("-minishell: ");
		ft_putstr(cmds[j + 1]->str);
		ft_putstr(": open failed\n");
		exit(1);
	}
	if (type == RBWS)
		dup2(fd, 0);
	else if ((type == RFWS) || (type == RFWD))
		dup2(fd, 1);
	close(fd);
}

void	ft_go_redirection(t_cmd **cmds, int j)
{
	if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RBWS)
	{
		ft_open_and_redirect(cmds, j, RBWS);
		i++;
	}
	if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RFWS)
		ft_open_and_redirect(cmds, j, RFWS);
	else if (cmds[j + 1]->cmd != END && cmds[j + 1]->status == RFWD)
		ft_open_and_redirect(cmds, j, RFWD);
}











///////////////////////////////////////////////////
void	ft_redirection_to_file(t_cmd **cmds, int j)
{
	int		fd;

	if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || \
		cmds[j + 1]->status == RFWD))
	{
		if (cmds[j + 1]->status == RFWS)
		{
			if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_TRUNC | O_CREAT, \
				S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
			{
				ft_putstr("Error: open failed\n");
				exit(1);
			}
		}
		else if (cmds[j + 1]->status == RFWD)
		{
			if ((fd = open(cmds[j + 1]->str, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP)) == -1)
			{
				ft_putstr("Error: open failed\n");
				exit(1);
			}
		}
		dup2(fd, 1);
		close(fd);
	}
}

int		ft_last_pipe(int *pipefd, t_cmd **cmds, int j, char **envp)
{
	pid_t	pid;
	int		i;

	i = (ft_check_pipes(cmds, ft_check_input_from_file(cmds))) * 2;
	if ((pid = fork()) < 0)
			return (ft_print_set_exit_code(FORKFAIL, cmds));
	if (pid == 0)
	{
		ft_redirection_to_file(cmds, j);
		ft_change_child_fd_pipe(pipefd, i, LASTPIPE);
		ft_goto_execve(cmds[j], cmds, envp, pid);
	}
	else
	{
		if (cmds[j + 1]->cmd != END && (cmds[j + 1]->status == RFWS || cmds[j + 1]->status == RFWD))
			j++;
		ft_close_fds_in_parent_pipe(pipefd, i);
		j = ft_parent_wait(pid, cmds, j);
	}
}



/////////////////////////////////////////////////////////////////////////

if ((j = ft_middle_pipe(pipefd, cmds, j, envp)) == -1)
	return (-1);

void	ft_change_child_fd_mid_pipe(int *pipefd, int i)
{
	close(pipefd[i - 1]);
	dup2(pipefd[i - 2], STDIN_FILENO);
	close(pipefd[i - 2]);
	close(pipefd[i]);
	dup2(pipefd[i + 1], STDOUT_FILENO);
	close(pipefd[i + 1]);
}

int		ft_close_fds_in_parent_mid_pipe(int *pipefd, int i)
{
	close(pipefd[i - 2]);
	close(pipefd[i - 1]);
	i += 2;
	return (i);
}

int		ft_middle_pipe(int *pipefd, t_cmd **cmds, int j, char **envp)
{
	pid_t	pid;
	int		pipes;
	int		i;

	i = 2;
	pipes = ft_check_pipes(cmds, ft_check_input_from_file(cmds));
	while (pipes > 1)// && pid != 0)
	{
		if (pipe(pipefd + i) < 0)
			return (ft_print_set_exit_code(PIPEFAIL, cmds));
		if ((pid = fork()) < 0)
			return (ft_print_set_exit_code(FORKFAIL, cmds));
		if (pid == 0)
		{
			ft_change_child_fd_mid_pipe(pipefd, i);
			ft_goto_execve(cmds[j], cmds, envp, pid);
		}
		else
		{
			i = ft_close_fds_in_parent_mid_pipe(pipefd, i);
			j = ft_parent_wait(pid, cmds, j);
			pipes--;
		}
	}
	return (j);
}






















///////////////////////////////////////////////////////////
void	ft_input_from_file(t_cmd **cmds, int input_file, int j)
{
	int		fd;

	if (input_file == 1)
	{
		if ((fd = open(cmds[j + 1]->str, O_RDONLY)) == -1)
		{
			printf("Error: open failed\n");
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
}

void	ft_goto_execve(t_cmd *cmds, t_cmd **cmds_big, char **envp, pid_t pid)
{
	if (!ft_execve_cmd(cmds, cmds_big, envp, pid))
	{
		if (ft_get_exit_code(cmds_big) == 127)
			exit(127);
		exit(1);
	}
	exit(0);
}

int		ft_parent_wait(int pid, t_cmd **cmds, int j)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	if (wstatus == 127 * 256)
	{
		ft_putstr(cmds[j]->str);
		ft_putstr(": command not found\n");
	}
	ft_set_exit_code(cmds, wstatus / 256);
	j++;
	return (j);
}

int		ft_first_pipe(int *pipefd, t_cmd **cmds, int input_file, char **envp)
{
	pid_t	pid;
	int		wstatus;
	int		j;

	j = 0;
	if (pipe(pipefd) < 0)
		return (ft_print_set_exit_code(PIPEFAIL, cmds));
	if ((pid = fork()) < 0)
		return (ft_print_set_exit_code(FORKFAIL, cmds));
	if (pid == 0)
	{
		ft_input_from_file(cmds, input_file, j);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_goto_execve(cmds[j], cmds, envp, pid);
	}
	else
	{
		j = ft_parent_wait(pid, cmds, j);
		if (input_file == 1)
			j++;
	}
	return (j);
}
