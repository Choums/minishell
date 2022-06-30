/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:14:44 by aptive            #+#    #+#             */
/*   Updated: 2022/06/30 15:27:36 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_str_back_slash(char *str)
{
	char	*tmp;
	char	c;
	int		i;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
				// printf("OK\n");
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

void	parse_back_redir(char **tab)
{
	char	*dest;
	int		j;

	j = -1;
	while (tab[++j])
	{
		if (ft_strchr(tab[j], '\\'))
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
			parse_back_redir(table_pipe[i]->tab_cmd);
		if (table_pipe[i]->tab_redir && table_pipe[i]->tab_redir->in)
			parse_back_redir(table_pipe[i]->tab_redir->in);
		if (table_pipe[i]->tab_redir && table_pipe[i]->tab_redir->out)
			parse_back_redir(table_pipe[i]->tab_redir->out);
	}
}
