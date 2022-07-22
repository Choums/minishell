/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/22 20:39:06 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Prompt
 *	readline -> affiche un prompt et attend une saisie
 *				(le \n n'est pas pris en compte).
 *	rl_clear_history ->	Supp. l'historique des saisies.
 *	rl_on_new_line -> Pour gérer le Ctrl + \ | 1
 *	rl_replace_line ->
 *	rl_redisplay -> Pour gérer le Ctrl + \ | 2
 *	add_history -> ajoute la saisie a la liste de toutes les saisies.
 *	-----------------
 *	Ajouter la pos au prompt
*/


void	free_list(t_list *list)
{
	int	i;
	// t_list *tmp_list

	i = 0;
	while(list)
	{
		// printf("List %i : %p / %s\n", i, list, list->content);
		free(list->content);
		if(list->previous)
			free(list->previous);
		list = list->next;
		i++;
	}
}

void	print_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("List %i : %p / %s\n", i, list, list->content);
		list = list->next;
		i++;
	}
}


// void	free_data(t_data *data)
// {
// 	print_list(data->env);
// 	// free_list(data->h_env);
// 	free_list(data->var);
// 	// free_list(data->h_var);
// 	free_list(data->path);
// 	// printf("data env : %p\n", data->env);
// 	// printf("data h_env : %p\n", data->h_env);
// 	// printf("data var : %p\n", data->var);
// 	// printf("data h_var : %p\n", data->h_var);
// 	// printf("data path : %p\n", data->path);
// 	// printf("data pipefd : %p\n", data->pipefd);

// }

void	main_two(t_data *data, char *line)
{
	t_command	*(*table_pipe);

	table_pipe = NULL;
	if (verif_line(line))
	{
		table_pipe = ft_parsing(data, line, table_pipe);
		parse_back_slash(table_pipe);
		go_expand(data, table_pipe);
		parse_quote(table_pipe);
		fusion_tab_redir(table_pipe);
		// ft_affiche_t_command(table_pipe);
		if (table_pipe[0]->tab_cmd[0])
			mother_board(data, table_pipe);
		// printf("g_signal.status : %i\n",g_signal.status);
		// free_data(data);
		free_struc(table_pipe);
	}
}
// ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
void exit_signal(t_data *data, char *line)
{
	free(line);
	rl_clear_history();
	ft_lstclear(&data->env, del);
	ft_lstclear(&data->var, del);
	ft_lstclear(&data->path, del);
	exit(EXIT_SUCCESS);
}

t_signal	g_signal;

int		main(int ac, char **av, char **envp)
{
	char				*line;
	t_data				data;
	struct sigaction	s_sigaction;
	pid_t				pid_server;
	sigset_t			block_mask;

	signal_init();

	(void)ac;
	(void)av;
	(void)pid_server;
	(void)block_mask;
	data.var = NULL;
	data.path = NULL;
	data.pipefd = NULL;
	s_sigaction.sa_sigaction = ft_signal;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_sigaction, 0);
	sigaction(SIGQUIT, &s_sigaction, 0);

	get_env(&data, envp);
	line = readline("minishell: ");
	if (line && *line)
		add_history(line);
	while (1 && line)
	{
		g_signal.nt_status = 0;
		main_two(&data, line);
		free(line);
		line = readline("minishell: ");
		if (line && *line)
			add_history(line);
	}
	exit_signal(&data, line);
}
