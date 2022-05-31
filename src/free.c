/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:36:29 by aptive            #+#    #+#             */
/*   Updated: 2022/05/31 03:17:39 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	i = 0;
	int len = struc_len(table_pipe);
	while (i < len)
	{
		// if (table_pipe[i]->all_pipe)
			free(table_pipe[i]->all_pipe);
		// if (table_pipe[i]->tab_cmd)
			ft_free_doutab(table_pipe[i]->tab_cmd);
		// if (table_pipe[i]->tab_token)
			ft_free_doutab(table_pipe[i]->tab_token);
		if (table_pipe[i]->tab_redirection)
		{
			printf("OK\n");
			// if (table_pipe[i]->tab_redirection->in)
				free_double_tab(table_pipe[i]->tab_redirection->in);
				// free(table_pipe[i]->tab_redirection->in);

			// if (table_pipe[i]->tab_redirection->token_in)
				free_double_tab(table_pipe[i]->tab_redirection->token_in);

			// if (table_pipe[i]->tab_redirection->out)
				free_double_tab(table_pipe[i]->tab_redirection->out);

			// if (table_pipe[i]->tab_redirection->token_out)
				free_double_tab(table_pipe[i]->tab_redirection->token_out);
			free(table_pipe[i]->tab_redirection);
		}
		else
		{
			printf("here\n");

				// free_double_tab(table_pipe[i]->tab_redirection->in);

				// free_double_tab(table_pipe[i]->tab_redirection->out);
			free(table_pipe[i]->tab_redirection);
		}
		free(table_pipe[i]);
		i++;
	}
	// free(table_pipe[i+1]);
	// free(table_pipe[i]->all_pipe);
	free(table_pipe);
}
