/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:06:40 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/21 15:51:18 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		return (change_dir(data, home_path, 1));
	}
	ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
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
			return (change_dir(data, path, 1));
		}
		tmp = tmp->next;
	}
	ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	return (1);
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
			if (!change_dir(data, path, 0))
			{
				ft_putendl_fd(path, STDOUT_FILENO);
				free(path);
				return (0);
			}
			free(path);
			return (1);
		}
		else
			tmp = tmp->next;
	}
	ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
	return (1);
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
