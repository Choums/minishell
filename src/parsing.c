/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/25 05:17:08 by aptive           ###   ########.fr       */
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

// int	ft_affiche_struc(t_command *(*tab_cmd))
// {
// 	int	i;
// 	int	j;

// 	printf("-----------------------------------------------------\n");
// 	i = -1;
// 	while (tab_cmd[++i])
// 	{
// 		j = -1;
// 		printf("tab_tab_cmd : %i ", tab_cmd[i]->nb_cmd);
// 		while (tab_cmd[i]->tab_cmd[++j])
// 			printf("%s ", tab_cmd[i]->tab_cmd[j]);
// 		j = -1;
// 		printf("\n");
// 		while (tab_cmd[i]->tab_pipe && tab_cmd[i]->tab_pipe[++j])
// 			printf("tab pipe: %s ", tab_cmd[i]->tab_pipe[j]);
// 		printf("\n");
// 	}
// 	printf("-----------------------------------------------------\n");
// 	return (1);
// }

int	ft_search_pipe(char *str)
{
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, ">") || !ft_strcmp(str, "<"))
		return (1);
	return (0);
}

// char	**ft_tab_pipe(char *line)
// {
// 	int	i;
// 	int	y;

// 	i = -1;
// 	y = 0;
// 	while (tab_cmd->tab_cmd[++i])
// 		if (ft_search_pipe(tab_cmd->tab_cmd[i]))
// 			y++;
// 	if (!y)
// 		return (NULL);
// 	tab_cmd->tab_pipe = malloc(sizeof(tab_cmd->tab_pipe) * (y + 1));
// 	if (!tab_cmd->tab_pipe)
// 		return (0);
// 	tab_cmd->tab_pipe[y] = NULL;
// 	i = -1;
// 	y = -1;
// 	while (tab_cmd->tab_cmd[++i])
// 		if (ft_search_pipe(tab_cmd->tab_cmd[i]))
// 			tab_cmd->tab_pipe[++y] = tab_cmd->tab_cmd[i];
// 	return (tab_cmd->tab_pipe);
// }


// int	ft_init_t_command(t_command *tab_command)
// {
// 	int	i;

// 	tab_command->redirection = malloc(sizeof(tab_command->redirection) * 4);
// 	if (!tab_command)
// 		return (0);
// 	i = -1;
// 	while (++i < 3)
// 		tab_command->redirection[i] = NULL;
// 	return (1);
// }



// void ft_affichage_parse(t_command tab_command)
// {
// 	printf("\n\033[31m ************	REDIRECTION	************************\n\033[0m");
// 	for (int i = 0; i < 3; i++)
// 		printf("tab_command->redirection %i: %p // %s\n", i,tab_command.redirection[i], tab_command.redirection[i]);
// 	printf("\033[31m ************	TABLEAU DE COMMANDE	****************\n\033[0m");
// 	for (int i = 0; tab_command.tab_cmd[i]; i++)
// 		printf("tab_cmd[%i] : %s\n", i, tab_command.tab_cmd[i]);
// 	printf("\033[32m-----------------------------------------------------\033[0m\n");
// }

int	ft_lendoubletab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_tab_pip(char *line, t_redirection *tab_redirection)
{
	int	i;

	i = -1;
	tab_redirection->token_in = 0;
	tab_redirection->token_out = 0;
	while (line[++i])
	{
		if(line[i] == '<')
		{
			i++;
			if (line[i] == '<')
				tab_redirection->token_in = 2;
			else
				tab_redirection->token_in = 1;
		}
		if(line[i] == '>')
		{
			i++;
			if (line[i] == '>')
				tab_redirection->token_out = 2;
			else
				tab_redirection->token_out = 1;
		}
	}
}

void	ft_parsing(char *line)
{
	char **tab_in_tmp;
	char **tab_out_tmp;
	t_redirection	tab_redirection;

	t_command	tab_command_tmp;
	t_command	*(*tab_command);

	if (!ft_strlen(line))
		return;

	tab_in_tmp = ft_split(line, '<');
	tab_out_tmp = ft_split(line, '>');

	if (ft_doubletab_len(tab_in_tmp) != 1)
		tab_redirection.in = tab_in_tmp[0];
	else
		tab_redirection.in = NULL;

	if (ft_doubletab_len(tab_out_tmp) != 1)
		tab_redirection.out = tab_out_tmp[1];
	else
		tab_redirection.out = NULL;

	int	i = 0;

	char *command_tmp;
	while(tab_out_tmp[0][i] != '<' && tab_out_tmp[0][i])
		i++;
	while(tab_out_tmp[0][i] == '<')
		i++;
	if((size_t)i != ft_strlen(tab_out_tmp[0]))
		command_tmp = tab_out_tmp[0] + i;
	else
		command_tmp = tab_out_tmp[0];

	tab_command_tmp.tab_cmd = ft_split(command_tmp, ' ');

	ft_tab_pip(line, &tab_redirection);



	i = -1;
	tab_command = malloc(sizeof(tab_command));
	tab_command[0] = malloc(sizeof(tab_command[0]));
	tab_command[0]->tab_cmd = malloc(sizeof(tab_command[0]->tab_cmd) * 10);
	while (tab_command_tmp.tab_cmd[++i])
	{
		if (!ft_strcmp(tab_command_tmp.tab_cmd[i], "|"))
			break;
		else
			tab_command[0]->tab_cmd[i] = tab_command_tmp.tab_cmd[i];
		printf("tab_command[0]->tab_cmd[%i]: %s\n", i, tab_command[0]->tab_cmd[i]);

	}
	printf("tab_redirection.in: %s\n", tab_redirection.in);
	printf("tab_redirection.token_in: %i\n", tab_redirection.token_in);
	printf("tab_redirection.out: %s\n", tab_redirection.out);
	printf("tab_redirection.token_in: %i\n", tab_redirection.token_out);

	for (int i = 0; tab_command_tmp.tab_cmd[i]; i++)
		printf("tab_command_tmp.tab_cmd[%i]: %s\n", i, tab_command_tmp.tab_cmd[i]);

	for (int i = 0; tab_command[0]->tab_cmd[i]; i++)
		printf("tab_command[0]->tab_cmd[%i]: %s\n", i, tab_command[0]->tab_cmd[i]);


}
