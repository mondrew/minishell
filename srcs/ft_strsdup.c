#include "minishell.h"

static int	is_contains_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_new(char *str, int j, int i)
{
	int		k;
	char	*new_str;

	k = 0;
	while ((str[j - 1] == ' ') && (j != i))
		j--;
	k = j - i;
	if (!(new_str = malloc(sizeof(char) * (k + 1))))
		return (NULL);
	j = 0;
	while (j < k)
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void		ft_quotes_changer(char c, int *quote, int *j)
{
	if (c == '\'' && !(*quote))
		*quote = 1;
	else if (c == '"' && !(*quote))
		*quote = 2;
	else if ((c == '\'' && *quote == 1) || (c == '"' && *quote == 2))
		*quote = 0;
	(*j)++;
}

char		*ft_strsdup(char *str, char *set)
{
	int		i;
	int		j;
	int		quote;

	i = skip_non_printable(str);
	j = i;
	quote = 0;
	while (str[j])
	{
		if (str[j] == '"' || str[j] == '\'')
			ft_quotes_changer(str[j], &quote, &j);
		else if (is_contains_in_set(str[j], set) && !quote)
			break ;
		else
			j++;
	}
	return (ft_new(str, j, i));
}
