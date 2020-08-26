/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mondrew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2020/05/02 12:58:52 by mondrew           #+#    #+#             */
/*   Updated: 2020/05/06 16:35:42 by mondrew          ###   ########.fr       */
=======
/*   Created: 2020/04/30 19:41:28 by gjessica          #+#    #+#             */
/*   Updated: 2020/08/25 20:45:51 by gjessica         ###   ########.fr       */
>>>>>>> 4381a050290f041c0f67432aceaaf8befd8fcac2
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
<<<<<<< HEAD
	while (*s1 != '\0' && *s1 == *s2 && *s2 != '\0' && n > 1)
=======
	s1t = (unsigned char*)s1;
	s2t = (unsigned char*)s2;
	i = 0;
	while (i < n)
>>>>>>> 4381a050290f041c0f67432aceaaf8befd8fcac2
	{
		s1++;
		s2++;
		n--;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}
