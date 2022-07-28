/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:27:54 by aptive            #+#    #+#             */
/*   Updated: 2022/07/28 22:31:32 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_int(int code)
{
	(void)code;
	g_signal.sigint = 1;
	ft_putstr_fd("\b\b  \b\b", STDOUT);
	ft_putstr_fd("\n", STDOUT);
	if (g_signal.prompt != 1)
	{
	g_signal.status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_quit(int code)
{
	(void)code;
	ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_putendl_fd("Quit (core dump)", STDERR);
}

/* Interruption (ctrl-C) == sigint == Terminaison int sig 2
 * Interruption forte (ctrl-\)	 == sigquit == Terminaison + core dump int sig 3
*/
void	signal_init(void)
{
	g_signal.nt_status = 0;
	g_signal.status = 0;
	g_signal.sigint = 0;
}
