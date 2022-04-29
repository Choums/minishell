/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/29 21:38:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Env
 *	Recup. toutes les variables d'environement dans une lst.
 *	Cas env -i => PWD, SHLVL et _ et PATH | set_env
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
	// set_var(data, get_path());
}

/*
 *	Permet d'init PATH en cas d'env -i
*/
char	*get_path(void)
{
	
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

void	print_env(t_list **h_env)
{
	t_list	*tmp;

	tmp = (*h_env);
	while (tmp)
	{
		ft_putendl_fd(tmp->content, STDOUT_FILENO);
		tmp = tmp->next;
	}
}
