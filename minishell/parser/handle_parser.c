/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:54:53 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:54:54 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_redirection(t_lastparse *lp)
{
	lp->last[lp->j - 1].red[lp->z].str = ft_strjoin2(lp->str[lp->i],
			lp->str[lp->i + 1]);
	lp->last[lp->j - 1].red[lp->z].type = lastparse_define_type(lp->str[lp->i]);
	lp->z++;
}

void	handle_pipe(t_lastparse *lp)
{
	if (check_redir(&(lp->str[lp->fpi])))
	{
		lp->last[lp->j - 1].red[lp->z].type = NULL;
	}
	lp->fpi = lp->i + 1;
	lp->tru = 1;
	lp->last[lp->j].red = NULL;
	lp->last[lp->j].str = towdcopy(&(lp->str[lp->i]));
	lp->last[lp->j++].type = lastparse_define_type(lp->str[lp->i]);
}

void	handle_redirection(t_lastparse *lp)
{
	if (lp->tru == 1 && !check_redir(&(lp->str[lp->fpi])))
	{
		lp->tru = 0;
		lp->last[lp->j].red = NULL;
		lp->last[lp->j].str = towdcopy(&(lp->str[lp->i]));
		lp->last[lp->j++].type = ft_strdup("word");
	}
}

void	last_parse_init(t_lastparse *lp)
{
	while (lp->str[++(lp->i)])
	{
		if (lp->str[lp->i][0] == '|')
			handle_pipe(lp);
		else if ((lp->str[lp->i][0] == '>' || lp->str[lp->i][0] == '<')
					&& lp->str[lp->i + 1] && check_redir(&(lp->str[lp->fpi])))
		{
			if (lp->tru == 1)
			{
				lp->last[lp->j].red = malloc(sizeof(t_red)
						* (count_redir(&(lp->str[lp->fpi])) + 1));
				lp->tru = 0;
				lp->z = 0;
				lp->last[lp->j].str
					= with_out_redir(&(lp->str[lp->fpi]), lp->i);
				lp->last[lp->j++].type = ft_strdup("word");
			}
			join_redirection(lp);
		}
		else
			handle_redirection(lp);
	}
	lp->last[lp->j].type = NULL;
	if (check_redir(&(lp->str[lp->fpi])))
		lp->last[lp->j - 1].red[lp->z].type = NULL;
}

t_parse	*lastparse(char **str, int tru, int i, t_data *data)
{
	t_lastparse	lp;
	t_parse		*last;

	lp.last = malloc(sizeof(t_parse) * (countfrompars(data, -1, 0, 1) + 1));
	lp.i = i;
	lp.j = 0;
	lp.z = 0;
	lp.fpi = 0;
	lp.tru = tru;
	lp.str = str;
	last_parse_init(&lp);
	last = lp.last;
	return (last);
}
