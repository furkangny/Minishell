/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:56 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:51:58 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwdcommand(t_data *data)
{
	char	**temp;

	temp = ft_split(data->envp[findenvpindex("PWD=", 4, data)], '=');
	printf("%s\n", temp[1]);
	freedoublepointer(temp);
}
