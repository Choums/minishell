/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/25 17:02:11 by aptive           ###   ########.fr       */
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
		{
			printf("%s ", tab_cmd[i]->tab_cmd[j]);
		}
		printf("\n");
	}
	printf("-----------------------------------------------------\n");
	return (1);
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
	}
	ft_affiche_struc(tab_cmd);
	ft_free_doutab(tab_parse);
	return (tab_cmd);
}
