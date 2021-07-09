#include "minishell.h"

char	*get_line_env_mod(char **env, char *param)
{
	while (*env)
	{
		if (start_with_nospace(*env, param))
			return (*env);
		env++;
	}
	return (NULL);
}

char	*get_line_env(char **env, char *param)
{
	char	*res;

	while (*env)
	{
		if (start_with_nospace(*env, param))
		{
			if (!(res = ft_strdup(*env)))
			{
				ft_putstr("Error: cannot allocate memory\n");
				return (NULL);
			}
			return (res);
		}
		env++;
	}
	return (NULL);
}

int		ft_putstr(char *s)
{
	if (s != NULL)
		return (write(1, s, ft_strlen(s)));
	return (0);
}

int		skip_whitespace(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int		skip_non_printable(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}
