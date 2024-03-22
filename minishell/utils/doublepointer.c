/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublepointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:52:41 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/16 13:04:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**adddoublepointer(char **dp, char *add)
{
	int		i;
	char	**returndp;

	returndp = malloc(sizeof(char *) * (commandpointerlen(dp) + 2));
	i = 0;
	while (dp[i])
	{
		returndp[i] = ft_strdup(dp[i]);
		free(dp[i]);
		i++;
	}
	free(dp[i]);
	returndp[i] = ft_strdup(add);
	returndp[i + 1] = NULL;
	free(dp);
	return (returndp);
}

char	**removedoublepointerarg(char **dp, int i)
{
	int		j;
	int		rdpi;
	char	**returndp;

	returndp = malloc(sizeof(char *) * commandpointerlen(dp));
	rdpi = 0;
	j = 0;
	while (dp[j])
	{
		if (j != i)
		{
			returndp[rdpi] = ft_strdup(dp[j]);
			rdpi++;
		}
		free(dp[j]);
		j++;
	}
	free(dp[j]);
	returndp[rdpi] = NULL;
	free(dp);
	return (returndp);
}

int	exportparser(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	if (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	findenvpindex2(char *searchedenvp, t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (data->envp[i])
	{
		temp = ft_split(data->envp[i], '=');
		if (ft_strcmp(temp[0], searchedenvp) == 0)
		{
			freedoublepointer(temp);
			return (i);
		}
		if (temp)
			freedoublepointer(temp);
		i++;
	}
	return (-1);
}

void	freedoublepointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}
