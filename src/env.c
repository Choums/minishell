/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:50 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/25 17:15:23 by chaidel          ###   ########.fr       */
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
		get_path(data);
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
			all_paths = ft_substr(tmp->content, ft_strlen("PATH="), ft_strlen(tmp->content));
			paths = ft_split(all_paths, ':');
			free(all_paths);
			set_path(data, paths);
			free_double_tab(paths);
			return ;
		}
		else
			tmp = tmp->next;
	}
	set_var(data, DEFAULT_PATH_VALUE);
	all_paths = ft_substr(DEFAULT_PATH_VALUE, ft_strlen("PATH="), ft_strlen(DEFAULT_PATH_VALUE));
	paths = ft_split(all_paths, ':');
	free(all_paths);
	set_path(data, paths);
	free_double_tab(paths);
	return ;
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
