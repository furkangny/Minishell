/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:52:21 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:52:21 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollarfill(t_data *data, int m, int startindex, int endindex)
{
	char	*temp;
	int		i;
	int		j;

	i = startindex;
	j = 0;
	temp = malloc(sizeof(char) * (endindex - startindex + 1));
	while (i < endindex)
	{
		temp[j++] = data->arguments[m][i++];
	}
	temp[j] = '\0';
	return (temp);
}

char	*addstringhelper(char *firststr, char *temp, char *thirdstr)
{
	char	*temp2;

	temp2 = ft_strjoin(firststr, temp);
	free(temp);
	temp = ft_strjoin(temp2, thirdstr);
	free(thirdstr);
	return (temp);
}

char	*addstring(int argi, int startindex, int endindex, t_data *data)
{
	char	*firststr;
	char	*temp;
	char	*addstr;
	char	*thirdstr;
	char	**temp3;

	addstr = dollarfill(data, argi, startindex, endindex);
	firststr = malloc(sizeof(char) * (startindex + 1));
	thirdstr = malloc((ft_strlen(data->arguments[argi]) - endindex + 1));
	addstringhelper2(data, firststr, argi, startindex);
	addstringhelper3(data, thirdstr, argi, endindex);
	if (findenvpindex2(addstr + 1, data) != -1)
	{
		temp3 = ft_split(data->envp[findenvpindex2(addstr + 1, data)], '=');
		temp = ft_strdup(temp3[1]);
		freedoublepointer(temp3);
	}
	else if (!ft_strcmp(addstr, "$?"))
		temp = ft_itoa(data->exitstatus);
	else
		temp = ft_strdup("\0");
	free(data->arguments[argi]);
	free(addstr);
	return (addstringhelper(firststr, temp, thirdstr));
}

void	transformdollar2(t_data *data, int i, int m, int j)
{
	while (data->arguments[i][++j])
	{
		if (data->arguments[i][j] == '$')
		{
			m = j + 1;
			if (data->arguments[i][m] == '?')
				m++;
			else if (ft_isdigit(data->arguments[i][m])
				|| (!ft_isalnum(data->arguments[i][m])
					&& data->arguments[i][m] != ' '))
				m++;
			else
			{
				while (!ft_isdigit(data->arguments[i][j + 1])
						&& (ft_isalnum(data->arguments[i][m])
							|| data->arguments[i][m] == '_')
						&& data->arguments[i][m])
					m++;
			}
			data->arguments[i] = addstring(i,
					j, m, data);
			j = m;
		}
	}
}

void	transformdollar(t_data *data, int quote)
{
	int		i;
	char	*temp;

	i = -1;
	while (data->arguments[++i])
	{
		if (data->arguments[i][0] != '\''
			&& ft_strchr(data->arguments[i], '$'))
		{
			if (data->arguments[i][0] == '\"'
				&& data->arguments[i]
				[ft_strlen(data->arguments[i]) - 1] == '\"')
			{
				temp = ft_strtrim(data->arguments[i], "\"");
				free(data->arguments[i]);
				data->arguments[i] = temp;
				quote = 1;
			}
			transformdollar2(data, i, 0, -1);
			if (quote == 1)
				addquote(data->arguments, i);
		}
	}
}
