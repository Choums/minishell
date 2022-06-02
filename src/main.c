/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/02 16:08:14 by chaidel          ###   ########.fr       */
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

data = NULL;

int main(int ac, char **av, char **envp)
{
	char	*line;
	// t_data	data;
	
	(void)ac;
	(void)av;
	// data.var = NULL;
	data.path = NULL;
	get_env(&data, envp);
	// set_var(&data, "test=Hola");
	// set_var(&data, "tdst=Hola");
	// set_var(&data, "Hola");
	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	while (is_exit(&data, line))
	{
		// if (ft_strcmp(line, "test") == 0)
		// 	export(&data, "test+=");
		// if (ft_strcmp(line, "x") == 0)
		// 	export(&data, NULL);
		// if (ft_strcmp(line, "env") == 0)
		// 	print_env(data.h_env);
		// if (ft_strcmp(line, "var") == 0)
		// 	print_vars(data.h_var);
		ft_parsing(&data, line);
		free(line);
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
	}
}
