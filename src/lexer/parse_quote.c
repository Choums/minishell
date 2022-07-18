/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:34:59 by tdelauna          #+#    #+#             */
/*   Updated: 2022/07/18 20:03:32 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_str_quote_utils(char *str, int *i, char *tmp)
{
	char	c;

	c = str[*i];
	while (str[++*i] != c)
	{
		if (str[*i] == '\\')
			tmp = ft_straddc(tmp, str[*i++]);
		tmp = ft_straddc(tmp, str[*i]);
	}

	return (tmp);
}

char	*parse_str_quote(char *str)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '\\')
		{
			tmp = ft_straddc(tmp, str[i++]);
			tmp = ft_straddc(tmp, str[i]);
		}
		else if (str[i] == '"' || str[i] == '\'')
			tmp = parse_str_quote_utils(str, &i, tmp);
		else
			tmp = ft_straddc(tmp, str[i]);
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
