/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/25 17:03:24 by aptive           ###   ########.fr       */
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
 *	rl_on_new_line ->
 *	rl_replace_line ->
 *	rl_redisplay ->
 *	add_history -> ajoute la saisie a la liste de toutes les saisies.
*/

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_data		data;
	t_command	*(*tab_cmd);

	(void)ac;
	(void)av;
	get_env(&data, envp);
	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	while (is_exit(&data, line))
	{
		//lexing parsing sur line, besoin des var d'env
		tab_cmd = ft_parsing(line);
		if (ft_strcmp(line, "env") == 0)
			print_env(data);
		if (ft_strcmp(line, "unset") == 0)
			unset(&data, "HOME");
		free(line);
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
	}
	(void)tab_cmd;
}
