/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:48:30 by root              #+#    #+#             */
/*   Updated: 2022/06/06 19:46:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **arg)
{
	size_t	i;

	i = 1;
	if (ft_strcmp(arg[i], "-n")) //affichage sans nl
	{
		i++;
		while (arg[i])
			ft_putstr_fd(arg[i], STDIN_FILENO);
	}
	else //affichqge avec nl
		while (arg[i])
			ft_putendl_fd(arg[i++], STDIN_FILENO);
}

/*
 *	unset [var]
 *	Supp. la var
 *	Supp. le maillon de la lst. var et env.
 *	tmp->previous->next = tmp->next
 *	tmp->next->previous = tmp->previous
 *	Cas	=> Premier	| head vers next, free(tmp), head previous NULL
 *		=> Milieu	| redirection previous et next de tmp, free(tmp)
 *		=> Fin		| lst = tmp, tmp->previous->next NULL, free(lst)
*/
void	unset(t_data *data, char **var)
{
	size_t	i;

	i = 0;
	while (var[i])
	{
		supp_elem(data->h_env, var);
		supp_elem(data->h_var, var);
		i++;
	}
}

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror(""); //Gestion d'erreur
	echo(path);
	free(path);
}

int	is_exit(t_data *data, char *line)
{
	if (line)
	{
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			rl_clear_history();
			ft_lstclear(&data->env, del);
			ft_lstclear(&data->var, del);
			ft_lstclear(&data->path, del);
			exit(EXIT_SUCCESS);
		}	
	}
	return (1);
}