/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:54:20 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:54:21 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getpcname(void)
{
	char	*pcname;
	int		fd[2];
	pid_t	id;
	int		bytesread;
	char	**temp;

	temp = ft_split("scutil --get ComputerName", ' ');
	pcname = malloc(256 * sizeof(char));
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/sbin/scutil", temp, NULL);
	}
	else
	{
		wait(NULL);
		bytesread = read(fd[0], pcname, sizeof(pcname));
		if (bytesread == -1)
			ft_error("File read error!");
		pcname[bytesread] = '\0';
		freedoublepointer(temp);
	}
	return (pcname);
}

void	findstarttext(char *pcname, t_data *data)
{
	char	**pwd;
	char	*temp;
	int		i;

	i = 0;
	temp = getcwd(NULL, 0);
	pwd = ft_split(temp, '/');
	free(temp);
	data->simplestarttext = ft_strjoin2("Miniroot - ", getenv("LOGNAME"));
	data->simplestarttext = ft_strjoin(data->simplestarttext, "@");
	data->simplestarttext = ft_strjoin(data->simplestarttext, pcname);
	data->starttext = ft_strjoin2(data->simplestarttext, " ");
	temp = getcwd(NULL, 0);
	if (ft_strcmp(temp, getenv("HOME")) == 0)
		data->starttext = ft_strjoin(data->starttext, "~");
	else
		data->starttext = ft_strjoin(data->starttext,
				pwd[commandpointerlen(pwd) - 1]);
	data->starttext = ft_strjoin(data->starttext, " % ");
	while (pwd[i])
		free(pwd[i++]);
	free(pwd[i]);
	free(pwd);
	free(temp);
	free(pcname);
}

void	printwelcome(void)
{
	printf("\033[32m/* ************************************************ */\n");
	printf("/*                                                  */\n");
	printf("/*          Welcome to our MiniShell                */\n");
	printf("/*          fgunay       ---       mubeyaz          */\n");
	printf("/*                                                  */\n");
	printf("/* ************************************************ */\n\n\033[0m");
}

void	initializefunction(char **envp, int argc, char **argv, t_data *data)
{
	char	*pcname;

	if (argc > 1)
		printf("\033[31;4mMinishell: Command not found: %s\n\033[0m",
			argv[1]);
	pcname = getpcname();
	findstarttext(pcname, data);
	data->path = ft_split(getenv("PATH"), ':');
	data->envp = copyenv(envp);
	data->exportp = copyenv(envp);
	data->exportlen = commandpointerlen(data->exportp);
	g_global.error = 0;
	data->exitstatus = 0;
	g_global.execstatus = 0;
	g_global.heredoc = 0;
	data->commandcount = 0;
	data->arguments = NULL;
	data->commandline = NULL;
	data->parts = NULL;
	data->fderr = dup(1);
	printwelcome();
}

void	ft_error(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		write(1, &a[i++], 1);
	exit(1);
}
