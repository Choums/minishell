/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:05:20 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/21 17:20:31 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			all_paths = ft_substr(tmp->content, 5, ft_strlen(tmp->content));
			paths = ft_split(all_paths, ':');
			free(all_paths);
			set_path(data, paths);
			free_double_tab(paths);
			return ;
		}
		else
			tmp = tmp->next;
	}
	set_def_path(data);
}

void	set_def_path(t_data *data)
{
	char	**paths;
	char	*all_paths;

	set_var(data, DEF);
	all_paths = ft_substr(DEF, ft_strlen("PATH="), ft_strlen(DEF));
	paths = ft_split(all_paths, ':');
	free(all_paths);
	set_path(data, paths);
	free_double_tab(paths);
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
