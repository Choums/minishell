/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/22 13:32:36 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Creer les variables d'env.
 *	--------------------------
 *	getenv -> char *getenv(const char *varname)
 *	retourne une string avec la valeur de la var donner
 *	ex: getenv("PATH")
 *	cas env -I a gerer -> PWD, SHLVL, _
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
	char	*line;
	t_data	data;
	
	(void)ac;
	(void)av;

	get_env(&data, envp);

	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	while (ft_strcmp(line, "exit") != 0)
	{
		if(ft_strcmp(line, "env") == 0)
		{
			printf("in\n");
			print_env(data);
		}
		free(line);
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		//lexing parsing sur line, besoin des var d'env
		
	}
	rl_clear_history();
	return (0);
}