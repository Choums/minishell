/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/28 18:24:14 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_signal	g_signal;

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

void	main_two(t_data *data, char *line)
{
	t_command	*(*table_pipe);

	table_pipe = NULL;
	if (verif_line(line))
	{
		g_signal.prompt = 1;
		table_pipe = ft_parsing(data, line, table_pipe);
		parse_back_slash(table_pipe);
		go_expand(data, table_pipe);
		parse_quote(table_pipe);
		fusion_tab_redir(table_pipe);
		mother_board(data, table_pipe);
		if (table_pipe)
			free_struc(table_pipe);
		g_signal.prompt = 0;
	}
}

void	exit_signal(t_data *data, char *line)
{
	free(line);
	rl_clear_history();
	ft_lstclear(&data->env, del);
	ft_lstclear(&data->var, del);
	ft_lstclear(&data->path, del);
	exit(EXIT_SUCCESS);
}

char	*which_readline(void)
{
	char	*line;

	line = readline("minishell: ");
	return (line);
}

int	main(int ac, char **av, char **envp)
{
	char				*line;
	t_data				data;
	struct sigaction	s_sigaction;
	sigset_t			block_mask;

	(void)ac;
	(void)av;
	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	signal_init(&s_sigaction, &block_mask);
	sigaction(SIGINT, &s_sigaction, 0);
	sigaction(SIGQUIT, &s_sigaction, 0);
	data_init(&data);
	get_env(&data, envp);
	while (1)
	{
		line = which_readline();
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		main_two(&data, line);
		free(line);
		g_signal.sigint = 0;
	}
	exit_signal(&data, line);
}
