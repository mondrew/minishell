/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:08:52 by gjessica          #+#    #+#             */
/*   Updated: 2020/09/12 16:53:13 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 30
# define PATH_MAX 1024
# define FDS 14000

# define UNKNOWN 0
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define END 8

# define NONE 10
# define PIPE 11
# define RFWS 12
# define RFWD 13
# define RBWS 14

# define MALLOCFAIL 1
# define FORKFAIL 2
# define PIPEFAIL 3

# define MIDDLEPIPE 1
# define LASTPIPE 0

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_cmd
{
	int			cmd;
	int			status;
	char		*str;
}				t_cmd;

char			*ft_add_bf_dollar_to_res(char *str, char *res, int *i, \
																int *quotes);
char			**ft_add_command_to_paths(char **paths, char *command, \
																int i, int j);
char			*ft_add_dollar_to_res(char *res, int *i);
char			*ft_add_env_value(char *str, char *res, char *param, int *i);
char			**ft_add_or_replace(char *key, char *value, char **envp);
int				ft_atoi(char *str);
void			ft_change_child_fd_pipe(int *pipefd, int i, int id);
char			*change_envs(char *str, char **envr, t_cmd **cmds);
int				ft_check_all_quotes(char *str, int i, int *quotes);
int				check_cmd_status(char *line);
int				check_cmd_status(char *line);
int				ft_check_input_from_file(t_cmd **cmds);
int				ft_check_pipes(t_cmd **cmds, int input_from_file);
int				ft_check_redirection(t_cmd **cmds);
int				ft_close_fds_in_parent_pipe(int *pipefd, int i);
int				ft_cmd_nf(char *command, t_cmd **cmds, char **array, \
																pid_t pid);
char			*correct_echo_msg(char **str, char **envr, t_cmd **cmds);
char			**ft_copy_array(char **envp);
char			*ft_copy_without_quotes(char *str);
char			**ft_cpyarr(char **arr);
void			ft_cpy_set_null_backslash(char *new_str, char c, int *j, \
															int *backslash);
void			ft_cpy_with_quotes(char c, int *quote, int *i);
void			ft_cpy_with_whitespaces(char c, int quote, int *i);
char			**ft_cpyarr(char **arr);
char			*ft_envvar_changer(char **help, char **envp, int *quotes, \
																t_cmd **cmds);
int				ft_execute(t_cmd **cmds, char ***envp);
int				ft_execute_in_parent(t_cmd **cmds, char ***envp);
int				ft_execute_pipes(t_cmd **cmds, int pipes, int input_file, \
																char **envp);
int				ft_execute_with_redir(t_cmd **cmds, char **envp);
int				ft_execve_buildins_one(t_cmd *cmds, t_cmd **cmds_big, \
																char **envp);
int				ft_execve_buildins_two(t_cmd *cmds, t_cmd **cmds_big, \
																char **envp);
int				ft_execve_cmd(t_cmd *cmds, t_cmd **cmds_big, char **envp, \
																	pid_t pid);
int				ft_execve_unknown(t_cmd *cmds, t_cmd **cmds_big, \
													char **envp, pid_t pid);
char			*ft_exit_code_or_path(char *str, char *res, int *i, \
																t_cmd **cmds);
int				ft_first_pipe(int *pipefd, t_cmd **cmds, int input_file, \
																char **envp);
char			**ft_free_array(char **arr);
t_cmd			**ft_free_cmds(t_cmd **cmds);
t_cmd			**free_cmds2(int cmd_i, t_cmd **cmds);
void			ft_free_cmd_elem(t_cmd *cmds);
char			**free_key_val_ret(char **key, char **val, char **ret);
char			*ft_free_one_null(char *str);
char			*ft_free_two_null(char *s1, char *s2);
char			**ft_free_special_array(char **arr, int n);
int				ft_free_split(char **array);
char			**ft_free_split_null(char **array);
char			*get_cur_path();
int				ft_get_exit_code(t_cmd **cmds);
char			*get_line_env(char **env, char *param);
char			*get_path(char **env);
char			*get_path_name(char *str);
int				ft_get_quote(char *line, int i, int quote);
void			ft_goto_execve(t_cmd *cmds, t_cmd **cmds_big, char **envp, \
																	pid_t pid);
void			ft_goto_redirection(t_cmd **cmds, int j);
void			ft_input_from_file(t_cmd **cmds, int input_file, int j);
int				ft_is_buildin_first(int cmd);
int				ft_is_buildin_second(int cmd);
int				ft_is_env_name(char c);
int				ft_is_only_dollar_sign(char *str, int i);
int				ft_is_single_parent_function(t_cmd **cmds);
char			*ft_itoa(int n);
int				ft_last_pipe(int *pipefd, t_cmd **cmds, int j, char **envp);
int				launch_commands(char *line, char ***envp, int *exit_code);
int				ft_len_to_char(char *str, char end);
char			**ft_make_paths_array(char **envp, char *command);
int				ft_middle_pipe(int *pipefd, t_cmd **cmds, int j, char **envp);
void			ft_open_and_redirect(t_cmd **cmds, int j, int type);
void			ft_open_failed_and_exit(void);
int				ft_parent_wait(int pid, t_cmd **cmds, int j);
t_cmd			**parse_cmd(char *line);
void			ft_parse_quotes(char *str, int *i, int *single_quote, \
															int *double_quote);
void			ft_parse_quotes_for_spaces(char *str, int i, int *j);
void			ft_print_cmd_not_found(char *str);
void			print_prompt(void);
int				ft_print_set_exit_code(int error, t_cmd **cmds);
int				ft_putstr(char *s);
void			ft_redirection_to_file(t_cmd **cmds, int j);
char			*remove_bad_quotes(char *str);
char			*remove_bad_whitespaces(char *str);
char			**remove_key(char *key, char **envp);
char			**ft_remove_quotes_in_args(char **array);
char			*ft_replace_env(char **help, char **envp, int *i, \
															t_cmd **cmds);
void			ft_set_exit_code(t_cmd **cmds, int exit_code);
void			sigint(int sig);
void			sigintexec(int sig);
void			signotactive(int sig);
void			sigquit(int sig);
int				ft_simple_execute(t_cmd **cmds, char **envp);
void			show(char **envp);
void			ft_smart_cpy(char *str, char *new_str, int backslash, int *quote);
void			ft_smart_cpy_whitespaces(char *str, char *new_str, int i, int j);
void			ft_smart_double_quotes(char *new_str, char c, int *j, int *quote);
void			ft_smart_single_quotes(char *new_str, char c, int *j, int *quote);
int				ft_skip_env_key(char *param);
int				skip_non_printable(char *str);
void			ft_skip_spaces(char *str, int *i, int quote);
int				skip_status(char *str);
int				skip_whitespace(char *str);
char			**ft_split(char const *s, char c);
int				start_with(char *str, char *con);
int				start_with_special(char *str, char *con);
int				start_with_nospace(char *str, char *con);
int				start_cd(char *line, char **env, t_cmd **cmds);
int				start_echo(char *line, char **envr, t_cmd **cmds);
int				start_env(char *line, char **envp);
int				start_export(char *line, char ***envp, t_cmd **cmds);
int				start_pwd(char *line, t_cmd **cmds);
int				start_unknown_cmd(char *line, char **env);
int				start_unset(char *line, char ***envp);
char			*ft_str_to_res(char *str, char *res, int i, int k);
char			*ft_strcdup(char *str, char c);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free_both(char *s1, char *s2);
char			*ft_strjoin_free_left(char *s1, char *s2);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strsdup(char *str, char *set);
void			ft_strswap(char **strs, int i1, int i2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_treat_array(char **array, char **envp, t_cmd **cmds_big, \
																	pid_t pid);

/*
** GET NEXT LINE
*/

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_find_lbreak(char *s);
void			free_chr(char **chr);

#endif
