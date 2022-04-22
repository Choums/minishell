/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/22 19:25:47 by tdelauna         ###   ########.fr       */
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

void	ft_parsing(char *line)
{
	char	**tab_parse;

	if(line)
	{
		tab_parse = ft_split(line, ';');

	// test
		int	i;

		i = -1;
		printf("******************************************\n");
		printf("line :%s\n", line);
		while (tab_parse[++i])
			printf("parsing %i : %s\n",i, tab_parse[i]);
		printf("******************************************\n");
	}
	
}
