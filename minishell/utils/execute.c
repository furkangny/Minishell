/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:53:19 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/16 12:57:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	commanddetermination(char **str, t_data *data)
{
	if (ft_strcmp(str[0], "cd") == 0)
		cdcommand(str, data);
	else if (ft_strcmp(str[0], "echo") == 0)
		echocommand(str);
	else if (ft_strcmp(str[0], "env") == 0)
		envcommand(data);
	else if (ft_strcmp(str[0], "export") == 0)
		exportcommand(str, 0, 0, data);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwdcommand(data);
	else if (ft_strcmp(str[0], "unset") == 0)
		unsetcommand(str, data);
	else if (ft_strcmp(str[0], "exit") == 0)
		exitcommand();
	else
		ft_chiled(str, data);
}

void	commandfinderpipe(t_data *data)
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

void	addquote(char **arguments, int i)
{
	char	*temp;

	temp = ft_strjoin2("\"", arguments[i]);
	free(arguments[i]);
	arguments[i] = ft_strjoin(temp, "\"");
}

void	addstringhelper2(t_data *data, char *firststr, int argi, int startindex)
{
	int	i;

	i = -1;
	while (++i < startindex)
		firststr[i] = data->arguments[argi][i];
	firststr[i] = 0;
}

void	addstringhelper3(t_data *data, char *thirdstr, int argi, int endindex)
{
	int	i;

	i = 0;
	while (data->arguments[argi][endindex])
		thirdstr[i++] = data->arguments[argi][endindex++];
	thirdstr[i] = 0;
}
