#include "minishell.h"

void		free_chr(char **chr)
{
	if (chr && *chr)
	{
		free(*chr);
		*chr = NULL;
	}
}

char		*ft_find_lbreak(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (0);
}
