/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:35:36 by root              #+#    #+#             */
/*   Updated: 2022/07/04 20:06:12 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_err(char *command, int alloc)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd("': not a valid identfier", STDERR_FILENO);
	if (alloc)
		free(command);
}

/*
 *	Affiche le message d'erreur basique de bash et retourne 0
*/
int	msg_err(char *cmd, char *msg, int status)
{
	g_signal.status = status;
	g_signal.nt_status = 1;
	// printf("numero err : %i\n", g_signal.status);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (0);
}
