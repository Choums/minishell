/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:48:30 by root              #+#    #+#             */
/*   Updated: 2022/04/27 17:37:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char *arg)
{
	if (*arg)
		ft_putendl_fd(arg, STDOUT_FILENO);
}

void	pwd(void)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	if (!path)
		perror(""); //Gestion d'erreur
	echo(path);
	free(path);
}

int	is_exit(t_data *data, char *line)
{
	if (!ft_strcmp(line, "exit"))
	{
		free(line);
		rl_clear_history();
		ft_lstclear(&data->env, del);
		ft_lstclear(&data->var, del);
		exit(EXIT_SUCCESS);
	}
	return (1);
}