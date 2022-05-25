/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/25 19:28:06 by tdelauna         ###   ########.fr       */
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

void ft_affichage_redirection(t_redirection	tab_redirection)
{
	printf("\033[31m***************** redirection **************************************\033[0m\n");
	printf("tab_redirection.in: \033[1;32m%s\033[0m\n", tab_redirection.in);
	printf("tab_redirection.token_in: \033[1;32m%i\033[0m\n", tab_redirection.token_in);
	printf("tab_redirection.out: \033[1;32m%s\033[0m\n", tab_redirection.out);
	printf("tab_redirection.token_in: \033[1;32m%i\033[0m\n", tab_redirection.token_out);

	printf("\033[31m***************** END **********************************************\033[0m\n");
}

// "\033[31m ROUGE \033[0m"

char	*ft_redirection_io(t_redirection *tab_redirection, char *line)
{
	char **tab_in_tmp;
	char **tab_out_tmp;
	char *tmp;

	if(ft_strchr(line, '<'))
	{
		tmp = ft_strchr_after(line, '<');
		tab_in_tmp = ft_split(tmp, ' ');
		tab_redirection->in = tab_in_tmp[0];

	}
	else
		tab_redirection->in = NULL;




	// for (int i =0; tab_in_tmp[i]; i++)
		printf("tmp: %s\n", tmp);







	tab_out_tmp = ft_split(line, '>');
	if (ft_doubletab_len(tab_out_tmp) != 1)
		tab_redirection->out = tab_out_tmp[1];
	else
		tab_redirection->out = NULL;
	ft_tab_pip(line, tab_redirection);
	return (tab_out_tmp[0]);
}

// void	ft_line_to_arg(tab_out_tmp[0]);
// {

// }

// void	ft_parsing(char *line)
// {
// 	t_redirection	tab_redirection;
// 	t_command	tab_command_tmp;
// 	char	*tab_out_tmp;

// 	if (!ft_strlen(line))
// 		return;

// 	tab_out_tmp = ft_redirection_io(&tab_redirection, line);

// 	int	i = 0;
// 	t_command	*(*tab_command);

// 	char *command_tmp;
// 	while(tab_out_tmp[i] != '<' && tab_out_tmp[i])
// 		i++;
// 	while(tab_out_tmp[i] == '<')
// 		i++;
// 	if((size_t)i != ft_strlen(tab_out_tmp))
// 		command_tmp = tab_out_tmp + i;
// 	else
// 		command_tmp = tab_out_tmp;

// 	tab_command_tmp.tab_cmd = ft_split(command_tmp, ' ');



// 	// i = -1;
// 	// tab_command = malloc(sizeof(tab_command));
// 	// tab_command[0] = malloc(sizeof(tab_command[0]));
// 	// tab_command[0]->tab_cmd = malloc(sizeof(tab_command[0]->tab_cmd) * 10);
// 	// while (tab_command_tmp.tab_cmd[++i])
// 	// {
// 	// 	if (!ft_strcmp(tab_command_tmp.tab_cmd[i], "|"))
// 	// 		break;
// 	// 	else
// 	// 		tab_command[0]->tab_cmd[i] = tab_command_tmp.tab_cmd[i];
// 	// 	printf("tab_command[0]->tab_cmd[%i]: %s\n", i, tab_command[0]->tab_cmd[i]);

// 	// }


// 	ft_affichage_redirection(tab_redirection);

// 	for (int i = 0; tab_command_tmp.tab_cmd[i]; i++)
// 		printf("tab_command_tmp.tab_cmd[%i]: %s\n", i, tab_command_tmp.tab_cmd[i]);

// 	// for (int i = 0; tab_command[0]->tab_cmd[i]; i++)
// 	// 	printf("tab_command[0]->tab_cmd[%i]: %s\n", i, tab_command[0]->tab_cmd[i]);


// }

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

void	ft_parsing(char *line)
{
	char		**tmp;
	t_command	*(*table_pipe);

	if (!ft_strlen(line))
		return;


	// table_pipe = malloc(sizeof(table_pipe) * (ft_count_pipe(line) + 1));
	// if (!table_pipe)
	// 	return;
	// table_pipe[ft_count_pipe(line)] = NULL;


	int i;

	i = -1;
	while (++i <= ft_count_pipe(line))
	{
		table_pipe[i] = malloc(sizeof(t_command) * (1));
		if (!table_pipe[i])
			return;
	}
	table_pipe[ft_count_pipe(line)] = NULL;




	for (int i = 0; table_pipe[i]; i++)
		printf("table_pipe[%i]:%p\n", i, table_pipe[i]);

	tmp = ft_split(line, '|');

	for (int i = 0; tmp[i]; i++)
		printf("tmp[%i]:%s\n", i, tmp[i]);



	i = -1;
	while (tmp[++i])
		table_pipe[i]->all_pipe = tmp[i];

	for (int i = 0; i < 2; i++)
		printf("table_pipe[%i]:%s\n", i, table_pipe[i]->all_pipe);


}
