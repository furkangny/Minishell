/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:56:13 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/16 12:57:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

typedef struct s_red
{
	char	*str;
	char	*type;
}	t_red;

typedef struct s_parse
{
	char	**str;
	char	*type;
	t_red	*red;
}	t_parse;

typedef struct s_lastpars
{
	int		i;
	int		z;
	int		j;
	t_parse	*last;
	int		fpi;
	int		tru;
	char	**str;
}	t_lastparse;

typedef struct s_data
{
	t_parse		*parts;
	t_red		*red;
	int			exitstatus;
	char		*commandline;
	char		*templine;
	char		**path;
	char		*foundedpath;
	char		**arguments;
	char		*simplestarttext;
	char		*starttext;
	char		**envp;
	char		**exportp;
	int			errorstatus;
	int			exportlen;
	int			commandcount;
	int			fderr;
	int			parsererrorcode;
	int			pipe_pos;
}	t_data;

typedef struct s_global
{
	int	error;
	int	heredoc;
	int	execstatus;
}	t_global;

t_global	g_global;

char	*getpcname(void);
void	findstarttext(char *pcname, t_data *data);
int		findpath(char *searchedpath, t_data *data);
void	initializefunction(char **envp, int argc, char **argv, t_data *data);
void	ifsendsigint(int signal);
void	ft_error(char *a);
char	**copyenv(char **env);
int		check_quote(char *line, int control);
void	parser(t_data *data);
void	print_twodstr(char **str, int flagcontrol);
int		parserlongcontroller(int i, t_data *data);
int		ifmultiquote(char *a, int i, int *j, t_data *data);
int		ifsinglequote(char *a, int i, int *j, t_data *data);
int		pipecontrol(char *a, int i, t_data *data);
t_parse	*lastparse(char **str, int tru, int i, t_data *data);
void	quoteerror(t_data *data);
int		commandpointerlen(char **d);
void	cdcommand(char **a, t_data *data);
void	pwdcommand(t_data *data);
int		findpathindex(char *searchedpath, t_data *data);
int		findenvpindex(char *searchedenvp, int searchindex, t_data *data);
int		findenvpindex2(char *searchedenvp, t_data *data);
void	envcommand(t_data *data);
void	exportcommand(char **str, int i, int error, t_data *data);
char	**adddoublepointer(char **dp, char *add);
char	**removedoublepointerarg(char **dp, int i);
void	echocommand(char **str);
char	*get_the_path(char **env, char *str, t_data *data);
int		exportparser(char *str);
int		findexportindex(char *searchedexportp, int searchindex, t_data *data);
void	unsetcommand(char **str, t_data *data);
void	exitcommand(void);
void	transformdollar(t_data *data, int quote);
void	ifsendsigquit(int signal);
void	pipecommand(t_parse *part1, t_parse *part2, int i, t_data *data);
void	ft_chiledfpi(t_parse *part1, t_parse *part2, t_data *data);
void	ft_chiled(char **str, t_data *data);
void	commanddetermination(char **str, t_data *data);
void	ft_odd_right_redirection(char *str, t_data *data, t_parse *part);
void	ft_odd_left_redirection(char *str, t_data *data, t_parse *part);
char	*removequotes2(char *str);
void	removequotes(t_data *data);
int		echonflagcontroller(char *str);
void	ft_multiple_right_redirection(char *str, t_data *data, t_parse *part);
void	ft_multiple_left_redirection(char *str, t_data *data, t_parse *part);
int		ifendispipe(t_data *data, int i);
void	preparewhile(t_data *data);
void	freedoublepointer(char **str);
void	errorcontrol(t_data *data, int err);
void	commanddetermination(char **str, t_data *data);
void	commandfinderv2(t_data *data);
void	printexport(t_data *data);
int		ifdoubleinput(t_data *data);
void	inputall(t_parse *part, t_data *data);
void	outputall(t_parse *part, t_data *data);
int		check_redir(char **str);
int		redlen(t_red *red);
void	commandfinderpipe(t_data *data);
int		count_redir(char **str);
char	**with_out_redir(char **str, int x);
int		words_of_parts_outredir(char **argu);
void	remove_ctrl(void);
void	ft_sub_output(t_parse *part, int i);
int		words_of_parts(char **argu);
char	**towdcopy(char **src);
int		countfrompars(t_data *data, int i, int count, int tru);
char	*lastparse_define_type(char *str);
void	addquote(char **arguments, int i);
void	addstringhelper2(t_data *data, char *firststr,
			int argi, int startindex);
void	addstringhelper3(t_data *data, char *thirdstr, int argi, int endindex);
void	isupdate1helperforexport(t_data *data, char *str);

#endif
