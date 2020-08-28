/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:01:27 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 15:02:39 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_path()
{
	char	cwd[PATH_MAX];

	// printf("17-get_cur_path-------------------------\n"); // почему это печатается 2 раза?
  	return (getcwd(cwd, sizeof(cwd)));
}

int		start_pwd(char *line)
{
	char	*path;

	// printf("13-start_pwd-------------------------\n");
	if (line && *(line + skip_whitespace(line)) != '\0') // pwd doesn't care about arguments. 
														// It works with any number of arguments. (only on Linux)
		ft_putstr("pwd: too many arguments");
	else
	{
		// printf("14-start_pwd-------------------------\n");
		if (!(path = get_cur_path()))
			printf("Error: pwd failed");
		else
		{
			// printf("15-start_pwd-------------------------\n");
			ft_putstr(path);
		}
	}
	ft_putstr("\n");
	// printf("16-start_pwd-------------------------\n");
	return (0);
}
