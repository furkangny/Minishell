/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:55:04 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:55:05 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lessorgreatersign(char *a, int i, int m, t_data *data)
{
	a[1] = '\0';
	a[2] = '\0';
	if (data->commandline[i] == '<')
	{
		if (data->commandline[i + 1] == '<')
		{
			a[0] = '<';
			a[1] = '<';
			m = 2;
		}
		else
			a[0] = '<';
	}
	else
	{
		if (data->commandline[i + 1] == '>')
		{
			a[0] = '>';
			a[1] = '>';
			m = 2;
		}
		else
			a[0] = '>';
	}
	return (i + m);
}

int	elsestatus(char *a, int i, t_data *data)
{
	int		j;

	j = 0;
	while (data->commandline[i] && ((data->commandline[i] != ' '
				&& data->commandline[i] != '<'
				&& data->commandline[i] != '>'
				&& data->commandline[i] != '|')))
	{
		a[j++] = data->commandline[i++];
	}
	a[j] = '\0';
	return (i);
}

int	parserv2(int i, int argi, t_data *data)
{
	int		j;
	char	*a;

	a = malloc(ft_strlen(data->commandline) + 1);
	j = 0;
	if (data->commandline[i] == '\"')
		i = ifmultiquote(a, i, &j, data);
	else if (data->commandline[i] == '\'')
		i = ifsinglequote(a, i, &j, data);
	else if (data->commandline[i] == '<' || data->commandline[i] == '>')
		i = lessorgreatersign(a, i, 1, data);
	else if (data->commandline[i] == '|')
		i = pipecontrol(a, i, data);
	else
		i = elsestatus(a, i, data);
	data->arguments[argi] = ft_strdup(a);
	free(a);
	return (i);
}

void	continueparser(t_data *data, int i, int argi)
{
	data->arguments = malloc(
			ft_strlen(data->commandline) * sizeof(char *) + 1);
	while (data->commandline[i])
	{
		if (data->commandline[i] == ' ')
			i++;
		else
			i = parserv2(i, argi++, data);
	}
	data->arguments[argi] = NULL;
	errorcontrol(data, 0);
	if (data->parsererrorcode == 0)
	{
		if (ifdoubleinput(data))
			data->parsererrorcode = 2;
		else
			g_global.heredoc = 0;
	}
}

void	parser(t_data *data)
{
	int		i;
	int		argi;
	char	*temp;

	temp = ft_strdup(data->commandline);
	i = 0;
	argi = 0;
	free(data->commandline);
	data->commandline = ft_strtrim(temp, " ");
	if (data->commandline == NULL)
	{
		data->parsererrorcode = 1;
		return ;
	}
	free(temp);
	if (ifendispipe(data, 0) == 1)
		data->parsererrorcode = 3;
	else
		g_global.heredoc = 0;
	if (data->parsererrorcode == 0 && g_global.error == 0)
		continueparser(data, i, argi);
}
