/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:33:32 by tdelauna          #+#    #+#             */
/*   Updated: 2022/07/19 16:27:49 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verif_quote(char *line)
{
	int	i;
	int	j;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (i < (int)ft_strlen(line))
	{
		j = 1;
		if (line[i] == '\\')
			i += 2;
		if (line[i] == '\'' || line[i] == '"')
		{
			nb_quote++;
			while (line[i + j] && line[i + j] != line[i])
				if (line[i + j++] == '\\')
					j++;
			if (line[i + j++] == line[i])
				nb_quote++;
		}
		i += j;
	}
	if (nb_quote % 2)
		return (error_msg("Error : unclosed quotation mark\n"));
	return (1);
}

int	verif_pipe(char *line, int *i)
{
	++*i;
	while (line [*i] && line[*i] == ' ')
		++*i;
	if (line[*i] == '|')
		return (error_msg_signal("|"));
	else if (line[*i] == '>')
	{
		if (line [++*i] && line[*i + 1] == '>')
			return (error_msg_signal(">>"));
		else if (ft_strlen(line + *i) == 0)
		{
			// printf("len : %i\n", (int)ft_strlen(line + *i));
			return (error_msg_signal("newline"));
		}
	}
	return (1);
}
// echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission
// echo hi | >
int	verif_redir_syntax(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = pass_quote_verif_line(line, i);
		else if (line[i] == '<')
		{
			while (line [i] && (line[i] == '<' || line[i] == ' '))
				i++;
			if (!line[i])
				return (error_msg_signal("newline"));
			else if (line[i] == '|')
				return (error_msg_signal("|"));
		}
		else if (line[i] == '|')
		{
			if (!verif_pipe(line, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	verif_line(char *line)
{
	if (line && line[0] == '|')
		return (error_msg_signal("|"));
	else if (line && (line[0] == '>' || line[0] == '<'))
	{
		if (ft_strlen(line) < 2)
			return (error_msg_signal("newline"));
		else if (line[2] == '>')
			return (error_msg_signal(">"));
		else if (line[2] == '<')
			return (error_msg_signal("<"));
		else
			return (error_msg_signal("newline"));
	}
	else if (!verif_redir_syntax(line))
	{
		g_signal.status = 2;
		return (0);
	}
	else if (line && ft_strlen(line) && verif_quote(line))
		return (1);
	return (0);
}
