/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/19 15:25:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Lexing Parsing
 *	Parcourt la line et execute les differentes tab_cmdes
 *	Separateur => espaces, '', "", <>, <<>>, |
 *
*/

/*

Les tab_cmdes séparées par un ';' sont exécutées successivement,
l'interpréteur attend que chaque tab_cmde se termine avant de lancer la suivante
*/
int	ft_doubletab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_count_pipe(char *line)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 1;
	while (i < ft_strlen(line))
	{
		j = 1;
		if (line[i] == '\'' || line[i] == '"')
		{
			while (line[i + j] && line[i + j] != line[i])
				j++;
			j++;
		}
		else if (line[i] == '|')
			count++;
		i += j;
	}
	return (count);
}

t_command	**ft_parse_pipe(t_command	*(*table_pipe), char *line)
{
	char	**tmp;
	int		i;

	table_pipe = malloc(sizeof(table_pipe) * (ft_count_pipe(line) + 1));
	if (!table_pipe)
		return (NULL);
	table_pipe[ft_count_pipe(line)] = NULL;
	i = -1;
	while (++i < ft_count_pipe(line))
	{
		table_pipe[i] = malloc(sizeof(t_command) * (1));
		if (!table_pipe[i])
			return (NULL);
	}
	table_pipe[ft_count_pipe(line)] = NULL;
	tmp = split_pipe(line);
	i = -1;
	while (tmp[++i] && table_pipe[i]->all_pipe)
		table_pipe[i]->all_pipe = tmp[i];
	free(tmp);
	return (table_pipe);
}

void	ft_pipe_len(t_command *(*table_pipe))
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (table_pipe[i])
		i++;
	while (table_pipe[++j])
		table_pipe[j]->len_pipe = i - 1;
}

//< infile cmd1 -opt1 > outfile | < infile2 cmd2 -opt2 > outfile2
//cmd1 -opt1 <infile
// < infile1 < infile2 cmd | < infile3 <infile4 cmd2
// < infile1 < infile2 cmd | < infile3 <infile4 cmd2 | <infile5 cmd3
//< infile <infile2 cmd | <infile3 cmd2 | <infile4<<infile5 cmd3
t_command	**ft_parsing(t_data *data, char *line, t_command	*(*table_pipe))
{
	int		i;

	table_pipe = ft_parse_pipe(table_pipe, line);
	i = -1;
	while (table_pipe[++i])
	{
		if (ft_strchr(table_pipe[i]->all_pipe, '<')
			|| ft_strchr(table_pipe[i]->all_pipe, '>'))
		{
			ft_parse_redir_in(table_pipe, i, '<');
			ft_parse_redir_out(table_pipe, i, '>');
			tokenizer_redir_in(table_pipe, i);
			tokenizer_redir_out(table_pipe, i);
		}
		else
			table_pipe[i]->tab_redir = NULL;
		table_pipe = ft_parse_cmd(table_pipe, i);
		tokenizer_cmd(table_pipe, i, data);
	}
	ft_pipe_len(table_pipe);
	return (table_pipe);
}
