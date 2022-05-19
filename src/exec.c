/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:19:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/18 16:35:31 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *	Permet de retrouver le fichier bin de la commande donnee et verifie
 *		ses droits.
 *	Ajoute "/[filename]" a chaque path de la lst
*/
char	*find_bin(t_list *lst_path, char *bin)
{
	char	*dir;
	char	*path;

	while (lst_path)
	{
		dir = ft_strjoin(lst_path->content, "/");
		path = ft_strjoin(dir, bin);
		free(dir);
		if (access(path, F_OK) == 0)
		{
			printf("path");
			return (path);
		}

		free(path);
		lst_path = lst_path->next;
	}
	return (NULL);
}

/*
 *	Child processus
 *	Trouve le path de la commande et l'execute
 *	Si 1er process, doit ouvrir le fichier en input et check
 *
*/
void	process(t_data *data, char *command, char **args, char **envp)
{
	char	*path;

	path = find_bin(data->path, command);
	if (execve(path, args, envp) > 0)
		return ;
}

// void	pipex(t_data *data, char **args)
// {

// }
