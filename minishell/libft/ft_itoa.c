/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:12 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:38:14 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	numberlen(int n)
{
	long	a;
	int		i;

	i = 0;
	a = n;
	if (a == 0)
		return (1);
	if (a < 0)
	{
		a *= -1;
		i++;
	}
	while (a > 0)
	{
		a /= 10;
		i++;
	}
	return (i);
}

void	putstring(char *string, int a, int numlen)
{
	long	n;

	n = a;
	if (n < 0)
	{
		string[0] = '-';
		n *= -1;
	}
	if (n >= 10)
	{
		putstring(string, n / 10, numlen - 1);
		putstring(string, n % 10, numlen);
	}
	if (n < 10)
		string[numlen] = n + 48;
}

char	*ft_itoa(int n)
{
	int		numlen;
	char	*string;

	numlen = numberlen(n);
	string = malloc((sizeof(char) * numlen) + 1);
	if (!string)
		return (0);
	putstring(string, n, numlen - 1);
	string[numlen] = '\0';
	return (string);
}
