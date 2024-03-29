/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:35:36 by root              #+#    #+#             */
/*   Updated: 2022/07/28 18:23:08 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_err(char *command)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_signal.nt_status = 1;
	g_signal.status = 1;
}

/*
 *	Ferme les fds precedement ouvert et free le tableau
*/
int	pipe_err(int *pipefd, int i)
{
	if (i == 0)
		i += 2;
	while (i)
		close(pipefd[i--]);
	free(pipefd);
	return (msg_err("pipe", "failed to create pipes", errno));
}

void	exit_err(t_data *data, t_command **tab, char *arg)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	is_exit(data, tab, 2);
}

/*
 *	Affiche le message d'erreur basique de bash et retourne 0
*/
int	msg_err(char *cmd, char *msg, int status)
{
	g_signal.status = status;
	g_signal.nt_status = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (0);
}

int	redir_err(char *file)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	g_signal.status = 1;
	return (0);
}
