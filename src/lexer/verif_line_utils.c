/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 02:26:06 by aptive            #+#    #+#             */
/*   Updated: 2022/07/19 16:19:04 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_msg(char *line)
{
	(void)line;
	ft_putstr_fd("Error : unclosed quotation mark\n", STDERR);
	return (0);
}

int	error_msg_signal(char *msg)
{
	g_signal.status = 2;
	ft_putstr_fd(" syntax error near unexpected token `", STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("'\n", STDERR);
	return (0);
}

int	pass_quote_verif_line(char *line, int i)
{
	char	c;

	c = line[i];
	i++;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}
