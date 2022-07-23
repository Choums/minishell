/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:41:51 by root              #+#    #+#             */
/*   Updated: 2022/07/21 16:24:17 by chaidel          ###   ########.fr       */
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
int	change_dir(t_data *data, char *path, int alloc)
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
		update_pwd(data);
		if (alloc)
			free(path);
		return (0);
	}
	free(current);
	return (change_err(path, alloc));
}

void	update_pwd(t_data *data)
{
	char	*var;
	char	*current;

	current = getcwd(NULL, 0);
	if (current)
	{
		var = ft_strjoin("PWD=", current);
		free(current);
		update_elem(data, var);
		free(var);
	}
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
			return (goto_homepath(data, args[1]));
		return (goto_home(data));
	}
	if (ft_strncmp(args[1], "-", 1) == 0)
		return (goto_oldpwd(data));
	return (change_dir(data, args[1], 0));
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
	return (1);
}
