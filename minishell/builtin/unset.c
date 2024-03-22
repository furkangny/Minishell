/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:52:05 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:52:05 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unsetcommand(char **str, t_data *data)
{
	int	i;

	i = 0;
	if (commandpointerlen(str) == 1)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (str[++i])
	{
		if (exportparser(str[i]))
		{
			if (findenvpindex(str[i], ft_strlen(str[i]), data) != -1)
			{
				data->envp = removedoublepointerarg(data->envp,
						findenvpindex(str[i], ft_strlen(str[i]), data));
			}
			if (findexportindex(str[i], ft_strlen(str[i]), data) != -1)
				data->exportp = removedoublepointerarg(data->exportp,
						findexportindex(str[i], ft_strlen(str[i]), data));
		}
		else
			printf("bash: unset: `%s': not a valid identifier\n", str[i]);
	}
}
