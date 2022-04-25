/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:50 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Lexing Parsing
 *	Parcourt la line et execute les differentes commandes
 *	Separateur => espaces, '', "", <>, <<>>, |
 *
*/

/*

Les commandes séparées par un ';' sont exécutées successivement,
l'interpréteur attend que chaque commande se termine avant de lancer la suivante
*/
void ft_free_doutab(char **tab)
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

void	ft_parsing(char *line)
{
	char		**tab_parse;
	t_command	*(*command);
	int			i;

	printf("-----------------------------------------------------\n");
	if(line)
	{
		tab_parse = ft_split(line, ';');

	// test

		i = -1;
		printf("******************************************\n");
		printf("line :%s\n", line);
		while (tab_parse[++i])
			printf("parsing %i : %s\n",i, tab_parse[i]);
		printf("******************************************\n");
	}
	command = malloc(sizeof(command) * (i + 1));
	i = -1;
	while (tab_parse[++i])
	{
		command[i]->nb_cmd = i;
		command[i]->tab_cmd = ft_split(tab_parse[i], ' ');
	}
	command[i] = NULL;
	i = 0;
	while(command[i])
	{
		printf("tab_command : %s\n",command[i]->tab_cmd[i]);
		i++;
	}
	ft_free_doutab(tab_parse);
	printf("-----------------------------------------------------\n");

}
