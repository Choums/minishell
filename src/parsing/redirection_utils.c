/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:50:22 by aptive            #+#    #+#             */
/*   Updated: 2022/07/19 00:51:41 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_redirection(char *str, char c_redirect)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(str))
	{
		j = 1;
		if (str[i] == '\'' || str[i] == '"')
		{
			while (str[i + j] && str[i + j] != str[i])
				j++;
			j++;
		}
		else if (str[i] == c_redirect)
		{
			count++;
			j++;
		}
		i += j;
	}
	return (count);
}

void	init_redir_zero(t_command	*(*table_pipe), int number_pipe)
{
	table_pipe[number_pipe]->tab_redir->cpy_in = 0;
	table_pipe[number_pipe]->tab_redir->cpy_out = 0;
	table_pipe[number_pipe]->tab_redir->in_fd = 0;
	table_pipe[number_pipe]->tab_redir->out_fd = 0;
}
