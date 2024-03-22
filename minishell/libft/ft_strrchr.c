/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:48:44 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:48:44 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	int				res;
	unsigned char	*title;
	unsigned char	d;

	d = c;
	title = (unsigned char *)s;
	i = 0;
	res = -1;
	while (i != (ft_strlen((char *)title) + 1))
	{
		if (title[i] == d)
			res = i;
		i++;
	}
	if (res != -1)
		return ((char *)(s + (res * sizeof(char))));
	return (0);
}
