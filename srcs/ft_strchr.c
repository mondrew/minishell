#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	unsigned int	i;

	ch = (unsigned char)c;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == ch)
			return (char*)(s + i);
		i++;
	}
	if (ch == '\0' && s[i] == '\0')
		return (char*)(s + i);
	return (NULL);
}
