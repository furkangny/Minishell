/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:55:19 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:55:19 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ifendispipe2(t_data *data, int i)
{
	char	*temp;

	temp = NULL;
	while (data->commandline[i - 1] == '|')
	{
		g_global.heredoc = 1;
		temp = readline("> ");
		if (temp == NULL && g_global.error == 0)
			return (1);
		if (g_global.error == 1)
		{
			free(temp);
			return (0);
		}
		data->commandline = ft_strjoin(data->commandline, " ");
		data->commandline = ft_strjoin(data->commandline, temp);
		free(temp);
		temp = ft_strtrim(data->commandline, " ");
		free(data->commandline);
		data->commandline = ft_strdup(temp);
		i = ft_strlen(data->commandline);
		if (temp)
			free(temp);
	}
	return (0);
}

int	ifendispipe(t_data *data, int i)
{
	while (data->commandline[i])
		i++;
	if (data->commandline[--i] == '|')
	{
		while (--i != -1)
		{
			if (data->commandline[i] == '<' || data->commandline[i] == '|'
				|| data->commandline[i] == '>')
			{
				printf("Minishell: syntax error near unexpected token `|'\n");
				data->exitstatus = 258;
				return (1);
			}
			else if (data->commandline[i] != ' ')
				break ;
		}
		if (ifendispipe2(data, ft_strlen(data->commandline)))
		{
			g_global.heredoc = 0;
			return (1);
		}
	}
	return (0);
}

int	freedoubleinput(char *temp1, char *temp2, int status)
{
	if (status == 1)
	{
		free(temp2);
		return (status);
	}
	else if (status == 0)
	{
		free(temp1);
		free(temp2);
		return (status);
	}
	return (-1);
}

int	ifdoubleinput2(t_data *data, int i)
{
	char	*temp;
	char	*temp2;

	temp = ft_strdup("");
	temp2 = ft_strdup("");
	while (ft_strcmp(data->arguments[i], temp))
	{
		if (temp)
			free(temp);
		temp = readline("> ");
		if (temp == NULL)
			return (freedoubleinput(NULL, temp2, 1));
		if (g_global.error == 1)
			return (freedoubleinput(temp, temp2, 0));
		if (ft_strcmp(data->arguments[i], temp))
		{
			temp2 = ft_strjoin(temp2, temp);
			temp2 = ft_strjoin(temp2, "\n");
		}
	}
	free(data->arguments[i]);
	data->arguments[i] = ft_strdup(temp2);
	free(temp);
	free(temp2);
	return (0);
}

int	ifdoubleinput(t_data *data)
{
	int		i;

	i = 0;
	while (data->arguments[i])
	{
		if (!ft_strcmp(data->arguments[i], "<<") && data->arguments[i + 1])
		{
			g_global.heredoc = 1;
			i++;
			if (ifdoubleinput2(data, i))
				return (1);
			if (g_global.error == 1)
				return (0);
		}
		i++;
	}
	return (0);
}
