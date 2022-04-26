/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:41:51 by root              #+#    #+#             */
/*   Updated: 2022/04/26 17:57:15 by root             ###   ########.fr       */
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
 *	if (!is_oldpwd(data->h_env))
 *		create_oldpwd(data->h_env);
*/
void	change_dir(t_data *data, char *path)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
		perror(""); //Gestion d'erreur
	update_elem(data->h_env, "OLDPWD=", current);
	free(current);
	chdir(path);
	current = getcwd(NULL, 0);
	if (!current)
		perror(""); //Gestion d'erreur
	update_elem(data->h_env, "PWD=", current);
	free(current);
}

void	goto_home(t_list **env)
{
	char	*path;
	t_list	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "HOME=") == 0)
		{
			path = ft_substr(tmp->content, ft_strlen("HOME="), ft_strlen(tmp->content));
			chdir(path);
			free(path);
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void	goto_oldpwd(t_list **env)
{
	char	*path;
	t_list	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "OLDPWD=") == 0)
		{
			path = ft_substr(tmp->content, ft_strlen("OLDPWD="), ft_strlen(tmp->content));
			chdir(path);
			free(path);
			return ;
		}
		else
			tmp = tmp->next;
	}
}
void	create_oldpwd(t_list **env)
{
	char	*path;
	char	*var;

	path = getcwd(NULL, 0);
	var = ft_strjoin("OLDPWD=", path);
	free(path);
	ft_lstadd_back(env, ft_lstnew(var));
	free(var);
}

/*
 *	Check si la var OLDPWD existe
*/
int	is_oldpwd(t_list **env)
{
	t_list	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "OLDPWD=") == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}