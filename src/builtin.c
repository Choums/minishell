/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:48:30 by root              #+#    #+#             */
/*   Updated: 2022/05/24 14:19:27 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char *arg)
{
	if (*arg)
		ft_putendl_fd(arg, STDOUT_FILENO);
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
void	unset(t_data *data, char *var)
{
	supp_elem(data->h_env, var);
	supp_elem(data->h_var, var);
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