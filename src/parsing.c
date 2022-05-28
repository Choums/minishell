/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/28 01:43:20 by aptive           ###   ########.fr       */
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
void	ft_free_doutab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
	int	count_pipe;
	int	i;

	count_pipe = 1;
	i = -1;

	while(line[++i])
	{
		if(line[i] == '|')
			count_pipe++;
	}
	return (count_pipe);
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
	while (++i <= ft_count_pipe(line))
	{
		table_pipe[i] = malloc(sizeof(t_command) * (1));
		if (!table_pipe[i])
			return (NULL);
	}
	table_pipe[ft_count_pipe(line)] = NULL;
	tmp = ft_split(line, '|');
	i = -1;
	while (tmp[++i] && table_pipe[i]->all_pipe)
		table_pipe[i]->all_pipe = tmp[i];
	return (table_pipe);
}


//< infile cmd1 -opt1 > outfile | < infile2 cmd2 -opt2 > outfile2
//cmd1 -opt1 <infile
// < infile1 < infile2 cmd | < infile3 <infile4 cmd2
// < infile1 < infile2 cmd | < infile3 <infile4 cmd2 | <infile5 cmd3
//< infile <infile2 cmd | <infile3 cmd2 | <infile4<<infile5 cmd3
void	ft_parsing(char *line)
{
	t_command	*(*table_pipe);

	if (!ft_strlen(line))
		return;
	table_pipe = ft_parse_pipe(table_pipe, line);
	int	i;

	i = -1;
	while (table_pipe[++i])
	{

		table_pipe = ft_parse_redirection_in(table_pipe, i, '<');
		table_pipe = ft_parse_redirection_out(table_pipe, i, '>');
		table_pipe = ft_parse_cmd(table_pipe, i);
	}


	// ft_affiche_t_command(table_pipe);
}
