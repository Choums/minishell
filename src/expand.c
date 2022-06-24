/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:38:11 by tdelauna          #+#    #+#             */
/*   Updated: 2022/06/23 14:44:35 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	go_expand(t_data *data, t_command *(*table_pipe))
{
	char	*expand;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (table_pipe[i])
	{
		while (table_pipe[i]->tab_cmd[j])
		{
			if (ft_strchr(table_pipe[i]->tab_cmd[j], '$'))
			{
				expand = which_dollar(data, table_pipe[i]->tab_cmd[j]);
				free(table_pipe[i]->tab_cmd[j]);
				table_pipe[i]->tab_cmd[j] = expand;
			}
			j++;
		}
		i++;
	}
}
