/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:41:51 by root              #+#    #+#             */
/*   Updated: 2022/07/08 00:09:45 by aptive           ###   ########.fr       */
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
void	change_dir(t_data *data, char *path, int alloc)
{
	char	*current;
	char	*var;

	current = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (current)
		{
			if (!is_oldpwd(data->h_env))
				create_oldpwd(data);
			var = ft_strjoin("OLDPWD=", current);
			free(current);
			update_elem(data, var);
			free(var);
		}
		current = getcwd(NULL, 0);
		if (current)
		{
			var = ft_strjoin("PWD=", current);
			free(current);
			update_elem(data, var);
			free(var);
		}
		if (alloc)
			free(path);
		return ;
	}
	free(current);
	change_err(path, alloc);
}

/*
 *	Vérifie le chemin et définis le changement
*/
int	check_dir(t_data *data, char **args)
{
	if (ft_doubletab_len(args) > 2)
	{
		g_signal.status = 1;
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (!args[1] || (ft_strncmp(args[1], "~", 1) == 0)
		|| ft_strncmp(args[1], "--", 2) == 0)
	{
		if (args[1] && ft_strncmp(args[1], "~/", 2) == 0)
		{
			goto_homepath(data, args[1]);
			return (0);
		}
		goto_home(data);
		return (0);
	}
	if (ft_strncmp(args[1], "-", 1) == 0)
	{
		goto_oldpwd(data);
		return (0);
	}
	change_dir(data, args[1], 0);
	return (0);
}

int	goto_homepath(t_data *data, char *path)
{
	char	*home_path;
	char	*tmp;
	char	*clean_path;

	home_path = get_elem(data->h_env, "HOME");
	if (home_path)
	{
		tmp = ft_substr(home_path, ft_strlen("HOME="), ft_strlen(home_path));
		clean_path = ft_substr(path, 1, ft_strlen(path));
		home_path = ft_join(tmp, clean_path);
		free(clean_path);
		change_dir(data, home_path, 1);
		return (1);
	}
	ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	return (0);
}

/*
 *	Check les droits du dir
*/
int	change_err(char *pathname, int alloc)
{
	struct stat	path_stat;

	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	if (stat(pathname, &path_stat) < 0)
	{
		// printf("TESST\n");
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_signal.status = 1;
	}
	else if ((path_stat.st_mode & __S_IFREG))
	{
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
		g_signal.status = 1;
	}
	else if ((path_stat.st_mode & S_IXUSR) == 0)
	{
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		g_signal.status = 1;
	}
	if (alloc)
		free(pathname);
	// printf("g_signal %i\n", g_signal.status);
	return (1);
}

int	goto_home(t_data *data)
{
	char	*path;
	t_list	*tmp;

	tmp = *(data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "HOME=", ft_strlen("HOME=")) == 0)
		{
			path = ft_substr(tmp->content,
					ft_strlen("HOME="), ft_strlen(tmp->content));
			change_dir(data, path, 0);
			free(path);
			return (1);
		}
		tmp = tmp->next;
	}
	ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	return (0);
}

int	goto_oldpwd(t_data *data)
{
	char	*path;
	t_list	*tmp;

	tmp = *(data->h_env);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			path = ft_substr(tmp->content,
					ft_strlen("OLDPWD="), ft_strlen(tmp->content));
			change_dir(data, path, 0);
			ft_putendl_fd(path, STDOUT_FILENO);
			free(path);
			return (1);
		}
		else
			tmp = tmp->next;
	}
	ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
	return (0);
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
