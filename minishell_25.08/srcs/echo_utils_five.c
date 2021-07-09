#include "minishell.h"

int		ft_skip_env_key(char *param)
{
	int		i;

	i = 0;
	while (param[i] && param[i] != '=')
		i++;
	if (param[i])
		i++;
	return (i);
}

char	*ft_free_one_null(char *str)
{
	free(str);
	return (NULL);
}

char	*ft_free_two_null(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

void	ft_smart_single_quotes(char *new_str, char c, int *j, int *quote)
{
	if (quote[1] == 1)
	{
		*new_str = c;
		(*j)++;
	}
	else if (quote[0] == 1)
		quote[0] = 0;
	else
		quote[0] = 1;
}
