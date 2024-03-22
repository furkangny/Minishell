/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:54:00 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/16 12:56:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redir(char **str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] && str[i][0] != '|')
	{
		if (str[i][0] == '<' || str[i][0] == '>')
			count++;
		i++;
	}
	return (count);
}

int	words_of_parts_outredir(char **argu)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (argu[i][0] == '|')
		return (1);
	while (argu[i])
	{
		if (argu[i][0] == '<' || argu[i][0] == '>')
		{
			count--;
			i++;
		}
		if (argu[i][0] == '|')
			return (count);
		i++;
		count++;
	}
	return (count);
}

int	redlen(t_red *red)
{
	int	i;

	i = 0;
	while (red[i].type)
	{
		i++;
	}
	return (i - 1);
}

void	ft_sub_output(t_parse *part, int i)
{
	int	fd;

	while (i + 1)
	{
		if (part->red[i].str[0] == '>' && part->red[i].str[1] == '>')
			fd = open(&(part->red[i].str[2]), O_CREAT, 0777);
		else if (part->red[i].str[0] == '>')
			fd = open(&(part->red[i].str[1]), O_CREAT, 0777);
		i--;
		close(fd);
	}
}
