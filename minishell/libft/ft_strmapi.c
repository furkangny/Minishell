/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:48:08 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:48:13 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*d;
	char			*m;
	unsigned int	i;

	m = (char *)s;
	d = (char *)malloc(sizeof(char) * (ft_strlen(m) + 1));
	i = 0;
	if (!d)
		return (NULL);
	while (m[i] && m)
	{
		d[i] = f(i, (char)m[i]);
		i++;
	}
	d[i] = '\0';
	return (d);
}
