/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:55:54 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/24 22:29:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Permet de retrouver le fichier bin de la commande donnee et verifie
 *		ses droits.
 *	Ajoute "/[filename]" a chaque path de la lst
 *	-------------------------------------
 *
*/
char	*find_bin(t_data *data, char *bin)
{
	char	*dir;
	char	*path;
	t_list	*tmp;
	int		perm;

	if (!get_elem(data->h_env, "PATH") && !get_elem(data->h_var, "PATH"))
		return (NULL);
	tmp = data->path;
	while (tmp)
	{
		dir = ft_strjoin(tmp->content, "/");
		path = ft_strjoin(dir, bin);
		free(dir);
		perm = check_perm(path);
		if (perm == 1)
			return (path);
		else
			free(path);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_perm(char *path)
{
	struct stat	path_stat;

	if (lstat(path, &path_stat) < 0)
		return (-1);
	else if ((path_stat.st_mode & __S_IFREG))
	{
		if (path_stat.st_mode & S_IXUSR)
			return (1);
		else
			return (msg_err(path, "permission denied", 126));
	}
	return (0);
}

int	check_cmd(char *cmd)
{
	struct stat	path_stat;

	if (lstat(cmd, &path_stat) == 0)
	{
		if (((path_stat.st_mode & __S_IFMT) == __S_IFDIR)
			&& (ft_strncmp(cmd, "./", 2) == 0
				|| cmd[0] == '/'))
			return (msg_err(cmd, ": Is a directory", 126));
		else if (((path_stat.st_mode & __S_IFMT) != __S_IFDIR)
			&& (cmd[ft_strlen(cmd) - 1] == '/'))
			return (msg_err(cmd, ": Not a directory", 126));
		else
		{
			if ((path_stat.st_mode & S_IXUSR) && (ft_strncmp(cmd, "./", 2) == 0
					|| cmd[0] == '/'))
				return (1);
			else if ((!(path_stat.st_mode & S_IXUSR))
				&& ft_strncmp(cmd, "./", 2) == 0)
				return (msg_err(cmd, ": Permission denied", 126));
		}
	}
	return (check_cmd_neg(cmd, path_stat));
}

int	check_cmd_neg(char *cmd, struct stat path_stat)
{
	if (((path_stat.st_mode & __S_IFMT) != __S_IFDIR)
		&& (cmd[ft_strlen(cmd) - 1] == '/'))
		return (msg_err(cmd, ": Not a directory", 126));
	else if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		|| cmd[ft_strlen(cmd) - 1] == '/')
		return (msg_err(cmd, ": No such file or directory", 127));
	return (msg_err(cmd, ": command not found", 127));
}

char	*get_cmd(t_data *data, char *cmd)
{
	char	*path;

	path = find_bin(data, cmd);
	if (!path)
	{
		if (check_cmd(cmd))
			return (cmd);
		else
			return (NULL);
	}
	else
		return (path);
}
