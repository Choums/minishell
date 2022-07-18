/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:14:44 by aptive            #+#    #+#             */
/*   Updated: 2022/07/18 18:00:11 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_str_back_slash(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			tmp = ft_straddc(tmp, str[i++]);
		}
		else
			tmp = ft_straddc(tmp, str[i++]);
	}
	return (tmp);
}

void	parse_back_redir(char **tab, char **tab_token)
{
	char	*dest;
	int		j;

	j = -1;
	while (tab[++j])
	{
		if (ft_strchr(tab[j], '\\') && tab_token[j][0] != '5'
			&& tab_token[j][0] != '4')
		{
			dest = parse_str_back_slash(tab[j]);
			free(tab[j]);
			tab[j] = dest;
		}
	}
}

void	parse_back_slash(t_command *(*table_pipe))
{
	int		i;

	i = -1;
	while (table_pipe[++i])
	{
		if (table_pipe[i]->tab_cmd)
			parse_back_redir(table_pipe[i]->tab_cmd, table_pipe[i]->tab_token);
		if (table_pipe[i]->tab_redir && table_pipe[i]->tab_redir->in)
			parse_back_redir(table_pipe[i]->tab_redir->in,
				table_pipe[i]->tab_redir->token_in);
		if (table_pipe[i]->tab_redir && table_pipe[i]->tab_redir->out)
			parse_back_redir(table_pipe[i]->tab_redir->out,
				table_pipe[i]->tab_redir->token_out);
	}
}
