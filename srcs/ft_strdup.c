#include "minishell.h"

char		*ft_strdup(char *str)
{
	char	*dest;
	char	*temp;

	if (!str)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!temp)
		return (NULL);
	dest = temp;
	while (*str)
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (dest);
}
