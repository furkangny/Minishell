/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:47 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:51:48 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isthere(char *str, t_data *data)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	while (data->envp[i])
	{
		temp = ft_split(data->envp[i], '=');
		if (ft_strcmp(temp[0], str) == 0)
			return (1);
		while (temp[j])
			free(temp[j++]);
		free(temp);
		j = 0;
		i++;
	}
	return (0);
}

void	sortexport(t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (data->exportp[i])
	{
		j = 0;
		while (data->exportp[j])
		{
			if (ft_strcmp(data->exportp[i], data->exportp[j]) < 0)
			{
				temp = data->exportp[i];
				data->exportp[i] = data->exportp[j];
				data->exportp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	isupdate2(char *str, int i, t_data *data)
{
	char	**temp;
	char	**temp2;
	int		j;

	while (--i != -1)
	{
		j = 0;
		temp = ft_split(str, '=');
		temp2 = ft_split(data->exportp[i], '=');
		if (ft_strchr(data->exportp[i], '='))
		{
			if (ft_strcmp(temp[0], temp2[0]) == 0)
				data->exportp = removedoublepointerarg(data->exportp, i);
		}
		else
			if (ft_strcmp(temp[0], data->exportp[i]) == 0)
				data->exportp = removedoublepointerarg(data->exportp, i);
		while (temp[j])
			free(temp[j++]);
		j = 0;
		while (temp2[j])
			free(temp2[j++]);
		free(temp);
		free(temp2);
	}
}

void	isupdate(char *str, int i, t_data *data)
{
	if (!ft_strchr(str, '='))
	{
		while (--i != -1)
		{
			if (ft_strcmp(data->exportp[i], str) == 0)
				data->exportp = removedoublepointerarg(data->exportp, i);
		}
		return ;
	}
	isupdate2(str, commandpointerlen(data->exportp), data);
	isupdate1helperforexport(data, str);
}

void	exportcommand(char **str, int i, int error, t_data *data)
{
	if (str[1])
	{
		while (str[++i])
		{
			if (exportparser(str[i]))
			{
				if (!isthere(str[i], data))
				{
					isupdate(str[i], commandpointerlen(data->exportp), data);
					if (ft_strchr(str[i], '='))
						data->envp = adddoublepointer(data->envp, str[i]);
					data->exportp = adddoublepointer(data->exportp, str[i]);
				}
			}
			else
				if (error == 0 && ++error == 1)
					printf("export: not valid in this context: %s\n", str[i]);
		}
	}
	sortexport(data);
	if (error == 0 && !str[1])
		printexport(data);
}
