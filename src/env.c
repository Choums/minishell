/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/26 10:27:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Env
 *	Recup. toutes les variables d'environement dans une lst.
 *	Cas env -i => PWD, SHLVL et _ a set
*/
void	get_env(t_data *data, char **env)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (env[i])
	{
		while (env[i])
			i++;	
		data->env = ft_lstnew(env[n++]);
		while (n < i)
			ft_lstadd_back(&data->env, ft_lstnew(env[n++]));
		data->h_env = &data->env;	
	}
	else
		set_env(data);
}

void	set_env(t_data *data)
{
	char	*path;
	char	*var;
	
	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("failed to get current directory\n"); //gestion d'erreur a faire
	var = ft_strjoin("PWD=", path);
	free(path);
	data->env = ft_lstnew(var);
	free(var);
	ft_lstadd_back(&data->env, ft_lstnew("SHLVL=1"));
	ft_lstadd_back(&data->env, ft_lstnew("_=/usr/bin/env"));
	data->h_env = &data->env;
}

/*
 *	export [var]
 *	export -> ajoute la var a l'env.
 *	La var est mise en fin de chaine
*/
void	export(t_data *data, char *var)
{
	t_list	*tmp;
	
	tmp = data->var;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, var, ft_strlen(var)))
		{
			ft_lstadd_back(&data->env, ft_lstnew(tmp->content));
			return ;
		}
		else
			tmp = tmp->next;
	}
}

/*
 *	unset [var]
 *	Supp. la var (aussi de l'env.)
 *	Supp. le maillon de la var
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

void	print_env(const t_data data)
{
	t_list	*tmp;

	tmp = data.env;
	while (tmp)
	{
		ft_putendl_fd(tmp->content, STDOUT_FILENO);
		tmp = tmp->next;
	}
}
