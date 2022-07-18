// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   affichage.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/05/27 19:06:35 by aptive            #+#    #+#             */
// /*   Updated: 2022/07/18 18:07:57 by aptive           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// void	ft_affiche_t_command(t_command	*(*table_pipe))
// {
// 	printf("\n\n\033[31m***************** tableau_t_command ******************************************\033[0m\n");
// 	for (int i = 0; table_pipe[i]; i++)
// 	{
// 		printf("table_pipe[\033[1;32m%i\033[0m]:\033[1;32m%p\033[0m\n", i, table_pipe[i]);
// 		printf("len_pipe : \033[1;32m%i\033[0m\033\n",table_pipe[i]->len_pipe);
// 	}
// 	printf("\033[31m***************** all_pipe ***************************************************\033[0m\n");
// 	for (int i = 0; table_pipe[i]; i++)
// 		printf("table_pipe->all_pipe[\033[1;32m%i]:\033[1;32m%s\033[0m\n", i, table_pipe[i]->all_pipe);
// 	printf("\033[31m***************** tab_cmd ****************************************************\033[0m\n");
// 	for (int i = 0; table_pipe[i]; i++)
// 	{
// 		for (int j = 0; table_pipe[i]->tab_cmd[j]; j++)
// 			printf("table_pipe[\033[1;32m%i\033[0m]->tab_cmd[\033[1;32m%i\033[0m]:\033[1;32m%s\033[0m\n", i, j,table_pipe[i]->tab_cmd[j]);
// 	}
// 	printf("\033[31m***************** tab_redir_in ***********************************************\033[0m\n");
// 	for (int j = 0; table_pipe[j]; j++)
// 	{
// 		if (table_pipe[j]->tab_redir)
// 		{
// 			printf("table_pipe[\033[1;32m%i\033[0m]: \033[1;32m%p\033[0m\n", j, table_pipe[j]);
// 			printf("table_pipe[\033[1;32m%i\033[0m]->tab_redir: \033[1;32m%p\033[0m\n", j, table_pipe[j]->tab_redir);
// 		}
// 		if(table_pipe[j]->tab_redir)
// 			for(int	i = 0; table_pipe[j]->tab_redir->in[i]; i++)
// 			{
// 				printf("table_pipe[\033[1;32m%i\033[0m]->tab_redir->in[\033[1;32m%i\033[0m]:\033[1;32m%s\033[0m\n", j, i,table_pipe[j]->tab_redir->in[i]);
// 			}
// 	}
// 	printf("\033[31m***************** tab_redir_out **********************************************\033[0m\n");
// 	for (int j = 0; table_pipe[j]; j++)
// 	{
// 		printf("table_pipe[\033[1;32m%i\033[0m]: \033[1;32m%p\033[0m\n", j, table_pipe[j]);
// 		printf("table_pipe[\033[1;32m%i\033[0m]->tab_redir: \033[1;32m%p\033[0m\n", j, table_pipe[j]->tab_redir);
// 		if(table_pipe[j]->tab_redir)
// 			for(int	i = 0; table_pipe[j]->tab_redir->out[i]; i++)
// 			{

// 				printf("table_pipe[\033[1;32m%i\033[0m]->tab_redir->out[\033[1;32m%i\033[0m]:\033[1;32m%s\033[0m\n", j, i,table_pipe[j]->tab_redir->out[i]);
// 			}
// 	}
// 	printf("\033[31m***************** token_cmd **************************************************\033[0m\n");
// 	for (int j = 0; table_pipe[j]; j++)
// 	{
// 		printf("table_pipe[j]->tab_token : %p\n", table_pipe[j]->tab_token);

// 		for (int i = 0; table_pipe[j]->tab_token[i]; i++)
// 			printf("[\033[1;32mtable_pipe[%i]->tab_token[%i] : %s\033[0m\n",j, i, table_pipe[j]->tab_token[i]);

// 	}
// 	printf("\033[31m***************** token_in ***************************************************\033[0m\n");
// 	for (int j = 0; table_pipe[j]; j++)
// 	{
// 		if(table_pipe[j]->tab_redir)
// 		{
// 			printf("table_pipe[j]->tab_redir->token_in : %p\n", table_pipe[j]->tab_redir->token_in);
// 			for (int i = 0; table_pipe[j]->tab_redir->token_in[i]; i++)
// 				printf("[\033[1;32mtable_pipe[%i]->tab_redir->token_in[%i] : %s\033[0m\n",j, i, table_pipe[j]->tab_redir->token_in[i]);
// 		}
// 	}
// 	printf("\033[31m***************** token_out **************************************************\033[0m\n");
// 	for (int j = 0; table_pipe[j]; j++)
// 	{
// 		if(table_pipe[j]->tab_redir)
// 		{
// 			printf("table_pipe[j]->tab_redir->token_out : %p\n", table_pipe[j]->tab_redir->token_out);
// 			for (int i = 0; table_pipe[j]->tab_redir->token_out[i]; i++)
// 				printf("[\033[1;32mtable_pipe[%i]->tab_redir->token_out[%i] : %s\033[0m\n",j, i, table_pipe[j]->tab_redir->token_out[i]);
// 		}
// 	}
// 	printf("\033[31m***************** END ********************************************************\033[0m\n\n");
// }

