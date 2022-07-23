/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_tab_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:16:21 by tdelauna          #+#    #+#             */
/*   Updated: 2022/07/22 20:39:29 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tab_fusion_init(t_redirection *tab_redir)
{
	int	len_tab_in;
	int	len_tab_out;

	len_tab_in = ft_doubletab_len(tab_redir->in);
	len_tab_out = ft_doubletab_len(tab_redir->out);
	// printf("len_tab_in : %i\n", len_tab_in);
	// printf("len_tab_out : %i\n", len_tab_out);
	tab_redir->tab_fusion =
		 malloc(sizeof(char *) * (len_tab_in + len_tab_out + 1));
	if (!tab_redir->tab_fusion)
		return ;
	tab_redir->tab_fusion[len_tab_in + len_tab_out] = NULL;
	tab_redir->tab_fusion_token =
		 malloc(sizeof(char *) * (len_tab_in + len_tab_out + 1));
	if (!tab_redir->tab_fusion_token)
		return ;
	tab_redir->tab_fusion_token[len_tab_in + len_tab_out] = NULL;

}

void	fusion(t_command *table_pipe)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = -1;
	j = 0;
	k = 0;
	m = 0;
	while (table_pipe->redir_place[++i])
	{
		if (table_pipe->redir_place[i] == '2')
		{
			table_pipe->tab_redir->tab_fusion[j] = table_pipe->tab_redir->in[k];
			table_pipe->tab_redir->tab_fusion_token[j] = table_pipe->tab_redir->token_in[k];
			j++;
			k++;
		}
		else if (table_pipe->redir_place[i] == '1')
		{
			table_pipe->tab_redir->tab_fusion[j] = table_pipe->tab_redir->out[m];
			table_pipe->tab_redir->tab_fusion_token[j] = table_pipe->tab_redir->token_out[m];
			j++;
			m++;
		}
	}
}

void	fusion_tab_redir(t_command	*(*table_pipe))
{
	int	i;

	i = 0;

	while (table_pipe[i])
	{
		if (table_pipe[i]->tab_redir)
		{
			tab_fusion_init(table_pipe[i]->tab_redir);
			fusion(table_pipe[i]);
			free(table_pipe[i]->redir_place);
		}
		i++;
	}
}
