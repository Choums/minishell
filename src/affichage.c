/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:06:35 by aptive            #+#    #+#             */
/*   Updated: 2022/05/28 01:41:25 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_affiche_t_command(t_command	*(*table_pipe))
{
	printf("\n\n\033[31m***************** tableau_t_command ******************************************\033[0m\n");
	for (int i = 0; table_pipe[i]; i++)
		printf("table_pipe[\033[1;32m%i\033[0m]:\033[1;32m%p\033[0m\n", i, table_pipe[i]);
	printf("\033[31m***************** all_pipe ***************************************************\033[0m\n");
	for (int i = 0; table_pipe[i]; i++)
		printf("table_pipe->all_pipe[\033[1;32m%i]:\033[1;32m%s\033[0m\n", i, table_pipe[i]->all_pipe);
	printf("\033[31m***************** tab_cmd ****************************************************\033[0m\n");
	for (int i = 0; table_pipe[i]; i++)
	{
		for (int j = 0; table_pipe[i]->tab_cmd[j]; j++)
			printf("table_pipe[\033[1;32m%i\033[0m]->tab_cmd[\033[1;32m%i\033[0m]:\033[1;32m%s\033[0m\n", i, j,table_pipe[i]->tab_cmd[j]);
	}
	printf("\033[31m***************** tab_redirection_in ****************************************************\033[0m\n");

	for (int j = 0; table_pipe[j]; j++)
	{
		printf("table_pipe[\033[1;32m%i\033[0m]: \033[1;32m%p\033[0m\n", j, table_pipe[j]);
		printf("table_pipe[\033[1;32m%i\033[0m]->tab_redirection: \033[1;32m%p\033[0m\n", j, table_pipe[j]->tab_redirection);
		if(table_pipe[j]->tab_redirection)
			for(int	i = 0; table_pipe[j]->tab_redirection->in[i]; i++)
			{

				printf("table_pipe[\033[1;32m%i\033[0m]->tab_redirection->in[\033[1;32m%i\033[0m]:\033[1;32m%s\033[0m\n", j, i,table_pipe[j]->tab_redirection->in[i]);
			}
	}
	printf("\033[31m***************** tab_redirection_out ****************************************************\033[0m\n");

	for (int j = 0; table_pipe[j]; j++)
	{
		printf("table_pipe[\033[1;32m%i\033[0m]: \033[1;32m%p\033[0m\n", j, table_pipe[j]);
		printf("table_pipe[\033[1;32m%i\033[0m]->tab_redirection: \033[1;32m%p\033[0m\n", j, table_pipe[j]->tab_redirection);
		if(table_pipe[j]->tab_redirection)
			for(int	i = 0; table_pipe[j]->tab_redirection->out[i]; i++)
			{

				printf("table_pipe[\033[1;32m%i\033[0m]->tab_redirection->out[\033[1;32m%i\033[0m]:\033[1;32m%s\033[0m\n", j, i,table_pipe[j]->tab_redirection->out[i]);
			}
	}
	printf("\033[31m***************** END ********************************************************\033[0m\n\n");
}
