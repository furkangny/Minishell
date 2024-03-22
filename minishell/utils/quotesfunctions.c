/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:53:52 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/16 12:56:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quoteerror(t_data *data)
{
	char	*temp;

	if (check_quote(data->commandline,
			ft_strlen(data->commandline)) != 0)
	{
		temp = ft_strtrim(data->starttext, "\033[320m");
		printf("\033[31;4m%sQuote Error!\n\033[0m", temp);
		free(data->commandline);
		free(temp);
		data->commandline = NULL;
		data->errorstatus = 1;
		data->exitstatus = 1;
	}
}

int	check_quote(char *line, int control)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (line[i] && i <= control)
	{
		if (line[i] == '\'')
		{
			if (sign == 0)
				sign = 1;
			else if (sign == 1)
				sign = 0;
		}
		else if (line[i] == '\"')
		{
			if (sign == 0)
				sign = 2;
			else if (sign == 2)
				sign = 0;
		}
		i++;
	}
	return (sign);
}

char	*removequotes2(char *str)
{
	int		i;
	int		status;
	char	*returnvalue;
	int		j;

	returnvalue = malloc(ft_strlen(str) + 1);
	status = 0;
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && status == 1)
			status = 0;
		else if (str[i] == '\"' && status == 0)
			status = 1;
		else if (str[i] == '\'' && status == 2)
			status = 0;
		else if (str[i] == '\'' && status == 0)
			status = 2;
		else
			returnvalue[j++] = str[i];
	}
	returnvalue[j] = 0;
	return (returnvalue);
}

void	removequotes(t_data *data)
{
	int		i;
	char	*temp;
	char	**returnvalue;

	i = 0;
	returnvalue = malloc(sizeof(char *)
			* (commandpointerlen(data->arguments) + 1));
	while (data->arguments[i])
	{
		temp = data->arguments[i];
		returnvalue[i] = removequotes2(temp);
		free(temp);
		i++;
	}
	free(data->arguments[i]);
	free(data->arguments);
	returnvalue[i] = NULL;
	data->arguments = returnvalue;
}
