/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:56:32 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:56:33 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	findpath(char *searchedpath, t_data *data)
{
	int		i;
	char	*foundedpath;

	i = 0;
	while (data->path[i])
	{
		foundedpath = ft_strjoin2(data->path[i], "/");
		foundedpath = ft_strjoin(foundedpath, searchedpath);
		if (access(foundedpath, F_OK) == 0)
		{
			data->foundedpath = foundedpath;
			return (1);
		}
		i++;
		free(foundedpath);
	}
	return (0);
}

int	findpathindex(char *searchedpath, t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i])
	{
		if (!ft_strcmp(data->path[i], searchedpath))
			return (i);
		i++;
	}
	return (-1);
}

int	findenvpindex(char *searchedenvp, int searchindex, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], searchedenvp, searchindex) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	findexportindex(char *searchedexportp, int searchindex, t_data *data)
{
	int	i;

	i = 0;
	while (data->exportp[i])
	{
		if (ft_strncmp(data->exportp[i], searchedexportp, searchindex) == 0)
			return (i);
		i++;
	}
	return (-1);
}
