/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:39:55 by aptive            #+#    #+#             */
/*   Updated: 2022/07/19 00:47:43 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pass_redir(char *tmp, int i)
{
	while (tmp[i] && (tmp[i] == '<' || tmp[i] == ' ' || tmp[i] == '>'))
		i++;
	while (tmp[i] && tmp[i] != ' ')
		i++;
	return (i++);
}

int	pass_quote(char *cmd, int i, int cut)
{
	char	c;

	c = cmd[i + cut++];
	if (cmd[i + cut] == '\\')
		cut += 2;
	while (cmd[i + cut] && cmd[i + cut] != c)
	{
		if (cmd[i + cut] == '\\')
			cut += 2;
		else
			cut++;
	}
	return (cut);
}
