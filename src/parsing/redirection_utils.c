/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:50:22 by aptive            #+#    #+#             */
/*   Updated: 2022/07/22 18:10:59 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_place_redirection(char *str)
{
	int	i;
	int	count;
	int	j;
	int	place;

	i = 0;
	count = 0;
	place = 0;
	// printf("str : %s\n", str);
	while (i < (int)ft_strlen(str))
	{
		// if (str[i] == '<' || str[i] == '>')
		// printf("%c", str[i]);
		j = 1;
		if (str[i] == '\'' || str[i] == '"')
		{
			while (str[i + j] && str[i + j] != str[i])
				j++;
			j++;
		}
		else if (str[i] == '>')
		{
			place = place * 10 + 1;
			j = 1;
		}
		else if (str[i] == '<')
		{

			place = place * 10 + 2;
			j = 1;
		}
		i += j;
	}
	// printf("\nplace = %i\n", place);
}

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
			if (str[i + 1] == c_redirect)
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
