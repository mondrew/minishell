/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:08:52 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/29 14:18:21 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H // MINISHELL_H (mondrew)
# define GET_NEXT_LINE_H // MINISHELL_H (mondrew)
# define BUFFER_SIZE 30

# define UNKNOWN 0
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define END 8

# define NONE 10 // new exec (first or after ';') (mondrew!)
# define PIPE 11 // |
# define RFWS 12 // >
# define RFWD 13 // >>
# define RBWS 14 // <


# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>

# define FDS 14000

typedef struct s_cmd
{
	int		cmd;
	int		status; // from 10 to 14 (mondrew!)
	char	*str;
} t_cmd;

typedef struct s_exec_cmd
{
	char *cmd;
	char **par;

} t_exec_cmd;

int ft_putstr(char *s);
t_cmd **parse_cmd(char *line);
char		*ft_itoa(int n);
char *ft_strcdup(char *str, char c);
int skip_non_printable(char *str);
int start_with(char *str, char *con);
int start_with_nospace(char *str, char *con);
int skip_whitespace(char *str);
char *get_cur_path();
int start_pwd(char *line);
int start_echo(char *line, char **envr);
int start_unknown_cmd(char *line, char **env);
int start_cd(char *line, char **env);
int start_unset(char *line, char ***envp); // added envp (mondrew)
int start_env(char *line, char **envp);
int start_export(char *line, char **envp);
char *get_line_env(char **env, char *param);
int ft_len_to_char(char *str, char end);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char *correct_echo_msg(char **str, char **envr);
int		ft_strcmp(const char *s1, const char *s2);
int     check_cmd_status(char *line);


/*
* GET NEXT LINE
*/

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_find_lbreak(char *s);
void			free_chr(char **chr);
char			*ft_strdup(char *str);
char			*ft_strjoin(char *s1, char *s2);
#endif

