/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/21 15:05:44 by chaidel          ###   ########.fr       */
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
		check_prim(data);
		get_path(data);
	}
	else
		set_env(data);
}

/*
 *	verifie que les var primordiales soient transférées
 *	sinon elles sont creés
 *	-------------------------------------
 *	prim var
 *	SHLVL
 *	OLDPWD PWD
 *	'_'
*/
void	check_prim(t_data *data)
{
	char	*path;
	char	*var;

	if (!get_elem(data->h_env, "PWD"))
	{
		path = getcwd(NULL, 0);
		var = ft_strjoin("PWD=", path);
		free(path);
		ft_lstadd_back(&data->env, ft_lstnew(var));
		free(var);
	}
	if (!get_elem(data->h_env, "OLDPWD"))
		data->env = ft_lstnew("OLDPWD");
	inception(data);
}

/*
 *	Verifie si la var SHLVL existe sinon l'a cree
 *	Si elle existe, sa valeur est incr
 *	Sinon elle est mise a 0
*/
void	inception(t_data *data)
{
	char	*value;
	char	*var;
	int		sub;

	if (get_elem(data->h_env, "SHLVL"))
	{
		value = get_var(data, "SHLVL");
		sub = ft_atoi(value);
		free(value);
		sub++;
		value = ft_itoa(sub);
		var = ft_strjoin("SHLVL=", value);
		free(value);
		update_elem(data, var);
		free(var);
	}
	else
		ft_lstadd_back(data->h_env, ft_lstnew("SHLVL=0"));
}

void	set_env(t_data *data)
{
	char	*path;
	char	*var;

	path = getcwd(NULL, 0);
	var = ft_strjoin("PWD=", path);
	free(path);
	data->env = ft_lstnew("OLDPWD");
	ft_lstadd_back(&data->env, ft_lstnew(var));
	free(var);
	ft_lstadd_back(&data->env, ft_lstnew("SHLVL=1"));
	ft_lstadd_back(&data->env, ft_lstnew("_=/usr/bin/env"));
	data->h_env = &data->env;
	get_path(data);
}

int	print_env(t_list **h_env)
{
	t_list	*tmp;

	tmp = (*h_env);
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			ft_putendl_fd(tmp->content, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (1);
}
