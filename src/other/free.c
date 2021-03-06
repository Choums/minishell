/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:36:29 by aptive            #+#    #+#             */
/*   Updated: 2022/07/24 18:51:07 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_doutab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_struc(t_command **table_pipe)
{
	int	i;
	int	len;

	i = -1;
	len = struc_len(table_pipe);
	while (++i < len)
	{
		free(table_pipe[i]->all_pipe);
		free_double_tab(table_pipe[i]->tab_cmd);
		free_double_tab(table_pipe[i]->tab_token);
		if (table_pipe[i]->tab_redir)
		{
			free_double_tab(table_pipe[i]->tab_redir->in);
			free_double_tab(table_pipe[i]->tab_redir->token_in);
			free_double_tab(table_pipe[i]->tab_redir->out);
			free_double_tab(table_pipe[i]->tab_redir->token_out);
			free(table_pipe[i]->tab_redir->tab_fusion);
			free(table_pipe[i]->tab_redir->tab_fusion_to);
			free(table_pipe[i]->tab_redir);
		}
		else
			free(table_pipe[i]->tab_redir);
		free(table_pipe[i]);
	}
	free(table_pipe);
}
