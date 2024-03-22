/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:00 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:51:01 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	makepwd(char *oldpwd, char *newpwd, t_data *data)
{
	int		oldpwdindex;
	int		pwdindex;
	char	**newstarttext;

	oldpwdindex = findenvpindex("OLDPWD=", 7, data);
	pwdindex = findenvpindex("PWD=", 4, data);
	free(data->envp[oldpwdindex]);
	free(data->envp[pwdindex]);
	data->envp[oldpwdindex] = ft_strjoin2("OLDPWD=", oldpwd);
	data->envp[pwdindex] = ft_strjoin2("PWD=", newpwd);
	free(data->starttext);
	if (ft_strcmp(newpwd, getenv("HOME")) == 0)
		data->starttext = ft_strjoin2(data->simplestarttext, " ~ ");
	else
	{
		newstarttext = ft_split(data->envp[pwdindex], '/');
		data->starttext = ft_strjoin2(data->simplestarttext, " ");
		data->starttext = ft_strjoin(data->starttext,
				newstarttext[commandpointerlen(newstarttext) - 1]);
		data->starttext = ft_strjoin(data->starttext, " % ");
		freedoublepointer(newstarttext);
	}
	free(newpwd);
	free(oldpwd);
}

void	cdcommand(char **a, t_data *data)
{
	int		i;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	i = commandpointerlen(a);
	if (i == 1 || (i == 2 && ft_strcmp(a[1], "~") == 0))
	{
		chdir(getenv("HOME"));
		makepwd(pwd, getcwd(NULL, 0), data);
	}
	else
	{
		if (chdir(a[1]))
		{
			free(pwd);
			perror(a[1]);
		}
		else
			makepwd(pwd, getcwd(NULL, 0), data);
	}
}
