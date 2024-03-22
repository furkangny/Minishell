/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:56:22 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/16 12:55:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commandfinderv2(t_data *data)
{
	int	i;

	i = 0;
	while (ft_strcmp(data->parts[i].type, "pipe") && data->parts[i + 1].type)
	{
		i++;
	}
	if (!ft_strcmp(data->parts[i].type, "pipe") && data->parts[i + 1].type)
	{
		ft_chiledfpi(&(data->parts[i - 1]), &(data->parts[i + 1]), data);
	}
	else
	{
		outputall(&(data->parts[0]), data);
	}
}

void	startprogram2(t_data *data)
{
	data->commandline = readline(data->starttext);
	if (!data->commandline)
		exit(0);
	if (ft_strcmp(data->commandline, ""))
		add_history(data->commandline);
	else
		free(data->commandline);
	quoteerror(data);
}

void	startprogram(t_data *data)
{
	while (1)
	{
		startprogram2(data);
		if (data->errorstatus == 0 && data->commandline[0])
		{
			parser(data);
			if (data->parsererrorcode == 0 && g_global.error == 0)
			{
				transformdollar(data, 0);
				data->exitstatus = 127;
				removequotes(data);
				data->parts = lastparse(data->arguments, 1, -1, data);
				commandfinderv2(data);
			}
			else if (data->parsererrorcode != 3 && g_global.error == 0)
			{
				printf("> bash: syntax error: unexpected end of file\n");
				data->exitstatus = 258;
			}
		}
		preparewhile(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	signal(SIGINT, ifsendsigint);
	signal(SIGQUIT, ifsendsigquit);
	remove_ctrl();
	initializefunction(envp, argc, argv, data);
	startprogram(data);
	return (0);
}
