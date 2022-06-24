/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:34:59 by tdelauna          #+#    #+#             */
/*   Updated: 2022/06/24 17:42:36 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_str_quote(char *str)
{
	char	*tmp;
	char	c;
	int		i;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			while (str[++i] != c)
				tmp = ft_straddc(tmp, str[i]);
		}
		else
			tmp = ft_straddc(tmp, str[i]);
		i++;
	}
	return (tmp);
}

void	parse_quote_redir(char **tab)
{
	char	*dest;
	int		j;

	j = -1;
	while (tab[++j])
	{
		if (ft_strchr(tab[j], '\'')
			|| ft_strchr(tab[j], '"'))
		{
			dest = parse_str_quote(tab[j]);
			free(tab[j]);
			tab[j] = dest;
		}
	}
}

void	parse_quote(t_command *(*table_pipe))
{
	int		i;

	i = -1;
	while (table_pipe[++i])
	{
		if (table_pipe[i]->tab_cmd)
			parse_quote_redir(table_pipe[i]->tab_cmd);
		if (table_pipe[i]->tab_redir && table_pipe[i]->tab_redir->in)
			parse_quote_redir(table_pipe[i]->tab_redir->in);
		if (table_pipe[i]->tab_redir && table_pipe[i]->tab_redir->out)
			parse_quote_redir(table_pipe[i]->tab_redir->out);
	}
}
