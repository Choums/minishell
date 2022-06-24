/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:41:51 by root              #+#    #+#             */
/*   Updated: 2022/06/24 18:01:21 by root             ###   ########.fr       */
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
		return ;
	}
	free(current);
	change_err(path);
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
	if (!args[1] || (ft_strncmp(args[1], "~", 1) == 0)
		|| ft_strncmp(args[1], "--", 2) == 0)
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

// /*
//  *	check via access si le path donnee existe ainsi que ses droits
//  *	gere le '-' et '~'
// */
// int	check_path(t_data *data, char *path)
// {
// 	char	*tmp;

// 	if (!path || ft_strncmp(path, "~", 1) == 0)
// 	{
// 		if (!get_elem(data->h_env, "HOME"))
// 		{
// 			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
// 			return (0);
// 		}
// 		tmp = get_var(data, "HOME=");
// 		if (access(tmp, F_OK) < 0)
// 		{
// 			free(tmp);
// 			return (0);
// 		}
// 		else
// 			free(tmp);
// 	}
// 	else if (ft_strncmp(path, "-", 1) == 0)
// 	{
// 		if (!get_elem(data->h_env, "OLDPWD"))
// 		{
// 			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
// 			return (0);
// 		}
// 		tmp = get_var(data, "OLDPWD=");
// 		if (access(tmp, F_OK) < 0)
// 		{
// 			free(tmp);
// 			perror("");
// 			return (0);
// 		}
// 		else
// 			free(tmp);

// 	}
// 	else if (check_access(path))
// 	{
// 		ft_putstr_fd("cd: ", STDERR_FILENO);
// 		return (0);
// 	}
// 	return (1);
// }

/*
 *	Check les droits du dir
*/
int	change_err(char *pathname)
{
	struct stat	path_stat;

	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	if (stat(pathname, &path_stat) < 0)
	{
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		// status = 127;
	}
	else if ((path_stat.st_mode & __S_IEXEC) == 0)
	{
		// ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if ((path_stat.st_mode & __S_IFMT) == __S_IFREG)
	{
		// ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	}
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
			path = ft_substr(tmp->content, ft_strlen("HOME="), ft_strlen(tmp->content));
			change_dir(data, path);
			free(path);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
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