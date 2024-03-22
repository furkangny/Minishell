/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:55:11 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:55:12 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parserlongcontroller(int i, t_data *data)
{
	return (data->commandline[i] && data->commandline[i] != ' '
		&& data->commandline[i] != '<' && data->commandline[i] != '>'
		&& data->commandline[i] != '|');
}

int	pipecontrol(char *a, int i, t_data *data)
{
	a[0] = data->commandline[i];
	a[1] = '\0';
	return (++i);
}

int	ifmultiquote(char *a, int i, int *j, t_data *data)
{
	while (parserlongcontroller(i, data))
	{
		if (data->commandline[i] == '\"')
		{
			a[(*j)++] = data->commandline[i++];
			while (data->commandline[i] != '\"' && data->commandline[i])
				a[(*j)++] = data->commandline[i++];
			a[(*j)++] = data->commandline[i++];
		}
		if (data->commandline[i] == ' ' || data->commandline[i] == '<'
			|| data->commandline[i] == '>' || !data->commandline[i]
			|| data->commandline[i] == '|')
			break ;
		while (parserlongcontroller(i, data) && data->commandline[i] != '\"')
		{
			if (data->commandline[i] == '\'')
				i = ifsinglequote(a, i, j, data);
			else
				a[(*j)++] = data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}

int	ifsinglequote(char *a, int i, int *j, t_data *data)
{
	while (parserlongcontroller(i, data))
	{
		if (data->commandline[i] == '\'')
		{
			a[(*j)++] = data->commandline[i++];
			while (data->commandline[i] != '\'' && data->commandline[i])
				a[(*j)++] = data->commandline[i++];
			a[(*j)++] = data->commandline[i++];
		}
		if (data->commandline[i] == ' ' || data->commandline[i] == '<'
			|| data->commandline[i] == '>' || !data->commandline[i]
			|| data->commandline[i] == '|')
			break ;
		while (parserlongcontroller(i, data) && data->commandline[i] != '\'')
		{
			if (data->commandline[i] == '\"')
				i = ifmultiquote(a, i, j, data);
			else
				a[(*j)++] = data->commandline[i++];
		}
	}
	a[*j] = '\0';
	return (i);
}
