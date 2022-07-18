/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:27:54 by aptive            #+#    #+#             */
/*   Updated: 2022/07/18 19:47:20 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signal(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGQUIT)
		sig_quit(sig, info, context);
	else if (sig == SIGINT)
		sig_int(sig, info, context);
}

void	sig_quit(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	ft_putstr_fd("\b\b  \b\b", STDERR);
}

void	sig_int(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd("minishell: ", STDERR);
}
// Interruption (ctrl-C) == sigint == Terminaison int sig 2
// Interruption forte (ctrl-\)	 == sigquit == Terminaison + core dump int sig 3

void	signal_init(void)
{
	g_signal.nt_status = 0;
	g_signal.status = 0;
}
