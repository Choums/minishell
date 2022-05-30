/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:46:05 by tdelauna          #+#    #+#             */
/*   Updated: 2022/05/30 20:13:57 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenizer_cmd(t_command **table_pipe, int nb_pp)
{
	int	i;

	i = ft_doubletab_len(table_pipe[nb_pp]->tab_cmd);



	table_pipe[nb_pp]->tab_token = ft_calloc(i + 1, sizeof(char *));
	if (!table_pipe[nb_pp]->tab_token)
		return ;

	i = 0;
	while (table_pipe[nb_pp]->tab_token[i])
		table_pipe[nb_pp]->tab_token[i] = ft_calloc(2, sizeof(char));

	i = 0;
	while (table_pipe[nb_pp]->tab_token[i])
	{
		if (find_b)
		table_pipe[nb_pp]->tab_token[i][0] =
	}
	printf("table_pipe[j]->tab_token : %p\n", table_pipe[nb_pp]->tab_token);

	for (int j = 0; table_pipe[nb_pp]->tab_token[j]; j++)
		printf("table_pipe[j]->tab_token[j] : %p\n", table_pipe[nb_pp]->tab_token[j]);
	printf("Len table : %i\n", i);
}
