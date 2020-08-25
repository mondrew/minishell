/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjessica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:00:50 by gjessica          #+#    #+#             */
/*   Updated: 2020/07/27 13:39:59 by gjessica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static int	get_count_dig(int sign, int n)
{
	int count_dig;

	count_dig = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		count_dig++;
	}
	if (sign == -1)
		count_dig++;
	return (count_dig);
}

static void	convert_int_to_char(char *res, int count_dig, int n)
{
	while (n > 9)
	{
		res[count_dig - 1] = (n % 10) + '0';
		n = n / 10;
		count_dig--;
	}
	res[count_dig - 1] = n + '0';
}

char		*ft_itoa(int n)
{
	int		count_dig;
	int		sign;
	char	*res;
	int		i;

	sign = get_sign(n);
	i = 0;
	if (n < 0 && n != -2147483648)
		n = -n;
	count_dig = get_count_dig(sign, n);
	res = malloc(count_dig * sizeof(char) + sizeof(char));
	if (res == NULL)
		return (NULL);
	if (sign == -1)
		res[i++] = '-';
	if (n == -2147483648)
	{
		res[i++] = '2';
		n = 147483648;
	}
	res[count_dig] = '\0';
	convert_int_to_char(res, count_dig, n);
	return (res);
}
