#include "minishell.h"

void	sigint(int sig)
{
	ft_putstr("\n");
	print_prompt();
	(void)sig;
}

void	sigquit(int sig)
{
	ft_putstr("minishell: quit (core dumped)\n");
	(void)sig;
}

void	signotactive(int sig)
{
	(void)sig;
	return ;
}

void	sigintexec(int sig)
{
	(void)sig;
	ft_putstr("\n");
}
