/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:42:45 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:42:46 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*source;
	char	*dest;

	dest = (char *)dst;
	source = (char *)src;
	if (dst == 0 && src == 0)
		return (NULL);
	i = 0;
	if (dest > source)
	{
		while (len-- > 0)
		{
			dest[len] = source[len];
		}
	}
	else
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dest);
}
