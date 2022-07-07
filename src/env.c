/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/07 18:34:28 by root             ###   ########.fr       */
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
		printf("found\n");
		value = get_var(data, "SHLVL");
		sub = ft_atoi(value);
		free(value);
		if (sub == 1)
		{
			sub++;
		}
		else
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

/*
 *	Recupere tout les chemins possible et les place dans la lst. path
 *	Si path est NULL => DEFAULT_PATH_VALUE
*/
void	get_path(t_data *data)
{
	t_list	*tmp;
	char	**paths;
	char	*all_paths;

	tmp = (*data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PATH=", ft_strlen("PATH=")) == 0)
		{
			set_var(data, tmp->content);
			all_paths = ft_substr(tmp->content, 5, ft_strlen(tmp->content));
			paths = ft_split(all_paths, ':');
			free(all_paths);
			set_path(data, paths);
			free_double_tab(paths);
			return ;
		}
		else
			tmp = tmp->next;
	}
	set_def_path(data);
}

void	set_def_path(t_data *data)
{
	char	**paths;
	char	*all_paths;

	set_var(data, DEF);
	all_paths = ft_substr(DEF, ft_strlen("PATH="), ft_strlen(DEF));
	paths = ft_split(all_paths, ':');
	free(all_paths);
	set_path(data, paths);
	free_double_tab(paths);
}

/*
 *	Permet d'init la lst. des paths
*/
void	set_path(t_data *data, char **path)
{
	int	i;

	i = 0;
	data->path = ft_lstnew(path[i++]);
	while (path[i])
		ft_lstadd_back(&data->path, ft_lstnew(path[i++]));
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
