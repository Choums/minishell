/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:41:51 by root              #+#    #+#             */
/*   Updated: 2022/05/30 18:16:25 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
 *	cd
 *	Change le working dir.
 *	Met a jour la var PWD
 *	Met a jour OLDPWD ou la creer
 *	getcwp et chdir
 *	~	=> var HOME	| goto_home
 *	-	=> var OLDPWD | goto_oldpwd
 *	Cas => cwd supp. a prendre en compte
 *
*/
void	change_dir(t_list **h_env, char *path)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
		perror(""); //Gestion d'erreur
	// update_elem(h_env, "OLDPWD=", current);
	free(current);
	if (chdir(path) < 0)
		perror(""); //Gestion d'erreur
	current = getcwd(NULL, 0);
	if (!current)
		perror(""); //Gestion d'erreur
	// update_elem(h_env, "PWD=", current);
	free(current);
}

void	check_dir(t_data *data, char *path)
{
	check_path(data, path);
	if (!is_oldpwd(data->h_env))
		create_oldpwd(data->h_env);
	if (path[0] == '-')
		goto_oldpwd(data->h_env);
	else if (path[0] == '~')
		goto_home(data->h_env);
	else
		change_dir(data->h_env, path);
}

/*
 *	check via access si le path donnee existe ainsi que ses droits, gere le '-' et '~'
*/
void	check_path(t_data *data, char *path)
{
	char	*tmp;

	if (ft_strcmp(path, "-") == 0)
	{
		tmp = get_var(data, "OLDPWD=");
		if (access(tmp, R_OK | X_OK) < 0)
		{
			free(tmp);
			ft_err("cd");
		}
		else
			free(tmp);
	}
	else if (ft_strcmp(path, "~") == 0)
	{
		tmp = get_var(data, "HOME=");
		if (access(tmp, R_OK | X_OK) < 0)
		{
			free(tmp);
			ft_err("cd");
		}
		else
			free(tmp);
	}
	else
		if (access(path, R_OK | X_OK) < 0)
			ft_err("cd");
}

void	goto_home(t_list **h_env)
{
	char	*path;
	t_list	*tmp;

	tmp = (*h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "HOME=", ft_strlen("HOME=")) == 0)
		{
			path = ft_substr(tmp->content, ft_strlen("HOME="), ft_strlen(tmp->content));
			change_dir(h_env, path);
			free(path);
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void	goto_oldpwd(t_list **h_env)
{
	char	*path;
	t_list	*tmp;

	tmp = (*h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			path = ft_substr(tmp->content, ft_strlen("OLDPWD="), ft_strlen(tmp->content));
			change_dir(h_env, path);
			free(path);
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void	create_oldpwd(t_list **h_env)
{
	char	*path;
	char	*var;

	path = getcwd(NULL, 0);
	var = ft_strjoin("OLDPWD=", path);
	free(path);
	ft_lstadd_back(h_env, ft_lstnew(var));
	free(var);
}

/*
 *	Check si la var OLDPWD existe
*/
int	is_oldpwd(t_list **h_env)
{
	t_list	*tmp;

	tmp = (*h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}