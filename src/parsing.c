/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/19 17:57:55 by tdelauna         ###   ########.fr       */
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

char	*ft_cut_redirection_out(char *command)
{
	char	*out;
	int		len_to_cut;

	out = ft_strchr(command, '>');
	printf("out : %s\n", out);
	return (out);
}

void	ft_init_t_command(t_command *tab_command)
{
	int	i;

	tab_command->redirection = malloc(sizeof(tab_command->redirection) * 4);
	if (!tab_command)
		return (NULL);
	i = -1;
	while (++i < 4)
		tab_command->redirection[i] = NULL;
}

void	ft_parsing(char *line)
{
	char		**tmp_command;
	t_command	*tab_command;

	ft_init_t_command(tab_command);
	for(int i = 0; i < 4; i++)
		printf("tab_command->redirection %i: %p // %s\n", i,tab_command->redirection[i], tab_command->redirection[i]);


	printf("ft_strchr : %s\n", ft_strchr(line, '>'));
	if (ft_strchr(line, '>'))
	{
		printf("here");
	// 	tab_command->redirection[1] = ft_cut_redirection_out(line);
	// 	// printf("	redirection out %s\n", tab_cmd.redirection[1]);
	}

	// for(int i = 0; i < 4; i++)
	// 	printf("tab_command->redirection %i: %p // %s\n", i,tab_command->redirection[i], tab_command->redirection[i]);

	// tmp_command = ft_split(line, '|');
	// for (int i = 0; tmp_command[i]; i++)
	// 	printf("	tmp command %i %s\n", i, tmp_command[i]);
}
