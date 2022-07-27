/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:27:54 by aptive            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/27 17:46:43 by chaidel          ###   ########.fr       */
=======
/*   Updated: 2022/07/27 17:30:39 by tdelauna         ###   ########.fr       */
>>>>>>> 42b91a62be6ddc8c36a051fa3825cfe7bb0953bc
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
	g_signal.sigint = 1;
	ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd("minishell1: ", STDERR);
	rl_replace_line(" ", 0);
}

/* Interruption (ctrl-C) == sigint == Terminaison int sig 2
 * Interruption forte (ctrl-\)	 == sigquit == Terminaison + core dump int sig 3
*/
void	signal_init(struct sigaction *s_sigaction, sigset_t *block_mask)
{
	g_signal.nt_status = 0;
	g_signal.status = 0;
	g_signal.sigint = 0;
	sigemptyset(block_mask);
	s_sigaction->sa_handler = 0;
	s_sigaction->sa_flags = SA_SIGINFO;
	s_sigaction->sa_sigaction = ft_signal;
}
