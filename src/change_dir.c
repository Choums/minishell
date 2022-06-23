/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:41:51 by root              #+#    #+#             */
/*   Updated: 2022/06/23 16:29:32 by chaidel          ###   ########.fr       */
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
 *	-------------------------------------
 *	Cas de dir precedent supp
 *		=>	Doit pouvoir se rendre au HOME
*/
void	change_dir(t_data *data, char *path)
{
	char	*current;
	char	*var;

	current = getcwd(NULL, 0);
	if (!current)
		perror("");
	var = ft_strjoin("OLDPWD=", current);
	free(current);
	update_elem(data, var);
	free(var);
	if (chdir(path) < 0)
		perror("");
	current = getcwd(NULL, 0);
	if (!current)
		perror("");
	var = ft_strjoin("PWD=", current);
	free(current);
	update_elem(data, var);
	free(var);
}

/*
 *	Vérifie le chemin et définis le changement
*/
void	check_dir(t_data *data, char **args)
{
	if (ft_doubletab_len(args) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return ;
	}
	if (!check_path(data, args[1]))
		return ;
	printf("path: %s\n", args[1]);
	if (!args[1] || ft_strncmp(args[1], "~", 1) == 0)
	{
		goto_home(data);
		return ;
	}
	if (ft_strncmp(args[1], "-", 1) == 0)
	{
		goto_oldpwd(data);
		return ;
	}
	change_dir(data, args[1]);
}

/*
 *	check via access si le path donnee existe ainsi que ses droits
 *	gere le '-' et '~'
*/
int	check_path(t_data *data, char *path)
{
	char	*tmp;

	if (!path || ft_strncmp(path, "~", 1) == 0)
	{
		if (!get_elem(data->h_env, "HOME"))
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (0);
		}
		tmp = get_var(data, "HOME=");
		if (access(tmp, F_OK) < 0)
		{
			printf("home err\n");
			free(tmp);
			return (0);
		}
		else
			free(tmp);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		if (!get_elem(data->h_env, "OLDPWD"))
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
			return (0);
		}
		tmp = get_var(data, "OLDPWD=");
		if (stat(path, ) < 0)
		{
			free(tmp);
			perror("");
			return (0);
		}
		else
			free(tmp);

	}
	else if (access(path, R_OK | X_OK) < 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		return (0);
	}
	return (1);
}

void	goto_home(t_data *data)
{
	char	*path;
	t_list	*tmp;

	tmp = *(data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "HOME=", ft_strlen("HOME=")) == 0)
		{
			path = ft_substr(tmp->content, ft_strlen("HOME="), ft_strlen(tmp->content));
			change_dir(data, path);
			free(path);
			return ;
		}
		tmp = tmp->next;
	}
}

void	goto_oldpwd(t_data *data)
{
	char	*path;
	t_list	*tmp;

	tmp = *(data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			path = ft_substr(tmp->content, ft_strlen("OLDPWD="), ft_strlen(tmp->content));
			change_dir(data, path);
			ft_putendl_fd(path, STDOUT_FILENO);
			free(path);
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void	create_oldpwd(t_data *data)
{
	char	*path;
	char	*var;

	path = getcwd(NULL, 0);
	var = ft_strjoin("OLDPWD=", path);
	free(path);
	ft_lstadd_back(data->h_env, ft_lstnew(var));
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