/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeforred.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:53:32 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/16 12:57:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**with_out_redir(char **str, int x)
{
	char	**new;
	int		i;
	int		j;

	(void)x;
	j = 0;
	i = 0;
	new = (char **)malloc(sizeof(char *) * words_of_parts_outredir(str) + 1);
	while (str[i] && str[i][0] != '|')
	{
		if (str[i][0] != '<' && str[i][0] != '>')
		{
			new[j] = ft_strdup(str[i]);
			j++;
		}
		else
			i++;
		i++;
	}
	new[j] = NULL;
	return (new);
}

int	check_redir(char **str)
{
	int	i;

	i = 0;
	while (str[i] && str[i][0] != '|')
	{
		if (str[i][0] == '<' || str[i][0] == '>'
			|| !ft_strcmp(str[i], "simpleoutput")
			|| !ft_strcmp(str[i], "simpleinput")
			|| !ft_strcmp(str[i], "multipleoutput")
			|| !ft_strcmp(str[i], "multipleinput"))
			return (1);
		i++;
	}
	return (0);
}

void	inputall(t_parse *part, t_data *data)
{
	int	i;

	if (check_redir(data->arguments) && part->red)
	{
		i = redlen(part->red);
		while (i + 1)
		{
			if (part->red[i].str[0] == '<' && part->red[i].str[1] == '<')
			{
				ft_multiple_left_redirection(&(part->red[i].str[2]),
					data, part);
				return ;
			}
			else if (part->red[i].str[0] == '<')
			{
				ft_odd_left_redirection(&(part->red[i].str[1]), data, part);
				return ;
			}
			i--;
		}
	}
	commanddetermination(part[0].str, data);
}

void	outputall(t_parse *part, t_data *data)
{
	int	i;

	if (check_redir(data->arguments) && part->red)
	{
		i = redlen(part->red);
		while (i + 1)
		{
			if (part->red[i].str[0] == '>' && part->red[i].str[1] == '>')
			{
				ft_multiple_right_redirection(&(part->red[i].str[2]),
					data, part);
				ft_sub_output(part, i - 1);
				return ;
			}
			else if (part->red[i].str[0] == '>')
			{
				ft_odd_right_redirection(&(part->red[i].str[1]), data, part);
				ft_sub_output(part, i - 1);
				return ;
			}
			i--;
		}
	}
	inputall(part, data);
}
