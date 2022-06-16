/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:49:04 by root              #+#    #+#             */
/*   Updated: 2022/06/16 19:39:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

size_t	get_cmd_num(t_command **cmd)
{
	size_t	len;

	len = 0;
	while (cmd[len])
		len++;
	return (len);
}

void	print_double_tab(char **tab)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (tab[len])
		len++;
	while (i < len)
		ft_putendl_fd(tab[i++], STDERR_FILENO);
}

void	ft_err(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

void	pipe_err(int *pipefd, int i)
{
	while (i)
	{
		close(pipefd[i]);
		i--;
	}
	free(pipefd);
	perror("failed to create pipes");
	exit(EXIT_FAILURE);
}
