/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_tab_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:16:21 by tdelauna          #+#    #+#             */
/*   Updated: 2022/07/29 00:58:57 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tab_fusion_init(t_redirection *tab_redir)
{
	int	len_tab_in;
	int	len_tab_out;

	len_tab_in = ft_doubletab_len(tab_redir->in);
	len_tab_out = ft_doubletab_len(tab_redir->out);
	tab_redir->tab_fusion
		= malloc(sizeof(char *) * (len_tab_in + len_tab_out + 1));
	if (!tab_redir->tab_fusion)
		return ;
	init_tab_fusion(tab_redir, len_tab_in + len_tab_out);
	tab_redir->tab_fusion_to
		= malloc(sizeof(char *) * (len_tab_in + len_tab_out + 1));
	if (!tab_redir->tab_fusion_to)
		return ;
	init_tab_fusion_to(tab_redir, len_tab_in + len_tab_out);
}

void	init_tab_fusion(t_redirection *tab, int max)
{
	int	i;

	i = 0;
	while (i < max)
		tab->tab_fusion[i++] = NULL;
	tab->tab_fusion[max] = NULL;
}

void	init_tab_fusion_to(t_redirection *tab, int max)
{
	int	i;

	i = 0;
	while (i < max)
		tab->tab_fusion_to[i++] = NULL;
	tab->tab_fusion_to[max] = NULL;
}

void	fusion(t_command *t_p)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = -1;
	j = 0;
	k = 0;
	m = 0;
	while (t_p->redir_place[++i])
	{
		if (t_p->redir_place[i] == '2')
		{
			t_p->tab_redir->tab_fusion[j] = t_p->tab_redir->in[k];
			t_p->tab_redir->tab_fusion_to[j++] = t_p->tab_redir->token_in[k++];
		}
		else if (t_p->redir_place[i] == '1')
		{
			t_p->tab_redir->tab_fusion[j] = t_p->tab_redir->out[m];
			t_p->tab_redir->tab_fusion_to[j++] = t_p->tab_redir->token_out[m++];
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
