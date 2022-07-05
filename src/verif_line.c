/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:33:32 by tdelauna          #+#    #+#             */
/*   Updated: 2022/07/05 19:39:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	verif_quote(char *line)
// {
// 	int	i;
// 	int	nb_quote;

// 	i = 0;
// 	nb_quote = 0;
// 	while (i < ft_strlen(line))
// 	{
// 		if (line[i] == '\'')
// 		{
// 			nb_quote++;
// 			i++;
// 			while (line[i] && line[i] != '\'')
// 				i++;
// 			if (line[i] == '\'')
// 				nb_quote++;
// 		}
// 		if (line[i] == '"')
// 		{
// 			nb_quote++;
// 			i++;
// 			while (line[i] && line[i] != '"')
// 				i++;
// 			if (line[i] == '"')
// 				nb_quote++;
// 		}
// 		i++;
// 	}
// 	if (nb_quote % 2)
// 	{
// 		ft_putstr_fd("Error : unclosed quotation mark\n", STDERR);
// 		return (0);
// 	}
// 	return (1);
// }

int	error_msg(char	*line)
{
	ft_putstr_fd("Error : unclosed quotation mark\n", STDERR);
	return (0);
}

int	verif_quote(char *line)
{
	int	i;
	int	j;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (i < ft_strlen(line))
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

int	verif_redir_syntax(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			char c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
		}
		else if (line[i] == '<')
		{
			while (line [i] && (line[i] == '<' || line[i] == ' '))
				i++;
			if (!line[i])
			{
				ft_putendl_fd(" syntax error near unexpected token `newline'", 2);
				return (0);
			}
			else if (line[i] == '|')
			{
				ft_putendl_fd(" syntax error near unexpected token `|'", 2);
				return (0);
			}
		}
		else if (line[i] == '|')
		{
			i++;
			while (line [i] && line[i] == ' ')
				i++;
			// if (!line[i])
			// {
			// 	ft_putendl_fd(" syntax error near unexpected token `newline'", 2);
			// 	return (0);
			// }
			// else
			if (line[i] == '|')
			{
				ft_putendl_fd(" syntax error near unexpected token `|'", 2);
				return (0);
			}
			else if (line[i] == '>')
			{
				i++;
				if (line [i] && line[i + 1] == '>')
					ft_putendl_fd(" syntax error near unexpected token `>>'", 2);
				else
					ft_putendl_fd(" syntax error near unexpected token `newline'", 2);
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}

int	verif_line(char *line)
{
	if(line && line[0] == '|')
	{
		g_signal.nt_status = 1;
		g_signal.status = 2;
		ft_putendl_fd(" syntax error near unexpected token `|'", 2);
		return (0);
	}
	else if(line && (line[0] == '>' || line[0] == '<'))
	{
		if (ft_strlen(line) < 2)
			ft_putendl_fd(" syntax error near unexpected token `newline'", 2);
		else if (line[2] == '>')
			ft_putendl_fd(" syntax error near unexpected token `>'", 2);
		else if (line[2] == '<')
			ft_putendl_fd(" syntax error near unexpected token `<'", 2);
		else
			ft_putendl_fd(" syntax error near unexpected token `newline'", 2);
		g_signal.nt_status = 1;
		g_signal.status = 2;
		return (0);
	}
	else if (!verif_redir_syntax(line))
	{
		// printf("OKKKK\n");
		g_signal.nt_status = 1;
		g_signal.status = 2;
		return (0);
	}
	else if (line && ft_strlen(line) && verif_quote(line))
		return (1);
	else
		return (0);
}
