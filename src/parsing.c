/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/25 19:16:04 by aptive           ###   ########.fr       */
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

int	ft_affiche_struc(t_command *(*tab_cmd))
{
	int	i;
	int	j;

	printf("-----------------------------------------------------\n");
	i = -1;
	while (tab_cmd[++i])
	{
		j = -1;
		printf("tab_tab_cmd : %i ", tab_cmd[i]->nb_cmd);
		while (tab_cmd[i]->tab_cmd[++j])
			printf("%s ", tab_cmd[i]->tab_cmd[j]);
		j = -1;
		printf("\n");
		while (tab_cmd[i]->tab_pipe && tab_cmd[i]->tab_pipe[++j])
			printf("tab pipe: %s ", tab_cmd[i]->tab_pipe[j]);
		printf("\n");
	}
	printf("-----------------------------------------------------\n");
	return (1);
}

int	ft_search_pipe(char *str)
{
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, ">") || !ft_strcmp(str, "<"))
		return (1);
	return (0);
}

char	**ft_tab_pipe(t_command *tab_cmd)
{
	int	i;
	int	y;

	i = -1;
	y = 0;
	while (tab_cmd->tab_cmd[++i])
		if (ft_search_pipe(tab_cmd->tab_cmd[i]))
			y++;
	if (!y)
		return (NULL);
	tab_cmd->tab_pipe = malloc(sizeof(tab_cmd->tab_pipe) * (y + 1));
	if (!tab_cmd->tab_pipe)
		return (0);
	tab_cmd->tab_pipe[y] = NULL;
	i = -1;
	y = -1;
	while (tab_cmd->tab_cmd[++i])
		if (ft_search_pipe(tab_cmd->tab_cmd[i]))
			tab_cmd->tab_pipe[++y] = tab_cmd->tab_cmd[i];
	return (tab_cmd->tab_pipe);
}

t_command	**ft_parsing(char *line)
{
	char		**tab_parse;
	t_command	*(*tab_cmd);
	int			i;

	if (!line)
		return (0);
	tab_parse = ft_split(line, ';');
	i = ft_doubletab_len(tab_parse);
	tab_cmd = malloc(sizeof(tab_cmd) * (i + 1));
	if (!tab_cmd)
		return (0);
	tab_cmd[i] = NULL;
	i = -1;
	while (tab_cmd[++i])
	{
		tab_cmd[i] = malloc(sizeof(t_command));
		tab_cmd[i]->nb_cmd = i;
		tab_cmd[i]->tab_cmd = ft_split(tab_parse[i], ' ');
		tab_cmd[i]->tab_pipe = ft_tab_pipe(tab_cmd[i]);
	}
	ft_affiche_struc(tab_cmd);
	ft_free_doutab(tab_parse);
	return (tab_cmd);
}
