/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/04 20:06:43 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
 *	Creer les variables d'env.
 *	--------------------------
 *	getenv -> char *getenv(const char *varname)
 *	retourne une string avec la valeur de la var donner || renvoie la var PATH malgre qu'elle soit unset
 *	ex: getenv("PATH")
 *	cas env -i a gerer -> PWD, SHLVL, _
 *	var de base -> TERM, SHELL, USER, PATH, PWD, LANG, HOME,
 *	LANGUAGE, LOGNAME, _, SHLVL
*/

/*
 *	Prompt
 *	readline -> affiche un prompt et attend une saisie (le \n n'est pas pris en compte).
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
		table_pipe = ft_parsing(data, line, table_pipe);
		parse_quote(table_pipe);
		parse_back_slash(table_pipe);
		go_expand(data, table_pipe);
		// ft_affiche_t_command(table_pipe);
		if (table_pipe[0]->tab_cmd[0])
			mother_board(data, table_pipe);
		free_struc(table_pipe);
	}
}

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
	while (is_exit(&data, line) && line)
	{
		g_signal.nt_status = 0;
		// printf("g_signal.status : %i\n", g_signal.pid);
		if (ft_strcmp(line, "var") == 0)
			print_vars(data.h_var);
		main_two(&data, line);
		free(line);
		line = readline("minishell: ");
		if (line && *line)
			add_history(line);
	}
}
