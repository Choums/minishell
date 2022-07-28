/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 02:26:06 by aptive            #+#    #+#             */
/*   Updated: 2022/07/28 18:54:43 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_outspace(char *str)
{
	int	len;

	if (str && ft_strlen(str) > 0)
	{
		len = (int)ft_strlen(str);
		while (len > 1 && str[len - 1] && str[len - 1] == ' ')
			len--;
		return (len);
	}
	return (1);
}

int	error_msg(char *line)
{
	(void)line;
	ft_putstr_fd("Error : unclosed quotation mark\n", STDERR);
	return (0);
}

int	error_msg_signal(char *msg)
{
	g_signal.status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
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
