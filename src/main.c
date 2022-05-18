/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/18 17:14:29 by chaidel          ###   ########.fr       */
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
 *	-----------------
 *	Ajouter la pos au prompt
*/

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	char	**args;

	args[0] = "cat";
	args[1] = "Hola";
	args[2] = NULL;	
	(void)ac;
	(void)av;

	data.var = NULL;
	data.path = NULL;
	get_env(&data, envp);
	set_var(&data, "test=content");
	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	while (is_exit(&data, line))
	{
		if(ft_strcmp(line, "cat") == 0)
			process(&data, "cat", args, envp);
		free(line);
		line = readline("minishell: ");
		if (line && *line)
			add_history(line);
		//lexing parsing sur line, besoin des var d'env
		
	}
}