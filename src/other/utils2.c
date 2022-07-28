/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:02:11 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/28 21:15:50 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_cmd_num(t_command **cmd)
{
	size_t	len;

	len = 0;
	while (cmd[len])
		len++;
	return (len);
}

void	data_init(t_data *data)
{
	data->var = NULL;
	data->path = NULL;
	data->pipefd = NULL;
}

int	check_inv_perm(char *cmd, struct stat path_stat)
{
	if ((!(path_stat.st_mode & S_IXUSR)
			|| !(path_stat.st_mode & S_IRUSR)
			|| !(path_stat.st_mode & __S_IFLNK))
		&& (ft_strncmp(cmd, "./", 2) == 0))
		return (1);
	return (0);
}
