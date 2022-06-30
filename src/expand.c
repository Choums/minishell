/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:38:11 by tdelauna          #+#    #+#             */
/*   Updated: 2022/06/30 16:39:09 by aptive           ###   ########.fr       */
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
			if (ft_strchr(table_pipe[i]->tab_cmd[j], '$')
				&& !ft_strchr(table_pipe[i]->tab_token[j], '4'))
			{
				expand = which_dollar(data, table_pipe[i]->tab_cmd[j]);
				free(table_pipe[i]->tab_cmd[j]);
				table_pipe[i]->tab_cmd[j] = expand;
				printf("expand : %s\n", expand);
			}
			j++;
		}
		i++;
	}
}
