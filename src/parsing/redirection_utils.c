/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:50:22 by aptive            #+#    #+#             */
/*   Updated: 2022/07/23 15:13:18 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	nb_place_redir(char *str, int *place, int *j)
{
	if (str[0] == '>')
		*place = *place * 10 + 1;
	else
		*place = *place * 10 + 2;
	if (str[1] == str[0])
		*j = 2;
}

char	*ft_place_redir(char *str)
{
	int	i;
	int	j;
	int	place;

	i = 0;
	place = 0;
	while (i < (int)ft_strlen(str))
	{
		j = 1;
		if (str[i] == '\'' || str[i] == '"')
		{
			while (str[i + j] && str[i + j] != str[i])
				j++;
			j++;
		}
		else if (str[i] == '>' || str[i] == '<')
			nb_place_redir(str + i, &place, &j);
		i += j;
	}
	return (ft_itoa(place));
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
