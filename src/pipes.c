/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:34:48 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/25 23:22:57 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipex(t_data *data, t_command **cmd)
{
	int		num;
	int		i;
	pid_t	child;

	num = cmd[0]->len_pipe;
	data->pipefd = create_pipes(cmd[0]->len_pipe);
	if (data->pipefd == NULL)
		return (msg_err("pipe", "failed to create pipes", 1));
	i = 0;
	while (num-- >= 0)
	{
		child = fork();
		if (child == 0)
		{
			process(data, cmd[i], i);
			exiter(data, cmd, cmd[i]->tab_cmd);
		}
		else if (child < 0)
			return (msg_err("execve", "failed to create child processus", 1));
		i++;
	}
	end_pipes(data, cmd, child);
	return (0);
}

void	end_pipes(t_data *data, t_command **cmd, pid_t child)
{
	int	status;

	close_pipes(data->pipefd, cmd[0]->len_pipe);
	while (waitpid(child, &status, 0) > 0)
		status_child(status);
}

int	*create_pipes(int num)
{
	int	*pipefd;
	int	i;

	i = 0;
	pipefd = malloc(sizeof(int) * (num * 2));
	if (!pipefd)
		return (NULL);
	while (i < num)
	{
		if (pipe(&pipefd[i * 2]) < 0)
		{
			pipe_err(pipefd, i * 2);
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}

void	close_pipes(int *pipefd, int n_pipe)
{
	int	i;

	i = 0;
	while (i < n_pipe * 2)
		close(pipefd[i++]);
	free(pipefd);
}
