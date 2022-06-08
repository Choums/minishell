/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/08 17:19:04 by aptive           ###   ########.fr       */
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

int main(int ac, char **av, char **envp)
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


	s_sigaction.sa_sigaction = ft_signal;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_sigaction, 0);
	sigaction(SIGQUIT, &s_sigaction, 0);

	get_env(&data, envp);
	// set_var(&data, "test=Hola");
	// set_var(&data, "tdst=Hola");
	// set_var(&data, "Hola");
	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	while (is_exit(&data, line) && line)
	{
		ft_parsing(&data, line);
		free(line);
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		// free_struc(table_pipe)
	}

}
