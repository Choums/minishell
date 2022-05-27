/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:29:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/27 02:37:47 by aptive           ###   ########.fr       */
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

void	ft_affiche_t_command(t_command	*(*table_pipe))
{
	printf("\n\n\033[31m***************** tableau_t_command ******************************************\033[0m\n");
	for (int i = 0; table_pipe[i]; i++)
		printf("table_pipe[%i]:\033[1;32m%p\033[0m\n", i, table_pipe[i]);
	printf("\033[31m***************** all_pipe ***************************************************\033[0m\n");
	for (int i = 0; table_pipe[i]; i++)
		printf("table_pipe->all_pipe[%i]:\033[1;32m%s\033[0m\n", i, table_pipe[i]->all_pipe);
	printf("\033[31m***************** tab_cmd ****************************************************\033[0m\n");
	for (int i = 0; table_pipe[i]; i++)
	{
		for (int j = 0; table_pipe[i]->tab_cmd[j]; j++)
			printf("table_pipe[%i]->tab_cmd[%i]:\033[1;32m%s\033[0m\n", i, j,table_pipe[i]->tab_cmd[j]);
	}
	printf("\033[31m***************** tab_redirection ****************************************************\033[0m\n");

	// printf("table_pipe[0]->tab_redirection: %p\n", table_pipe[0]->tab_redirection);
	// for(int	i = 0; table_pipe[0]->tab_redirection->in[i]; i++)
	// 	// printf("table_pipe[0]->tab_redirection.in: %p\n", table_pipe[0]->tab_redirection->in);

	// for(int	i = 0; table_pipe[0]->tab_redirection->in[i]; i++)
	// 	printf("table_pipe[0]->tab_redirection.in[%i]:%p\n", i, table_pipe[0]->tab_redirection->in[i]);

	if(table_pipe[0]->tab_redirection)
		for(int	i = 0; table_pipe[0]->tab_redirection->in[i]; i++)
			printf("table_pipe[0]->tab_redirection.in[%i]:%s\n", i,table_pipe[0]->tab_redirection->in[i]);


	printf("\033[31m***************** END ********************************************************\033[0m\n\n");
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

t_command	**ft_parse_cmd(t_command	*(*table_pipe))
{
	char *tmp;
	int	to_cut;
	int	k;
	int	index;

	k = -1;
	index = 0;
	while (table_pipe[++k])
	{
		to_cut = 0;
		if (ft_strchr_after(table_pipe[k]->all_pipe, '<'))
		{
			tmp = ft_strchr_after(table_pipe[k]->all_pipe, '<');
			while (tmp[index] && (tmp[index] == '<' || tmp[index] == ' '))
				index++;
			while (tmp[index] && tmp[index] != ' ' )
				index++;
			tmp = tmp + index;
			// printf("index %i\n", index);
			// printf("tmp : %s\n", tmp);
		}
		else
			tmp = table_pipe[k]->all_pipe;



		while(tmp[to_cut] && tmp[to_cut] != '>')
			to_cut++;
		tmp = ft_substr(tmp, 0, to_cut);
		table_pipe[k]->tab_cmd = ft_split(tmp, ' ');
		// printf ("tmp = %s\n", tmp);
		free(tmp);
	}
	return (table_pipe);
}
//< infile cmd1 -opt1 > outfile | < infile2 cmd2 -opt2 > outfile2
//cmd1 -opt1 <infile

int	ft_count_redirection_in(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while(str[++i])
	{
		if (str[i] == '<')
		{
			if (str[++i])
				count++;
			else
				count++;
		}
	}
	return (count);
}

t_command	**ft_redirection_in_init(t_command	*(*table_pipe))
{
	int nb_pipe;

	nb_pipe = ft_count_redirection_in(table_pipe[0]->all_pipe);


	table_pipe[0]->tab_redirection = malloc(sizeof(t_redirection));
	if(!table_pipe[0]->tab_redirection)
		return (NULL);

	if (nb_pipe)
	{
		table_pipe[0]->tab_redirection->in = malloc(sizeof(char **) * (nb_pipe + 1));
		if(!table_pipe[0]->tab_redirection->in)
			return (NULL);
		table_pipe[0]->tab_redirection->in[nb_pipe] = NULL;
	}
	else
		table_pipe[0]->tab_redirection = NULL;

	printf("nb_pipe :%i\n", nb_pipe);
	return (table_pipe);
}

t_command	**ft_parse_redirection_in(t_command	*(*table_pipe))
{
	char	*tmp;
	int		to_cut;
	int		index;
	int	i;


	table_pipe = ft_redirection_in_init(table_pipe);

	i = 0;

	int nb_redirect_in;

	nb_redirect_in = ft_count_redirection_in(table_pipe[0]->all_pipe);

	tmp = table_pipe[0]->all_pipe;
	printf("nb_redirect_in : %i\n", nb_redirect_in);
	while (nb_redirect_in)
	{
		to_cut = 0;
		index = 0;
		tmp = ft_strchr(tmp, '<');
		printf("OK\n");
		printf("HERE tmp :%s\n", tmp);
		while (tmp[index] == '<' || tmp[index] == ' ')
			index++;
		while ((tmp[index + to_cut] != ' ' && tmp[index + to_cut] != '<') && tmp[index + to_cut])
			to_cut++;
		table_pipe[0]->tab_redirection->in[i] = ft_substr(tmp, index, to_cut);
		tmp = tmp + index;
		nb_redirect_in--;
		i++;
	}
	printf("SORTIE\n");
	// if (ft_strchr(table_pipe[0]->all_pipe, '<'))
	// {
	// 	tmp = ft_strchr(table_pipe[0]->all_pipe, '<');
	// 	to_cut = 0;
	// 	index = 0;
	// 	printf("tmp : %s\n", tmp);
	// 	// printf("index : %i\n", index);
	// 	// printf("to_cut: %i\n", to_cut);
	// 	table_pipe[0]->tab_redirection->in[0] = ft_substr(tmp, index, to_cut);
	// }
	// else
	// 	table_pipe[0]->tab_redirection->in[0] = NULL;


	return(table_pipe);
}

void	ft_parsing(char *line)
{
	t_command	*(*table_pipe);

	if (!ft_strlen(line))
		return;
	table_pipe = ft_parse_pipe(table_pipe, line);
	table_pipe = ft_parse_cmd(table_pipe);
	table_pipe = ft_parse_redirection_in(table_pipe);

		printf("ICI\n");


	ft_affiche_t_command(table_pipe);


}
