/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:38:58 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/27 17:43:48 by root             ###   ########.fr       */
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
	char	*line;
	t_data	data;
	
	(void)ac;
	(void)av;

	get_env(&data, envp);
	data.h_var = &data.var;
	data.var = ft_lstnew("test=salut");
	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	while (is_exit(&data, line))
	{
		if(ft_strcmp(line, "env") == 0)
			print_env(data);
		if (ft_strcmp(line, "pwd") == 0)
			pwd();
		if (ft_strcmp(line, "cd") == 0)
			check_dir(&data, "~");
		free(line);
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		//lexing parsing sur line, besoin des var d'env
		
	}
}