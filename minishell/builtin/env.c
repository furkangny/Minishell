/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:51:23 by fgunay            #+#    #+#             */
/*   Updated: 2024/03/14 16:51:26 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envcommand(t_data *data)
{
	int	i;

	i = 0;
	while (i < commandpointerlen(data->envp))
		printf("%s\n", data->envp[i++]);
}
